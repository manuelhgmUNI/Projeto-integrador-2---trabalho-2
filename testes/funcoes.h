#ifndef funcoes_H
#define funcoes_H

#include "structs.h"

    // leitura de comandos bit a bit
    int carregar_memoria_unificada(typ_memoria_principal **mem_out);
    typ_decoded_instruction decode_instruction(uint16_t instruction_word);
   
    // ula
    typ_ulaR ula(int A, int B, typ_ulaOp operacao);
    
    // controlador (n testei :))
    typ_stt *controlador(typ_stt *state);
   
    void asm_gerador(typ_memoria_principal *mem, int n, char *nome_arq);
    int asm_gerador_char(char *asembly, typ_ins *instrucao);
   
    // banco de registradores
    void inicia_registradores(BancoRegistradores *banco);
    void escreve_registrador(BancoRegistradores *banco, int indice, int valor);
    int le_registrador(BancoRegistradores *banco, int indice);
    void imprime_registradores(BancoRegistradores *banco);

    // execução (recebe o estado)
    int executar(typ_stt *status);

#endif
