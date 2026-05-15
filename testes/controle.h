#include "dcl_str_p2.h"

#ifndef controle_H
#define controle_H




void Unidade_de_Controle(typ_state **C);
void Controle_sinais(typ_state **c);
void controle_ula_fonte(typ_state **c);
void controle_pc_fonte(typ_state **c);
estado_fsm calcula_proximo_estado(estado_fsm estado_atual, uint16_t opcode);
void decodifica_estado_para_sinais(typ_state *s);
void decodifica_sinais_para_estado(typ_state *s);



#endif