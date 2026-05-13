#ifndef funcoes_H
#define funcoes_H

#include "dcl_str_p2.h"

    // leitura e conversao
    int carregar_memoria_unificada(typ_memoria_principal *mem_out);
    typ_decoded_instruction decode_instruction(uint16_t instruction_word);
   
    // ULA
    typ_ulaR ula(int A, int B, typ_ulaOp operacao);
    
    void controlador(typ_state *s);
    int caminho_de_dados(typ_state *s, bool clock, bool clear);
   
    // asm
    void asm_gerador(typ_memoria_principal *mem, int n, char *nome_arq);
    int asm_gerador_char(char *asembly, typ_decoded_instruction *instrucao);
   
    void inicia_registradores(typ_state *s);
    void imprime_registradores(typ_state *s);

    int executar(typ_state *s);

#endif
