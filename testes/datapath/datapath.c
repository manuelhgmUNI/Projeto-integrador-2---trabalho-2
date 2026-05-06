#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include"dcl_str_p2.h"

int main() // usado para fins de testes somente
{

}
uint8_t mux(uint8_t A,uint8_t B,bool sinal);
int caminho_de_dados(typ_state **c, bool clock, bool clear)
{
    // geração do sinal com or entre PCesc e o resuldado da and brench e zero ula
    // escrita no PC

    (**c).dados.mux_mem = mux((**c).registrador.PC, (**c).registrador.intermediario.ULA_saida, (**c).sinais[IouD]);
    //acesso a memoria memoria()
    
    //______________________________________________________________________________________________
    // escrita nos intermediarios RD e MDR
    //______________________________________________________________________________________________

    //controle
    //banco de registradores
    //

    //______________________________________________________________________________________________
    // escrita nos intermediaros A e B
    //______________________________________________________________________________________________

    
    (**c).dados.mux_ulaA = mux((**c).dados.PC, (**c).dados.A, (**c).sinais[UlaFonteA]);

    (**c).dados.mux_ulaB = mux((**c).dados.B, 1, (**c).sinais[UlaFonteB0]);
    (**c).dados.mux_ulaB = mux((**c).dados.mux_ulaB, /*imediato*/ 0 , (**c).sinais[UlaFonteB1]);
    
    // ula


    //______________________________________________________________________________________________
    // escrita na saida da ula
    //______________________________________________________________________________________________


}

uint8_t mux(uint8_t A,uint8_t B,bool sinal)
{
    if (sinal == 0)
        return A;
    return B;
}