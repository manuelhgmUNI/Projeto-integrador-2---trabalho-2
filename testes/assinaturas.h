#ifndef assinaturas_H
#define assinaturas_H

#include "dcl_str_p2.h"

    
    int carregar_memoria_unificada(typ_memoria_principal *mem);
    
    
    typ_decoded_instruction decode_instruction(uint16_t instruction_word);
   
    // ULA
    typ_ulaR ula(int A, int B, typ_ulaOp operacao);
    typ_ulaOp controle_ula(bool c1, bool c2, bool c3, uint8_t funct);
    
    // Controle e Datapath
    void controle(typ_state **c);
    void decodifica_estado_para_sinais(typ_state *s);
    void step_cycle(typ_state *s);
    estado_fsm calcula_proximo_estado(estado_fsm estado_atual, uint16_t opcode);
    void atualiza_estado(typ_state *s, estado_fsm proximo);
    int caminho_de_dados(typ_state **c, bool clear);
    
    // Banco de Registradores
    void inicia_registradores(typ_state *s);
    void escreve_registrador(int8_t *banco, int indice, int valor);
    int le_registrador(int8_t *banco, int indice);
    void imprime_registradores(typ_state *s);
    void Banco_de_registradores(uint16_t rs, uint16_t rt, uint8_t dest, bool escreve, typ_state **c);

    // mux
    uint8_t mux(uint8_t A, uint8_t B, bool sinal);


    int asm_gerador_char(char *asembly, typ_decoded_instruction *instrucao);
    void asm_gerador(typ_memoria_principal *mem, int n, char *nome_arq);

    void backstep_push(const typ_state *s);
    bool backstep_pop(typ_state *s);
    void backstep_libera(void);
    int  backstep_get_profundidade(void);


    void limpa_buff(void);
    void imprime_mem_instrucoes(const typ_state *s, int num_instrucoes);
    void imprime_mem_dados(const typ_state *s);
    int  conta_instrucoes(const typ_state *s);

    
    void salva_binario(const typ_state *s, int num_instrucoes, const char *nome);
    void salva_dat(const typ_state *s, const char *nome);
    void carrega_dat(typ_state *s, const char *nome);

    void run_completo(typ_state *s);

#endif
