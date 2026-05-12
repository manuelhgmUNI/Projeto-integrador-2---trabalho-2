#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include"dcl_str_p2.h"
#include"funcoes.h"

void controle(typ_state **c); // somente para testes
int main() // usado para fins de testes somente
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
}

uint8_t mux(uint8_t A,uint8_t B,bool sinal);
int caminho_de_dados(typ_state **c, bool clear)
{
    // geração do sinal com or entre PCesc e o resuldado da and brench e zero ula
    if ( ((**c).sinais[PCEsc]) || ((**c).dados.ula.R.zero && (**c).sinais[Branch]) )
    {
        // escrita no pc
        (**c).registrador.PC = (**c).dados.ULA_saida;
    }

    (**c).dados.mux_mem = mux((**c).registrador.PC, (**c).registrador.intermediario.ULA_saida, (**c).sinais[IouD]);
    
    
    //acesso a memoria memoria()


    // controle
    controle(c);

    // mux registrador destino 
    (**c).dados.mux_reg_dest = mux((**c).instrucao.rt, (**c).instrucao.rd, (**c).sinais[RegDst]);
    // mux valor a ser escrito no registrador
    (**c).dados.mux_mem_reg = mux((**c).dados.ULA_saida , (**c).registrador.intermediario.RDM, (**c).sinais[MemParaReg]);
    
    // banco de registradores
    Banco_de_registradores((**c).instrucao.rs, (**c).instrucao.rt, (**c).dados.mux_reg_dest, (**c).sinais[EscReg], c);

    // mux ula
    (**c).dados.mux_ulaA = mux((**c).registrador.PC, (**c).dados.A, (**c).sinais[UlaFonteA]); // mux entrada superior

    (**c).dados.mux_ulaB = mux((**c).dados.B, 1, (**c).sinais[UlaFonteB0]);
    (**c).dados.mux_ulaB = mux((**c).dados.mux_ulaB, (**c).instrucao.immediato, (**c).sinais[UlaFonteB1]); // mux ula entrada inferior
    
    
    // ula
    (**c).dados.ula.R = ula((**c).dados.A, (**c).dados.B ,(**c).dados.ula.Op );

    // fim do clock
    //______________________________________________________________________________________________
        if (clear)
        {
            (**c).registrador = (typ_all_reg) {0};
            (**c).dados = (typ_dados) {0};
        }

    // escrita nos intermediarios

    // RI
    if ((**c).sinais[IREsc])
        (**c).registrador.intermediario.RI = (**c).dados.saida_mem;
    

    // MDR
    (**c).registrador.intermediario.RDM = (**c).dados.saida_mem;

    // A
    (**c).registrador.intermediario.A = (**c).dados.rs;
    (**c).dados.A = (**c).registrador.intermediario.A;

    // B
    (**c).registrador.intermediario.B = (**c).dados.rt;
    (**c).dados.B = (**c).registrador.intermediario.B;

    // saida da ula
    (**c).registrador.intermediario.ULA_saida = (**c).dados.ula.R.resultado;
    (**c).dados.ULA_saida = (**c).registrador.intermediario.ULA_saida;

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