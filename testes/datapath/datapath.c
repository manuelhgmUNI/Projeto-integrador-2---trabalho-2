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

    mux((**c).registrador.PC, (**c).registrador.intermediario.ULA_saida, (**c).sinais[IouD]);
    //acesso a memoria memoria()

    // escrita nos intermediarios RD e MDR

    //controle
    //banco de registradores
    //
}

uint8_t mux(uint8_t A,uint8_t B,bool sinal)
{
    if (sinal == 0)
        return A;
    return B;
}