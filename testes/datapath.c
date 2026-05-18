#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include"dcl_str_p2.h"
#include"controle.h"
#include"assinaturas.h"


/*int main() // usado para fins de testes somente
{
    typ_state *c = calloc(1, sizeof(typ_state));

    //controle(&c);

    (*c).sinais[estado3] = 0;
    (*c).sinais[estado2] = 0;
    (*c).sinais[estado1] = 0;
    (*c).sinais[estado0] = 0;

    caminho_de_dados(&c, 0);

    (*c).sinais[estado3] = 0;
    (*c).sinais[estado2] = 0;
    (*c).sinais[estado1] = 0;
    (*c).sinais[estado0] = 1;

    caminho_de_dados(&c, 0);

    (*c).sinais[estado3] = 0;
    (*c).sinais[estado2] = 1;
    (*c).sinais[estado1] = 1;
    (*c).sinais[estado0] = 1;

    caminho_de_dados(&c, 0);

    (*c).sinais[estado3] = 1;
    (*c).sinais[estado2] = 0;
    (*c).sinais[estado1] = 0;
    (*c).sinais[estado0] = 0;


    free(c);
}*/

uint8_t mux(uint8_t A,uint8_t B,bool sinal);
uint8_t mux(uint8_t A,uint8_t B,bool sinal);
int caminho_de_dados(typ_state **c, bool clear)
{

    // Mux da Memória (IouD)
    (**c).dados.mux_mem = mux((**c).registrador.PC, (**c).registrador.intermediario.ULA_saida, (**c).sinais[IouD]);

    // Mux ULA A
    (**c).dados.mux_ulaA = mux((**c).registrador.PC, (**c).registrador.intermediario.A, (**c).sinais[UlaFonteA]);

    // Mux ULA B
    int valor_B;
    if ((**c).sinais[UlaFonteB1] == 0 && (**c).sinais[UlaFonteB0] == 0) valor_B = (**c).registrador.intermediario.B;
    else if ((**c).sinais[UlaFonteB1] == 0 && (**c).sinais[UlaFonteB0] == 1) valor_B = 1; // Para PC + 1
    else valor_B = (**c).instrucao.immediato;

    (**c).dados.mux_ulaB = valor_B;

    // ula
    (**c).dados.ula.Op = controle_ula((**c).sinais[ControleUla1], (**c).sinais[ControleUla2], (**c).sinais[ControleUla3], (**c).instrucao.funct);
    (**c).dados.ula.R = ula((**c).dados.mux_ulaA, (**c).dados.mux_ulaB, (**c).dados.ula.Op);

    bool branch_taken = ((**c).sinais[Branch] && (**c).dados.ula.R.zero);
    if ((**c).sinais[PCEsc] || branch_taken || ((**c).estado == JUMP_COMP))
    {
        if ((**c).sinais[PCEsc]) {
            (**c).registrador.PC = (**c).dados.ula.R.resultado;
        } else if (branch_taken) {
            (**c).registrador.PC = (**c).registrador.intermediario.ULA_saida;
        } else {
            (**c).registrador.PC = (**c).instrucao.addr;
        }
    }

    // acesso memoria
    (**c).dados.saida_mem = (**c).memoria.palavras[(**c).dados.mux_mem];

    if ((**c).sinais[EscMem])
        (**c).memoria.palavras[(**c).dados.mux_mem] = (**c).registrador.intermediario.B;

    // registradores
    (**c).dados.mux_reg_dest = mux((**c).instrucao.rt, (**c).instrucao.rd, (**c).sinais[RegDst]);
    (**c).dados.mux_mem_reg = mux((**c).dados.ula.R.resultado, (**c).registrador.intermediario.MDR, (**c).sinais[MemParaReg]);

    Banco_de_registradores((**c).instrucao.rs, (**c).instrucao.rt, (**c).dados.mux_reg_dest, (**c).sinais[EscReg], c);

    //prepara os valores p proximo ciclo

    if ((**c).sinais[IREsc])
        (**c).registrador.intermediario.RI = (**c).dados.saida_mem;

    (**c).registrador.intermediario.MDR = (**c).dados.saida_mem;
    (**c).registrador.intermediario.A = le_registrador((**c).registrador.banco, (**c).instrucao.rs);
    (**c).registrador.intermediario.B = le_registrador((**c).registrador.banco, (**c).instrucao.rt);
    (**c).registrador.intermediario.ULA_saida = (**c).dados.ula.R.resultado;

    if (clear) {
        (**c).registrador = (typ_all_reg) {0};
        (**c).dados = (typ_dados) {0};
    }

    return 1;

}

uint8_t mux(uint8_t A,uint8_t B,bool sinal)
{
    if (sinal == 0)
        return A;
    return B;
}
