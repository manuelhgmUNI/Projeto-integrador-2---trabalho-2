#include <stdio.h>
#include <string.h>
#include "assinaturas.h"

void inicia_registradores(typ_state *s) {
    for(int i = 0; i < 8; i++) {
        s->registrador.banco[i] = 0;
    }
    s->registrador.PC = 0;
}

void escreve_registrador(int8_t *banco, int indice, int valor) {
    // Evitar escrever no registrador $0 (sempre 0 no MIPS)
    if(indice > 0 && indice < 8) {
        banco[indice] = (int8_t)valor;
    }
}

int le_registrador(int8_t *banco, int indice) {
    if(indice >= 0 && indice < 8) {
        return (int)banco[indice];
    }
    return 0; 
}

void imprime_registradores(typ_state *s) {
    /* converte RI para binário legível */
    uint16_t ri = s->registrador.intermediario.RI;
    char ri_bin[17];
    for (int b = 15; b >= 0; b--)
        ri_bin[15 - b] = ((ri >> b) & 1) ? '1' : '0';
    ri_bin[16] = '\0';

    /* decodifica RI para mostrar a instrução atual */
    char asm_ri[64] = {0};
    typ_decoded_instruction dec = decode_instruction(ri);
    asm_gerador_char(asm_ri, &dec);
    asm_ri[strcspn(asm_ri, "\n")] = '\0';

    printf("\n+-------[ Registradores ]--------------------------------+\n");
    printf("| PC     : %d\n", s->registrador.PC);
    printf("| IR     : %s  (%s)\n", ri_bin, asm_ri);
    printf("| MDR    : %d\n", (int16_t)s->registrador.intermediario.RDM);
    printf("| A      : %d\n", s->registrador.intermediario.A);
    printf("| B      : %d\n", s->registrador.intermediario.B);
    printf("| ALUOut : %d\n", s->registrador.intermediario.ALUOut);
    printf("+--------------------------------------------------------+\n");
    printf("| Banco de Registradores:                                |\n");
    for (int i = 0; i < 8; i++) {
        printf("|   $r%d = %d\n", i, s->registrador.banco[i]);
    }
    printf("+--------------------------------------------------------+\n");
}

void Banco_de_registradores(typ_state *s) {
    
    s->caminhos.rs_val = s->registrador.banco[s->ir_decoded.rs];
    s->caminhos.rt_val = s->registrador.banco[s->ir_decoded.rt];
    
    
    if (s->sinais[EscReg]) {
        escreve_registrador(s->registrador.banco, s->caminhos.mux_reg_dest, s->caminhos.mux_mem_reg);
    }
}
