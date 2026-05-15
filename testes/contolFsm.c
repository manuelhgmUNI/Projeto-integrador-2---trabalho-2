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

//ciclo clock 1
void executar(typ_state *s) {
    //(FSM) gera os sinais de controle baseados no estado atual
    controle(&s);

    // chama datapath
    caminho_de_dados(&s, false);
    
    //stats
    if (s->estado == FETCH) {
        typ_decoded_instruction d = decode_instruction(s->memoria.palavras[s->registrador.PC]);
        if (d.instrucao_bruta != 0) {
            s->total_instrucoes++;
            if      (d.tipo == r) s->r_instrucoes++;
            else if (d.tipo == i) s->i_instrucoes++;
            else if (d.tipo == j) s->j_instrucoes++;
        } else {
            s->nop_instrucoes++;
        }
    }

    // proximo estado borda de clock
    estado_fsm proximo = calcula_proximo_estado(s->estado, s->ir_decoded.opcode);
    atualiza_estado(s, proximo);
}