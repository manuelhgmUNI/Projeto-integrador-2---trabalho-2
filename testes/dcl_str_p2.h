#include<stdbool.h>
#include<stdint.h>

#ifndef dcl_str_p2_H
#define dcl_str_p2_H

    // estados fsm
    typedef enum {
        FETCH = 0,
        DECODE = 1,
        MEM_ADDR = 2,
        MEM_READ = 3,
        MEM_WRITEBACK = 4,
        MEM_WRITE = 5,
        EXEC_I = 6,
        EXEC_R = 7,
        BRANCH_COMP = 9,
        JUMP_COMP = 10
    } estado_fsm;

  
    enum tipos_de_instrucao {
        r = 1, i = 2, j = 3
    };

    typedef struct {
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

    typedef struct {
        uint16_t palavras[256];
    } typ_memoria_principal;

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
        uint16_t RI;       
        uint16_t RDM;     
        int8_t A;          
        int8_t B;          
        int8_t ULA_saida;  
    } tpy_int_reg;

    typedef struct 
    {
        int8_t banco[8];
        tpy_int_reg intermediario;
        uint8_t PC;
    } typ_all_reg;
    
    //valores no datapath
    typedef struct 
    {
        uint8_t mux_mem;      // endereco
        uint16_t saida_mem;   
        uint8_t mux_reg_dest; // destino no banco de regs
        int8_t mux_mem_reg;   // dado para o banco de regs

        int8_t rs_val;        
        int8_t rt_val;        

        int8_t mux_ula_A;     
        int8_t mux_ula_B;     
        typ_ulaR ular;        // result ula

        uint8_t mux_pc;       // prox pc
    } typ_dados;

    typedef struct 
    {
        estado_fsm estado;
        typ_memoria_principal memoria;
        typ_all_reg registrador;
        typ_decoded_instruction ir_decoded;
        typ_dados caminhos;   // datapath
        bool sinais[20];      

        // estatisticas
        int total_instrucoes;
        int r_instrucoes;
        int i_instrucoes;
        int j_instrucoes;
        int nop_instrucoes;
    } typ_state;

    //sinais controle
    enum 
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

    enum opcodes
    {
        addi = 4,
        beq  = 8,
        lw   = 11,
        sw   = 15,
        j_op = 2,
        r_op = 0
    };
#endif
