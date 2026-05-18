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
    

    (**c).dados.mux_mem = mux((**c).registrador.PC, (**c).registrador.intermediario.ULA_saida, (**c).sinais[IouD]);
    
    //acesso a memoria memoria()
    (**c).dados.saida_mem = (**c).memoria.palavras[(**c).dados.mux_mem];


    // decodificação da instrução
    (**c).instrucao = decode_instruction((**c).registrador.intermediario.RI);
    // controle
    Unidade_de_Controle(c);

    // mux registrador destino 
    (**c).dados.mux_reg_dest = mux((**c).instrucao.rt, (**c).instrucao.rd, (**c).sinais[RegDst]);
    // mux valor a ser escrito no registrador
    (**c).dados.mux_mem_reg = mux((**c).dados.ULA_saida , (**c).registrador.intermediario.MDR, (**c).sinais[MemParaReg]);
    
    // banco de registradores
    Banco_de_registradores((**c).instrucao.rs, (**c).instrucao.rt, (**c).dados.mux_reg_dest, (**c).sinais[EscReg], c);

    // mux ula
    (**c).dados.mux_ulaA = mux((**c).registrador.PC, (**c).dados.A, (**c).sinais[UlaFonteA]); // mux entrada superior

    (**c).dados.mux_ulaB = mux((**c).dados.B, 1, (**c).sinais[UlaFonteB0]);
    (**c).dados.mux_ulaB = mux((**c).dados.mux_ulaB, (**c).instrucao.immediato, (**c).sinais[UlaFonteB1]); // mux ula entrada inferior
    
    
    // ula
    (**c).dados.ula.R = ula((**c).dados.mux_ulaA, (**c).dados.mux_ulaB ,(**c).dados.ula.Op );

    // fim do clock
    //______________________________________________________________________________________________
        if (clear)
        {
            (**c).registrador = (typ_all_reg) {0};
            (**c).dados = (typ_dados) {0};
            return 0;
        }

    

    // escrita na memoria
    if ((**c).sinais[EscMem])
        (**c).memoria.palavras[128+(**c).dados.mux_mem] = (**c).dados.B;

    // escrita nos intermediarios

    // RI
    if ((**c).sinais[IREsc])
        (**c).registrador.intermediario.RI = (**c).dados.saida_mem;
    

    // MDR
    (**c).registrador.intermediario.MDR = (**c).dados.saida_mem;

    // A
    (**c).registrador.intermediario.A = (**c).dados.rs;
    (**c).dados.A = (**c).registrador.intermediario.A;

    // B
    (**c).registrador.intermediario.B = (**c).dados.rt;
    (**c).dados.B = (**c).registrador.intermediario.B;

    // saida da ula
    (**c).registrador.intermediario.ULA_saida = (**c).dados.ula.R.resultado;
    (**c).dados.ULA_saida = (**c).registrador.intermediario.ULA_saida;

    // geração do sinal com or entre PCesc e o resuldado da and brench e zero ula
    if ( ((**c).sinais[PCEsc]) || ((**c).dados.ula.R.zero && (**c).sinais[Branch]) )
    {
        // escrita no pc
        (**c).registrador.PC = (**c).dados.ULA_saida;
    }

    // sinais de controle
    (**c).sinais[estado3] = (**c).prox_estado[PE3];
    (**c).sinais[estado2] = (**c).prox_estado[PE2];
    (**c).sinais[estado1] = (**c).prox_estado[PE1];
    (**c).sinais[estado0] = (**c).prox_estado[PE0];
    
    //______________________________________________________________________________________________

}

uint8_t mux(uint8_t A,uint8_t B,bool sinal)
{
    if (sinal == 0)
        return A;
    return B;
}
