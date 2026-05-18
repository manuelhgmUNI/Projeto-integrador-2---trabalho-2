#include "dcl_str_p2.h"
#include "assinaturas.h"

void Unidade_de_Controle(typ_state **c)
{
    // proximo estado
    (**c).prox_estado_fsm = calcula_proximo_estado((**c).estado, (**c).instrucao.opcode);

    //sinais controle state atual
    Controle_sinais(c);
    controle_ula_fonte(c);
    controle_ula(c);
    controle_pc_fonte(c);

    // transicao
    decodifica_estado_para_sinais_prox(*c);

}

//tirei o bitwise

void Controle_sinais(typ_state **c)
{
    estado_fsm st = (**c).estado;
    uint16_t op = (**c).instrucao.opcode;

    // inicializa zerado
    for(int i=0; i<20; i++) (**c).sinais[i] = 0;

    // IREsc: spenas no FETCH
    (**c).sinais[IREsc] = (st == FETCH);

    // PCEsc: no FETCH (PC+1) e no JUMP_COMP
    (**c).sinais[PCEsc] = (st == FETCH || st == JUMP_COMP);

    // Branch: apenas no BRANCH_COMP
    (**c).sinais[Branch] = (st == BRANCH_COMP);

    // IouD: 1 para acesso a dados (MEM_READ, MEM_WRITE), 0 para instruções
    (**c).sinais[IouD] = (st == MEM_READ || st == MEM_WRITE);

    // EscMem: Apenas no MEM_WRITE
    (**c).sinais[EscMem] = (st == MEM_WRITE);

    // EscReg: nMEM_WRITEBACK (LW) e REG_WRITEBACK (R-type, ADDI)
    (**c).sinais[EscReg] = (st == MEM_WRITEBACK || st == REG_WRITEBACK);

    // MemParaReg: 1 para carregar da memória (LW), 0 para ALUOut
    (**c).sinais[MemParaReg] = (st == MEM_WRITEBACK);

    // RegDst: 1 para rd (R-type), 0 para rt (ADDI, LW)
    // No REG_WRITEBACK, depende se e R-type ou ADDI
    if (st == REG_WRITEBACK) {
        (**c).sinais[RegDst] = (op == r_op);
    } else if (st == MEM_WRITEBACK) {
        (**c).sinais[RegDst] = 0; // rt para LW
    }
}

void controle_ula_fonte(typ_state **c)
{
    estado_fsm st = (**c).estado;

    if (st == FETCH) {
        (**c).sinais[UlaFonteA] = 0;  // PC
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1; // 1
        return;
    }

    if (st == DECODE) {
        (**c).sinais[UlaFonteA] = 0;  // PC
        // No DECODE, sempre calcula o alvo do branch pc+1+offsett
        (**c).sinais[UlaFonteB1] = 1; // Imm
        (**c).sinais[UlaFonteB0] = 0;
        return;
    }

    if (st == MEM_ADDR || st == MEM_WRITE || st == EXEC_I) {
        (**c).sinais[UlaFonteA] = 1;  // A
        (**c).sinais[UlaFonteB1] = 1; // Immediato
        (**c).sinais[UlaFonteB0] = 0;
        return;
    }

    if (st == EXEC_R || st == BRANCH_COMP) {
        (**c).sinais[UlaFonteA] = 1;  // A
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0; // B
        return;
    }
}

void controle_pc_fonte(typ_state **c)
{
    estado_fsm st = (**c).estado;

    // 00: ALU Result
    // 01: ALUOut
    // 10: Jump Target

    if (st == FETCH) {
        (**c).sinais[PCFonte1] = 0;
        (**c).sinais[PCFonte0] = 0;
    } else if (st == BRANCH_COMP) {
        (**c).sinais[PCFonte1] = 0;
        (**c).sinais[PCFonte0] = 1; 
    } else if (st == JUMP_COMP) {
        (**c).sinais[PCFonte1] = 1;
        (**c).sinais[PCFonte0] = 0;
    }
}

