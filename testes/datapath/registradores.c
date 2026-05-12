#include <stdio.h>
#include "dcl_str_p2.h"

void inicia_registradores(int8_t *banco) {
    int i;
    for(i = 0; i < 8; i++) {
        (banco)[i] = 0;
    }
}
void escreve_registrador(int8_t *banco, int indice, int valor) {
    //evitar escrever no 0
    if(indice > 0 && indice < 8) {
        (banco)[indice] = (int8_t)valor;
    }
}

int le_registrador(int8_t *banco, int indice) {
    if(indice >= 0 && indice < 8) {
        return (int)(banco)[indice];
    }
    return 0; 
}

void imprime_registradores(int8_t **banco) {
    int i;
    printf("\nBanco de Registradores\n");
    for(i = 0; i < 8; i++) {
        printf("$%d: %4d\n", i, (*banco)[i]);
    }
}

void Banco_de_registradores(uint8_t rs, uint8_t rt, uint8_t rd, bool esc_reg, typ_state **state)
{
    (**state).dados.rs = (**state).registrador.banco[rs];
    (**state).dados.rt = (**state).registrador.banco[rt];
    
    if (esc_reg)
        escreve_registrador((**state).registrador.banco, rd, (**state).dados.mux_reg_dest);
}
