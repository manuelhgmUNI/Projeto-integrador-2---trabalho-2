#include <stdbool.h>
#include <stdint.h>

#ifndef dcl_str_p2_H
#define dcl_str_p2_H

    // 
    typedef enum {
        FETCH = 0,
        DECODE = 1,
        MEM_ADDR = 2,
        MEM_READ = 3,
        MEM_WRITEBACK = 4,
        MEM_WRITE = 5,
        EXEC_I = 6,
        EXEC_R = 7,
        BRANCH_COMP = 8,
        JUMP_COMP = 9
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

    typedef struct {
        uint16_t RI;       // Instruction Register
        uint16_t RDM;      // Memory Data Register
        int8_t A;          // Reg A (saida rs)
        int8_t B;          // Reg B (saida rt)
        int8_t ALUOut;     // ALU Out
    } tpy_int_reg;

    typedef struct {
        int8_t banco[8];
        tpy_int_reg intermediario;
        uint8_t PC;
    } typ_all_reg;
    
    // Valores no datapath (sinais combinacionais)
    typedef struct {
        uint8_t mux_mem;      // Endereço para memória
        uint16_t saida_mem;   // Saída da memória
        uint8_t mux_reg_dest; // Destino no banco de regs (rt ou rd)
        int8_t mux_mem_reg;   // Dado para o banco de regs (ALUOut ou MDR)

        int8_t rs_val;        // Valor lido do banco (rs)
        int8_t rt_val;        // Valor lido do banco (rt)

        int8_t mux_ula_A;     // Entrada A da ULA
        int8_t mux_ula_B;     // Entrada B da ULA
        typ_ulaR ular;        // Resultado da ULA

        uint8_t mux_pc;       // Próximo PC
    } typ_dados;

    typedef struct {
        typ_memoria_principal memoria;
        typ_all_reg registrador;
        typ_decoded_instruction ir_decoded;
        typ_dados caminhos;
        bool sinais[20];      
        estado_fsm estado; // Adicionado para rastrear o estado atual da FSM

        // stats
        int total_instrucoes;
        int r_instrucoes;
        int i_instrucoes;
        int j_instrucoes;
        int nop_instrucoes;
    } typ_state;

    // Sinais de Controle ( array sinais)
    enum {
        ControleUla1 = 0,
        ControleUla2 = 1,
        ControleUla3 = 2,
        PCEsc        = 3,
        Branch       = 4,
        IouD         = 5,
        EscMem       = 6,
        IREsc        = 7,
        MemParaReg   = 8,
        RegDst       = 9,
        EscReg       = 10,
        UlaFonteA    = 11,
        UlaFonteB1   = 12,
        UlaFonteB0   = 13,
        PCFonte1     = 14,
        PCFonte0     = 15,
        estado0      = 16, // e0 
        estado1      = 17, // e1
        estado2      = 18, // e2
        estado3      = 19  // e3 
    };

    enum opcodes {
        addi = 4,
        beq  = 8,
        lw   = 11,
        sw   = 15,
        j_op = 2,
        r_op = 0
    };

#endif
