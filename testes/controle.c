#include "assinaturas.h"

static void Controle_sinais(typ_state **c);
static void controle_ula_fonte(typ_state **c);
static void controle_ula_operacao(typ_state **c);
static void controle_pc_fonte(typ_state **c);

void controle(typ_state **c)
{
    Controle_sinais(c);
    controle_ula_fonte(c);
    controle_ula_operacao(c);
    controle_pc_fonte(c);

    decodifica_estado_para_sinais(*c);
}

void Controle_sinais(typ_state **c)
{
    estado_fsm st = (**c).estado;

    (**c).sinais[Branch] = (st == BRANCH_COMP);
    (**c).sinais[PCEsc] = (st == FETCH);
    (**c).sinais[IouD] = (st == MEM_ADDR || st == MEM_READ || st == MEM_WRITE);
    (**c).sinais[EscMem] = (st == MEM_WRITE);
    (**c).sinais[IREsc] = (st == FETCH);
    (**c).sinais[MemParaReg] = (st == MEM_WRITEBACK);
    (**c).sinais[RegDst] = (st == EXEC_R);
    (**c).sinais[EscReg] = (st == EXEC_I || st == EXEC_R || st == MEM_WRITEBACK);
}

void controle_ula_fonte(typ_state **c)
{
    estado_fsm st = (**c).estado;

    if (st == FETCH) {
        (**c).sinais[UlaFonteA] = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1;
        return;
    }

    if (st == DECODE) {
        (**c).sinais[UlaFonteA] = 0;
        if ((**c).instrucao.opcode == beq) {
            (**c).sinais[UlaFonteB1] = 1;
            (**c).sinais[UlaFonteB0] = 0;
        } else {
            (**c).sinais[UlaFonteB1] = 0;
            (**c).sinais[UlaFonteB0] = 1;
        }
        return;
    }

    if (st == MEM_ADDR || st == MEM_READ || st == MEM_WRITE || st == EXEC_I) {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        return;
    }

    if (st == EXEC_R || st == BRANCH_COMP) {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
        return;
    }

    (**c).sinais[UlaFonteA] = 0;
    (**c).sinais[UlaFonteB1] = 0;
    (**c).sinais[UlaFonteB0] = 0;
}

void controle_ula_operacao(typ_state **c)
{
    estado_fsm st = (**c).estado;

    if (st == EXEC_R) {
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 1;
        (**c).sinais[ControleUla3] = 0;
        return;
    }

    if (st == BRANCH_COMP) {
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 1;
        return;
    }

    (**c).sinais[ControleUla1] = 0;
    (**c).sinais[ControleUla2] = 0;
    (**c).sinais[ControleUla3] = 0;
}

void controle_pc_fonte(typ_state **c)
{
    estado_fsm st = (**c).estado;
    (**c).sinais[PCFonte1] = (st == JUMP_COMP);
    (**c).sinais[PCFonte0] = (st == BRANCH_COMP);
}
