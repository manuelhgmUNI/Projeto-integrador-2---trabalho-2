#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include"dcl_str_p2.h"
#include"assinaturas.h"

int caminho_de_dados(typ_state **c, bool clear);
/*
int main() // usado para fins de testes somente
{
    typ_state *c = calloc(1, sizeof(typ_state));
    
    
    for (int i = 0 ; i < 10; i++)
    caminho_de_dados(&c, 0);
    
    
    
    free(c);
}
*/

uint8_t mux(uint8_t A,uint8_t B,bool sinal);
int caminho_de_dados(typ_state **c, bool clear)
{
    // Mux mem (IouD)
    (**c).dados.mux_mem = mux((**c).registrador.PC, (**c).registrador.intermediario.ULA_saida, (**c).sinais[IouD]);
    
    // Acesso memoria
    (**c).dados.saida_mem = (**c).memoria.palavras[(**c).dados.mux_mem];

    // decodificacao baseado no ir atual
    (**c).instrucao = decode_instruction((**c).registrador.intermediario.RI);

    
    Unidade_de_Controle(c);

    // leitura (rs, rt)
    (**c).dados.rs = (**c).registrador.banco[(**c).instrucao.rs];
    (**c).dados.rt = (**c).registrador.banco[(**c).instrucao.rt];

    //muxed da ULA
    (**c).dados.mux_ulaA = mux((**c).registrador.PC, (**c).registrador.intermediario.A, (**c).sinais[UlaFonteA]);

    // mux ULA B
    uint8_t muxB_temp = mux((**c).registrador.intermediario.B, 1, (**c).sinais[UlaFonteB0]);
    (**c).dados.mux_ulaB = mux(muxB_temp, (**c).instrucao.immediato, (**c).sinais[UlaFonteB1]);
    
    //ULA
    (**c).dados.ula.R = ula((**c).dados.mux_ulaA, (**c).dados.mux_ulaB, (**c).dados.ula.Op);

    // mux(RegDst)
    (**c).dados.mux_reg_dest = mux((**c).instrucao.rt, (**c).instrucao.rd, (**c).sinais[RegDst]);
    
    //(MemParaReg)
    (**c).dados.mux_mem_reg = mux((**c).registrador.intermediario.ULA_saida, (**c).registrador.intermediario.MDR, (**c).sinais[MemParaReg]);
    
    // escrita (ocorre se EscReg for alto)
    if ((**c).sinais[EscReg]) {
        escreve_registrador((**c).registrador.banco, (**c).dados.mux_reg_dest, (**c).dados.mux_mem_reg);
    }

    if (clear) {
        (**c).registrador = (typ_all_reg) {0};
        (**c).dados = (typ_dados) {0};
        return 0;
    }

    // ---(Borda de Clock) ---

    // escrit memoria
    if ((**c).sinais[EscMem]) {
        
        (**c).memoria.palavras[(**c).dados.mux_mem] = (**c).registrador.intermediario.B;
    }

    // RI 
    if ((**c).sinais[IREsc]) {
        (**c).registrador.intermediario.RI = (**c).dados.saida_mem;
        
        (**c).instrucao = decode_instruction((**c).dados.saida_mem);
    }

    // MDR 
    (**c).registrador.intermediario.MDR = (**c).dados.saida_mem;

    // A e B
    (**c).registrador.intermediario.A = (**c).dados.rs;
    (**c).registrador.intermediario.B = (**c).dados.rt;

    // ALUOut 
    (**c).registrador.intermediario.ULA_saida = (**c).dados.ula.R.resultado;

    // att pc
    bool pc_cond = (**c).sinais[Branch] && (**c).dados.ula.R.zero;
    if ((**c).sinais[PCEsc] || pc_cond) {
        // Mux PCFonte
        // 00: Resultado da ULA (PC+1)
        // 01: ALUOut (Endereço de Branch)
        // 10: Jump Address
        if ((**c).sinais[PCFonte1] == 0 && (**c).sinais[PCFonte0] == 0) {
            (**c).registrador.PC = (**c).dados.ula.R.resultado;
        } else if ((**c).sinais[PCFonte1] == 0 && (**c).sinais[PCFonte0] == 1) {
            (**c).registrador.PC = (**c).registrador.intermediario.ULA_saida;
        } else if ((**c).sinais[PCFonte1] == 1 && (**c).sinais[PCFonte0] == 0) {
            (**c).registrador.PC = (**c).instrucao.addr;
        }
    }

    // att do estado
    (**c).estado = (**c).prox_estado_fsm;


    (**c).sinais[estado3] = (**c).prox_estado[PE3];
    (**c).sinais[estado2] = (**c).prox_estado[PE2];
    (**c).sinais[estado1] = (**c).prox_estado[PE1];
    (**c).sinais[estado0] = (**c).prox_estado[PE0];

    return 0;
}

uint8_t mux(uint8_t A,uint8_t B,bool sinal)
{
    if (sinal == 0)
        return A;
    return B;
}
