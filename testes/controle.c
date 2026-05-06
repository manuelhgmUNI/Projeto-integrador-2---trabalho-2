#include "structs.h"
#include "funcoes.h"

typ_stt *controlador(typ_stt *state)
{
    // reset todos os sinais de controle a cada ciclo, faz sentido???
    for (int i = 0; i < 8; i++) state->sinal[i] = 0;

    switch (state->estado)
    {
    case FETCH:
        // sinaliza incremento de PC; IR será carregado em DECODE
        state->sinal[inc_pc] = 1;
        state->sinal[ir_esc] = 1; 
        state->estado = DECODE;
        break;

    case DECODE:
        //  IR da instrução em mem[pc-1] (pc já foi incrementado no FETCH)
        //  A e B do banco de registradores 
        state->ir = decode_instruction(state->mem_principal->palavras[state->pc - 1]);
        state->A  = state->registradores->$[state->ir.rs];
        state->B  = state->registradores->$[state->ir.rt];

        //  baseada no tipo/opcode
        if (state->ir.tipo == r)
            state->estado = EXEC_R;
        else if (state->ir.opcode == lw  ||  state->ir.opcode == sw  || state->ir.opcode == addi)
            state->estado = MEM_ADDR;
        else if (state->ir.opcode == beq)
            state->estado = BRANCH_COMP;
        else if (state->ir.tipo == j)       
            state->estado = JUMP_COMP;
        else
            state->estado = FETCH;
        break;

    case MEM_ADDR:
        // ULA calcula endereço: A + sign_ext(imm)
        // ula_fon=1 indica que o segundo operando é o imediato (não B)
        state->sinal[ula_fon] = 1;
        state->ulaop = ADD;

        if      (state->ir.opcode == lw)   state->estado = MEM_READ;
        else if (state->ir.opcode == sw)   state->estado = MEM_WRITE;
        else if (state->ir.opcode == addi) state->estado = MEM_WRITEBACK;
        break;

    case MEM_READ:
        // leitura de memória 
        state->sinal[esc_mem] = 0;
        state->estado = MEM_WRITEBACK;
        break;

    case MEM_WRITE:
        // escrita em memória 
        state->sinal[esc_mem] = 1;
        state->estado = FETCH;
        break;

    case MEM_WRITEBACK:
        // escrita no banco de registradores no ultimo estagio
        state->sinal[esc_reg] = 1;
        state->estado = FETCH;
        break;

    case EXEC_R:
        // ULA opera com A e B 
        state->sinal[ula_fon] = 0;
        state->ulaop = (typ_ulaOp)state->ir.funct;
        state->estado = MEM_WRITEBACK;
        break;

    case BRANCH_COMP:
        // ula calcula A - B para verificar igualdade (zero flag)
        // a decisão de branch é tomada em executar.c após a ULA gerar o resultaod
        state->ulaop = SUB;
        state->estado = FETCH;
        break;

    case JUMP_COMP:
        //
        state->estado = FETCH;
        break;

    default:
        state->estado = FETCH;
        break;
    }

    return state;
}
