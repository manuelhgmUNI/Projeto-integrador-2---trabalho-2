#include "dcl_str_p2.h"

void escreve_pc(typ_state **state, uint8_t valor)
{
    (**state).registrador.PC = valor;
}

void incrementar_pc(typ_state **state)
{
    (**state).registrador.PC = (**state).dados.ULA_saida;
}
