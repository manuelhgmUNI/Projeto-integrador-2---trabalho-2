#include "dcl_str_p2.h"

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
