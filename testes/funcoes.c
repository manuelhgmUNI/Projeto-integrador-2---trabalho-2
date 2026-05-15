#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assinaturas.h"


typedef struct no_pilha {
    typ_state         snapshot;
    struct no_pilha  *anterior;
} no_pilha;

static no_pilha *topo_pilha = NULL;
static int       profundidade = 0;

void backstep_push(const typ_state *s) {
    no_pilha *no = (no_pilha *)malloc(sizeof(no_pilha));
    if (!no) return;
    no->snapshot = *s;
    no->anterior = topo_pilha;
    topo_pilha   = no;
    profundidade++;
}

bool backstep_pop(typ_state *s) {
    if (!topo_pilha) return false;
    no_pilha *no = topo_pilha;
    *s = no->snapshot;
    topo_pilha = no->anterior;
    free(no);
    profundidade--;
    return true;
}

void backstep_libera(void) {
    while (topo_pilha) {
        no_pilha *no = topo_pilha;
        topo_pilha = no->anterior;
        free(no);
    }
    profundidade = 0;
}

int backstep_get_profundidade(void) {
    return profundidade;
}


void limpa_buff(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int conta_instrucoes(const typ_state *s) {
    int n = 0;
    for (int i = 0; i < 128; i++)
        if (s->memoria.palavras[i] != 0) n = i + 1;
    return n;
}

void imprime_mem_instrucoes(const typ_state *s, int num_instrucoes) {
    printf("\nMemoria de instrucoes (0-127):\n");
    for (int i = 0; i < 128; i++) {
        uint16_t w = s->memoria.palavras[i];
        typ_decoded_instruction dec = decode_instruction(w);
        char asm_buf[64] = {0};
        asm_gerador_char(asm_buf, &dec);
        printf("[%03d] Op:%-2d | %s\n", i, dec.opcode, asm_buf);
    }
}

void salva_binario(const typ_state *s, int num_instrucoes, const char *nome) {
    FILE *f = fopen(nome, "w");
    if (!f) return;
    for (int i = 0; i < num_instrucoes; i++) {
        uint16_t w = s->memoria.palavras[i];
        for (int b = 15; b >= 0; b--)
            fputc(((w >> b) & 1) ? '1' : '0', f);
        fputc('\n', f);
    }
    fclose(f);
}

void step_cycle(typ_state *s) {
    if (s->estado == FETCH) {
        s->instrucao = decode_instruction(s->memoria.palavras[s->registrador.PC]);
    }

    memset(s->sinais, 0, sizeof(s->sinais));
    decodifica_estado_para_sinais(s);
    controle(&s);
    caminho_de_dados(&s, false);
    estado_fsm proximo = calcula_proximo_estado(s->estado, s->instrucao.opcode);
    
    // Contabiliza instrução quando ela completa (transição para FETCH)
    if (proximo == FETCH && s->estado != FETCH && s->instrucao.instrucao_bruta != 0) {
        s->total_instrucoes++;
        
        // Classifica o tipo de instrução
        if (s->instrucao.tipo == r) {
            s->r_instrucoes++;
            // Conta NOPs (add $r0, $r0, $r0)
            if (s->instrucao.opcode == r_op && s->instrucao.rs == 0 && s->instrucao.rt == 0 && s->instrucao.rd == 0) {
                s->nop_instrucoes++;
            }
        } else if (s->instrucao.tipo == i) {
            s->i_instrucoes++;
        } else if (s->instrucao.tipo == j) {
            s->j_instrucoes++;
        }
    }
    
    atualiza_estado(s, proximo);
}

void run_completo(typ_state *s) {
    int limite = 100000;
    s->estado = FETCH;
    while (s->registrador.PC != 255 && limite-- > 0)
        step_cycle(s);
}