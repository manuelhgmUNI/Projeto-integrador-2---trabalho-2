#include "dcl_str_p2.h"

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