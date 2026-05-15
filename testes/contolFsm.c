#include "assinaturas.h"
#include <stdio.h>


 // Calcula o proximo estado baseado no estado atual e no opcode.
 
estado_fsm calcula_proximo_estado(estado_fsm estado_atual, uint16_t opcode) {
    estado_fsm proximo = FETCH; // Padrão
    
    switch (estado_atual) {
        case FETCH:
            proximo = DECODE;
            break;

        case DECODE:
            switch (opcode) {
                case lw:
                case sw:    proximo = MEM_ADDR;     break;
                case r_op:  proximo = EXEC_R;       break;
                case beq:   proximo = BRANCH_COMP;  break;
                case j_op:  proximo = JUMP_COMP;    break;
                case addi:  proximo = EXEC_I;       break;
                default:    proximo = FETCH;        break; //  NOP
            }
            break;

        case MEM_ADDR:
            proximo = (opcode == lw) ? MEM_READ : MEM_WRITE;
            break;

        case MEM_READ:
            proximo = MEM_WRITEBACK;
            break;

        case MEM_WRITEBACK:
        case MEM_WRITE:
        case EXEC_R:
        case EXEC_I:
        case BRANCH_COMP:
        case JUMP_COMP:
            //finalizam e retornam pra fetch
            proximo = FETCH;
            break;
    }
    return proximo;
}


void atualiza_estado(typ_state *s, estado_fsm proximo) {
    s->estado = proximo;
}

void decodifica_estado_para_sinais(typ_state *s) {
    int v = (int)s->estado; // pega o int do enum 0-9

    
    s->sinais[estado0] = (v >> 0) & 1; // bit 0
    s->sinais[estado1] = (v >> 1) & 1; // bit 1
    s->sinais[estado2] = (v >> 2) & 1; // bit 2
    s->sinais[estado3] = (v >> 3) & 1; // bit 3
}

