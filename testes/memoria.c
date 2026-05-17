#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "assinaturas.h"

int carregar_memoria_unificada(typ_memoria_principal *mem)
{
    char nome_arquivo[25];
    printf("Nome do arquivo .mem: ");
    if (scanf("%24s", nome_arquivo) != 1) return 0;

    FILE *Mem_ins = fopen(nome_arquivo, "r");
    if (Mem_ins == NULL) {
        printf("Erro ao abrir '%s'.\n", nome_arquivo);
        return 0;
    }

    memset(mem->palavras, 0, sizeof(mem->palavras));

    char buffer[50];
    int addr_inst = 0;
    int addr_data = 128;
    int lendo_dados = 0;

    while (fgets(buffer, sizeof(buffer), Mem_ins) != NULL) {
        
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strlen(buffer) == 0) continue;

        if (strcmp(buffer, ".data") == 0) {
            lendo_dados = 1;
            continue;
        }

        int end_explicit;
        char bin_str[20];
        
        if (sscanf(buffer, "%d %s", &end_explicit, bin_str) == 2) {
            mem->palavras[end_explicit] = (uint16_t) strtol(bin_str, NULL, 2);
        } else {
            uint16_t val = (uint16_t) strtol(buffer, NULL, 2);
            if (!lendo_dados && addr_inst < 128) {
                mem->palavras[addr_inst++] = val;
            } else if (lendo_dados && addr_data < 256) {
                mem->palavras[addr_data++] = val;
            }
        }
    }

    fclose(Mem_ins);
    return 256; 
}
