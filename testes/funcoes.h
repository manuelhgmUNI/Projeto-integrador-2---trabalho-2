#include"dcl_str_p2.h"

#ifndef funcoes_H
#define funcoes_H  

    // leitura de comandos bit a bit


    // ULA
    typ_ulaR ula(int A, int B, typ_ulaOp operacao);

    // controlador
    // typ_state *controlador(typ_state *state, int n);

    // banco de registradores
    void inicia_registradores(int8_t **banco);
    void escreve_registrador(int8_t **banco, int indice, int valor);
    int le_registrador(int8_t **banco, int indice);
    void imprime_registradores(int8_t **banco);
    void Banco_de_registradores(uint8_t rs, uint8_t rt, uint8_t rd, bool esc_reg, typ_state **state);


    // memoria de dados
    //int8_t mem_data(unsigned int endereco, int8_t D, bool str, bool ld, bool clear);
#endif