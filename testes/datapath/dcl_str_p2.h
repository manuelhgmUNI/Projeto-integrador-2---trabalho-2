#include<stdbool.h>
#include<stdint.h>

#ifndef dcl_str_p2_H
#define dcl_str_p2_H

    enum tipos_de_instrucao
    {
        r = 1,
        i = 2,
        j = 3,
    };

    typedef struct str_instrucao
    {
        enum tipos_de_instrucao tipo;
        uint16_t instrucao_bruta;
        char total[18];
        uint16_t opcode;
        uint16_t rs;
        uint16_t rt;
        uint16_t rd;
        uint16_t funct;
        int16_t  immediato;
        uint16_t addr;
    } typ_decoded_instruction;
    typedef typ_decoded_instruction typ_ins;

    typedef enum {
        ADD = 0,
        SUB = 2,
        AND = 4,
        OR  = 5,
    } typ_ulaOp;

    typedef struct {
        int resultado;
        bool zero;
        bool overflow;
    } typ_ulaR;

    typedef struct 
    {
        typ_ulaOp Op;
        typ_ulaR R;
    }typ_ula;

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
        int8_t banco[8];
        tpy_int_reg intermediario;
        uint8_t PC;
    }typ_all_reg;
    
    // valores no caminho de dados
    typedef struct 
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

        typ_ula ula;
        int8_t ULA_saida;

        uint8_t mux_pc;

    }typ_dados;

    typedef struct 
    {
        typ_dados dados; // dados no datapath
        typ_ins instrucao;
        
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