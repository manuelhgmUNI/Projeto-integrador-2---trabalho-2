#include "dcl_str_p2.h"

void Unidade_de_Controle(typ_state **c)
{

    Controle_sinais(c);
    controle_ula_fonte(c);
    controle_pc_fonte(c);

    decodifica_estado_para_sinais(c);
}


void Controle_sinais(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];

    (**c).sinais[Branch] = e0 && e3;

    (**c).sinais[PCEsc] = (( (!e3 && !e2) && (!e1 && !e0) ) || (e3 && e1));

    (**c).sinais[IouD] = (((!e2 && e1) && e0) || ((e2 && !e1) && e0));

    (**c).sinais[EscMem] = ((e2 && !e1) && e0);

    (**c).sinais[IREsc] = ((!e3 && !e2) && (!e1 && !e0));

    (**c).sinais[MemParaReg] = ((e2 && !e1) && !e0);

    (**c).sinais[RegDst] = ( ( ( (!e3 && !e2) & !e1 ) || ( (!e3 && e2) && (e1 && e0) ) ) || ( (e3 && !e1) && !e0) );

    (**c).sinais[EscReg] = ( (e2 && !e0) || ( (e3 && !e1) && !e0) );

}

void controle_ula_fonte(typ_state **c)
{
    // limpa sinais
    (**c).sinais[UlaFonteA] = 0;
    (**c).sinais[UlaFonteB1] = 0;
    (**c).sinais[UlaFonteB0] = 0;

    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];

    //FETCH PC = PC + 1

    if ((!e3 && !e2) && (!e1 && !e0))
    {
        (**c).sinais[UlaFonteA] = 0;

        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1;
    }

    // Tipo R A op B
    
    if ((**c).instrucao.tipo == r)
    {
        (**c).sinais[UlaFonteA] = 1;

        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
    }

    // LW / SW / ADDI  base + imediato

    if ((**c).instrucao.opcode == 11 || // lw
        (**c).instrucao.opcode == 15 || // sw
        (**c).instrucao.opcode == 4)    // addi
    {
        (**c).sinais[UlaFonteA] = 1;

        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
    }

    // BEQA - B

    if ((**c).instrucao.opcode == 8)
    {
        (**c).sinais[UlaFonteA] = 1;

        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
    }
}

void controle_pc_fonte(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];

    (**c).sinais[PCFonte1] = (((e3 && !e2) && e1) || ((e3 && e2) && e0));
    (**c).sinais[PCFonte0] = (((e3 && !e2) && e1));
}


void decodifica_estado_para_sinais(typ_state *s) {
    int v = (int)s->estado; // pega o int do enum 0-9

    
    s->prox_estado[PE0] = (v >> 0) & 1; // bit 0
    s->prox_estado[PE1] = (v >> 1) & 1; // bit 1
    s->prox_estado[PE2] = (v >> 2) & 1; // bit 2
    s->prox_estado[PE3] = (v >> 3) & 1; // bit 3
}