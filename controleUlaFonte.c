#include "dcl_str_p2.h"

void controle_ula_fonte(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];
    
    // RESET DOS SINAIS
    (**c).sinais[UlaFonteA] = 0;

    (**c).sinais[UlaFonteB0] = 0;
    (**c).sinais[UlaFonteB1] = 0;

    (**c).sinais[ControleUla1] = 0;
    (**c).sinais[ControleUla2] = 0;
    (**c).sinais[ControleUla3] = 0;

    // FETCH ESTADO 0000 ULA = PC + 1

    if ((!e3 && !e2) && (!e1 && !e0))
    {
        //Entrada A = PC
        (**c).sinais[UlaFonteA] = 0;

        //Entrada B = 1
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1;

        // Operação = ADD ALUOp = 000
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 0;
    }

    // EXECUÇÃO TIPO R
    if ((**c).instrucao.tipo == r)
    {
        // A = registrador A
        (**c).sinais[UlaFonteA] = 1;

        // B = registrador B
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;

        //  ALUOp = 010  usa funct
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 1;
        (**c).sinais[ControleUla3] = 0;
    }

    // LW / SW / ADDI
    if ((**c).instrucao.opcode == 11 || // lw
        (**c).instrucao.opcode == 15 || // sw
        (**c).instrucao.opcode == 4)    // addi
    {
        // A = registrador base
        (**c).sinais[UlaFonteA] = 1;

        // B = imediato
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;

        //  ALUOp = 000 ADD
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 0;
    }

    //BEQ
    if ((**c).instrucao.opcode == 8)
    {
        // A = registrador A
        (**c).sinais[UlaFonteA] = 1;

        // B = registrador B
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;

        // ALUOp = 001 SUB
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 1;
    }
}