void decodifica_estado_para_sinais_prox(typ_state *s) {
    int v = (int)s->prox_estado_fsm; 
    s->prox_estado[PE0] = (v >> 0) & 1; 
    s->prox_estado[PE1] = (v >> 1) & 1; 
    s->prox_estado[PE2] = (v >> 2) & 1; 
    s->prox_estado[PE3] = (v >> 3) & 1; 
}


estado_fsm calcula_proximo_estado(estado_fsm estado_atual, uint16_t opcode) {
    estado_fsm proximo = FETCH; // Padrão
    
    switch (estado_atual) {
        case FETCH:
            proximo = DECODE;
            break;

        case DECODE:
            switch (opcode) {
                case lw:
                case sw:    proximo = MEM_ADDR;     break;
                case r_op:  proximo = EXEC_R;       break;
                case beq:   proximo = BRANCH_COMP;  break;
                case j_op:  proximo = JUMP_COMP;    break;
                case addi:  proximo = EXEC_I;       break;
                default:    proximo = FETCH;        break; //  NOP
            }
            break;

        case MEM_ADDR:
            proximo = (opcode == lw) ? MEM_READ : MEM_WRITE;
            break;

        case MEM_READ:
            proximo = MEM_WRITEBACK;
            break;

        case EXEC_R:
            proximo = REG_WRITEBACK;
            break;
        case EXEC_I:
            proximo = REG_WRITEBACK;
            break;

        case MEM_WRITEBACK:
        case MEM_WRITE:
        case BRANCH_COMP:
        case JUMP_COMP:
            //finalizam e retornam pra fetch
            proximo = FETCH;
            break;
    }
    return proximo;
}

void controle_ula(typ_state **c)
{
    (**c).sinais[ControleUla1] = 0;
    (**c).sinais[ControleUla2] = 0;
    (**c).sinais[ControleUla3] = 0;
    (**c).dados.ula.Op = ADD;

    if ((**c).instrucao.tipo == r)
    {
        switch ((**c).instrucao.funct)
        {
            // ADD
            case 0:
                (**c).sinais[ControleUla1] = 0;
                (**c).sinais[ControleUla2] = 0;
                (**c).sinais[ControleUla3] = 0;
                (**c).dados.ula.Op = ADD;
                break;

            // SUB
            case 2:
                (**c).sinais[ControleUla1] = 0;
                (**c).sinais[ControleUla2] = 0;
                (**c).sinais[ControleUla3] = 1;
                (**c).dados.ula.Op = SUB;
                break;

            // AND
            case 4:
                (**c).sinais[ControleUla1] = 0;
                (**c).sinais[ControleUla2] = 1;
                (**c).sinais[ControleUla3] = 1;
                (**c).dados.ula.Op = AND;
                break;

            // OR
            case 5:
                (**c).sinais[ControleUla1] = 1;
                (**c).sinais[ControleUla2] = 0;
                (**c).sinais[ControleUla3] = 0;
                (**c).dados.ula.Op = OR;
                break;
        }
    }

    // LW / SW / ADDI

    if ((**c).instrucao.opcode == 11 || // lw
        (**c).instrucao.opcode == 15 || // sw
        (**c).instrucao.opcode == 4)    // addi
    {
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 0;
        (**c).dados.ula.Op = ADD;
    }

    // BEQ

    if ((**c).instrucao.opcode == 8)
    {
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 1;
        (**c).dados.ula.Op = SUB;
    }
}

void decodifica_estado_para_sinais(typ_state *s) {
    int v = (int)s->estado; // pega o int do enum 0-9

    
    s->prox_estado[PE0] = (v >> 0) & 1; // bit 0
    s->prox_estado[PE1] = (v >> 1) & 1; // bit 1
    s->prox_estado[PE2] = (v >> 2) & 1; // bit 2
    s->prox_estado[PE3] = (v >> 3) & 1; // bit 3
}

void decodifica_sinais_para_estado(typ_state *s)
{
    s->estado = 0;

    s->estado |= s->sinais[estado0];
    s->estado |= s->sinais[estado1] << 1;
    s->estado |= s->sinais[estado2] << 2;
    s->estado |= s->sinais[estado3] << 3;
    return;
}
