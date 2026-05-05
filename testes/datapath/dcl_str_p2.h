#include<stdbool.h>
#include<stdint.h>

#ifndef dcl_str_p2_H
#define dcl_str_p2_H

    // declaração das strings projeto 2

    typedef struct 
    {
        uint16_t RI;
        uint16_t RDM;
        uint8_t A;
        uint8_t B;
        uint8_t ULA_saida;
    }tpy_int_reg;

    typedef struct 
    {
        uint8_t banco[8];
        tpy_int_reg intermediario;
        uint8_t PC;
    }typ_all_reg;
    
    
    typedef struct 
    {
        
        typ_all_reg registrador;
        bool sinais[20];
    }typ_state;

    enum // sinais do controle
    {
        ControleUla1 =  0,
        ControleUla2 =  1,
        ControleUla3 =  2,
        PCEsc = 3,
        Branch = 4,
        IouD = 5,
        EscMem = 6,
        IREsc = 7,
        MemParaReg = 8,
        RegDst = 9,
        EscReg = 10,
        UlaFonteA = 11,
        UlaFonteB1 = 12,
        UlaFonteB0 = 13,
        PCFonte1 = 14,
        PCFonte0 = 15,
        estado0 = 16,
        estado1 = 17,
        estado2 = 18,
        estado3 = 19,
    };
    

#endif