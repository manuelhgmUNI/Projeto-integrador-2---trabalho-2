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
        typ_dados dados; // dados no datapath
        
        typ_all_reg registrador;
        bool sinais[20];
    }typ_state;

    typedef struct // valores no caminho de dados
    {
        uint8_t mux_mem; // endereço da memoria
        int16_t saida_mem; // saida da memoria
        uint8_t mux_reg_dest; // mux do rt e rd
        uint8_t mux_mem_reg; // mux do dado no banco

        int8_t rs; // saida do banco
        int8_t rt; // saida do banco

        int8_t A; // saida do intermediario A
        int8_t B; // saida do intermediario B


        int8_t mux_ulaA; // valor da saida do mux de entrada de cima da ula
        int8_t mux_ulaB; // valor da saida do mux de entrada de baixo da ula
        bool zero_ula; // sinal zero da ula
        int8_t ula; // saida da ula

        uint8_t mux_pc;

    }typ_dados;
    

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