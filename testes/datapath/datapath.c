#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include"dcl_str_p2.h"

int main() // usado para fins de testes somente
{

}
void controle(typ_state **c); // somente para testes
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

    // controle
    // banco de registradores
    //

    //______________________________________________________________________________________________
    // escrita nos intermediaros A e B
    //______________________________________________________________________________________________

    
    (**c).dados.mux_ulaA = mux((**c).dados.PC, (**c).dados.A, (**c).sinais[UlaFonteA]); // mux entrada superior

    (**c).dados.mux_ulaB = mux((**c).dados.B, 1, (**c).sinais[UlaFonteB0]);
    (**c).dados.mux_ulaB = mux((**c).dados.mux_ulaB, /*imediato*/ 0 , (**c).sinais[UlaFonteB1]); // mux ula entrada inferior
    
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
void controle(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];

    (**c).sinais[Branch] = e0 && e3;

    (**c).sinais[PCEsc] = (( (!e3 && !e2) && (!e1 && !e0) ) || (e3 && e1));

    (**c).sinais[IouD] = (((!e2 && e1) && e0) || ((e2 && !e1) && e0));

    (**c).sinais[EscMem] = ((e2 && !e1) && e0);

    (**c).sinais[IREsc] = ((!e3 && !e2) && (!e1 && !e0));

    (**c).sinais[MemParaReg] = ((e2 && !e1) && !e0);

    (**c).sinais[RegDst] = ( ( ( (!e3 && !e2) & !e1 ) || ( (!e3 && e2) && (e1 && e0) ) ) || ( (e3 && !e1) && !e0) );

    (**c).sinais[EscReg] = ( (e2 && !e0) || ( (e3 && !e1) && !e0) );

}