#include <stdint.h>
#include <stdbool.h>

#ifndef structs_H
#define structs_H

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

    typedef struct {
        uint16_t palavras[256];
    } typ_memoria_principal;

    enum tipos_de_instrucao
    {
        r = 1,
        i = 2,
        j = 3,
    };

    typedef struct str_instrucaoV2
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

    typedef struct str_regis
    {
        int8_t $[8];
    } typ_reg;

    typedef typ_reg BancoRegistradores;

    typedef enum {
        ADD = 0,
        SUB = 2,
        AND = 4,
        OR  = 5,
        SLT
    } typ_ulaOp;

    typedef struct {
        int resultado;
        bool zero;
        bool overflow;
    } typ_ulaR;

    typedef struct {
        int pc;
        typ_reg banco_reg;
        typ_memoria_principal mem_principal;
    } print;

    typedef struct str_state
    {
        estado_fsm estado;
        typ_memoria_principal *mem_principal;
        typ_reg *registradores;
        unsigned char pc;
        typ_decoded_instruction ir; //(IR)
        int mdr; // (MDR)
        int A, B; // Registradores A e B
        int alu_out; // saida da ULA

        print pilha_back[2000];
        int topo_pilha;
        
        int total_instrucoes;
        int r_instrucoes;
        int i_instrucoes;
        int j_instrucoes;
        int nop_instrucoes;

        bool sinal[8];
        typ_ulaOp ulaop;
        typ_ulaR ular;
    } typ_stt;

    enum
    {
        esc_mem = 0, 
        esc_reg = 1, 
        mem_reg = 2, 
        ula_fon = 3, 
        reg_des = 4, 
        inc_pc  = 5, 
        jump    = 6, 
        branch  = 7, 
        ir_esc  = 8
    };

    enum tipo_i
    {
        addi = 4,
        beq  = 8,
        lw   = 11,
        sw   = 15,
    };

#endif
