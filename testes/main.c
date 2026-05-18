#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dcl_str_p2.h"
#include "assinaturas.h"

static const char *ula_descricao(estado_fsm estado, uint16_t opcode) {
    switch (estado) {
        case FETCH:
            return "PC+1";
        case DECODE:
            switch (opcode) {
                case beq: return "PC+offset";
                case j_op: return "jump addr";
                default: return "nao usado";
            }
        case MEM_ADDR:
        case MEM_WRITE:
            return "base+offset";
        case MEM_WRITEBACK:
            return "load data";
        case EXEC_I:
            return "addi";
        case EXEC_R:
            return "r-type";
        case BRANCH_COMP:
            return "compare";
        case JUMP_COMP:
            return "jump";
        default:
            return "ULA";
    }
}

int main(void) {
    int menu = 0;
    typ_state *estado;
    estado = calloc(1, sizeof(typ_state));

    const char *fsm_nomes[] = {"FETCH", "DECODE", "MEM_ADDR", "MEM_READ", "MEM_WRITEBACK", "MEM_WRITE", "EXEC_I", "EXEC_R", "REG_WRITEBACK", "BRANCH_COMP", "JUMP_COMP"};
    int num_instrucoes = 0;

    do {
        printf("\n   -=|| MIPS UNIPAMPA ||=-   \n");
        printf(" PC: %d | Estado Atual: %s | Instrucoes Carregadas: %d | Backstep: %d\n", 
               estado->registrador.PC, fsm_nomes[(int)estado->estado], num_instrucoes, backstep_get_profundidade());
        printf("+------+----------------------------------------------------+\n");
        printf("| [1]  | Carregar memoria unificada (.mem)                  |\n");
        printf("| [2]  | Imprimir memorias (instrucoes e dados)             |\n");
        printf("| [3]  | Imprimir banco de registradores                    |\n");
        printf("| [4]  | Imprimir estado completo (memoria + registradores) |\n");
        printf("| [5]  | Salvar binario                                     |\n");
        printf("| [6]  | Salvar memoria unificada (.mem)                    |\n");
        printf("| [7]  | Executar Programa (Run)                            |\n");
        printf("| [8]  | Executar uma instrucao (Step)                      |\n");
        printf("| [9]  | Voltar uma instrucao (Back)                        |\n");
        printf("| [10] | Gerar estatisticas                                 |\n");
        printf("| [11] | Gerar .asm                                         |\n");
        printf("| [0]  | Reset                                              |\n");
        printf("| [123]| Sair                                               |\n");
        printf("+------+----------------------------------------------------+\n");
        printf("Entrada: ");

        if (scanf("%i", &menu) != 1) {
            limpa_buff();
            continue;
        }
        limpa_buff();

        switch (menu) {
            case 1:
                backstep_libera();
                carregar_memoria_unificada(&estado->memoria);
                num_instrucoes = conta_instrucoes(estado);
                estado->registrador.PC = 0;
                estado->estado = FETCH;
                break;

            case 2: 
                imprime_mem_instrucoes(estado, num_instrucoes);
                printf("\nMemoria de dados (128-255):\n");
                for (int i = 128; i < 256; i++) {
                    
                        printf("[%03d] = %d\n", i, (int16_t)estado->memoria.palavras[i]);
                    
                }
                break;


            case 3:
                imprime_registradores(estado);
                break;

            case 4:
                printf("\n--- ESTADO COMPLETO ---\n");
                imprime_registradores(estado);
                printf("\nMemoria de dados (128-255):\n");
                for (int i = 128; i < 256; i++) {
                    if (estado->memoria.palavras[i] != 0) {
                        printf("[%03d] = %d\n", i, (int16_t)estado->memoria.palavras[i]);
                    }
                }
                printf("\n");

                break;

            case 5:{
                char buffer[25];
                printf("Nome do arquivo de saida: ");
                if (scanf("%24s", buffer) == 1) {
                    FILE *f = fopen(buffer, "w");
                    if (f) {
                        for (int i = 0; i < num_instrucoes; i++) {
                            typ_decoded_instruction dec = decode_instruction(estado->memoria.palavras[i]);
                            fprintf(f, "%s\n", dec.total);
                        }
                        fclose(f);
                        printf("Arquivo binario salvo: %s\n", buffer);
                    } else printf("Erro ao criar %s\n", buffer);
                }
                limpa_buff();
                break;
            }

            case 6: {
                char nome_dat[25];
                printf("Nome do arquivo de saida .dat: ");
                if (scanf("%24s", nome_dat) == 1) {
                    FILE *f = fopen(nome_dat, "w");
                    if (f) {
                        for (int i = 128; i < 256; i++) {
                            fprintf(f, "%d\n", (int16_t)estado->memoria.palavras[i]);
                        }
                        fclose(f);
                        printf("Arquivo .dat salvo: %s\n", nome_dat);
                    } else printf("Erro ao criar %s\n", nome_dat);
                }
                limpa_buff();
                break;
            }

            case 7:  // run
                printf("Executando programa...\n");
                do {
                    caminho_de_dados(&estado, false);
                } while (estado->registrador.PC < num_instrucoes );
                
                // Reseta PC para 0 quando execução termina
                estado->registrador.PC = 0;
                
                imprime_registradores(estado);
                printf("Execucao finalizada. PC: %d\n", estado->registrador.PC);
                break;


            case 8: { // step
                backstep_push(estado); // Salva o estado atual ANTES de executar o ciclo

                int pc_antes = estado->registrador.PC;
                estado_fsm estado_fsm_antes = estado->estado;

                char linha_asm[64] = {0};
                typ_decoded_instruction dec;
                if (estado->estado == FETCH) {
                    dec = decode_instruction(estado->memoria.palavras[pc_antes]);
                } else {
                    dec = estado->instrucao;
                }
                if (dec.instrucao_bruta == 0) {
                    sprintf(linha_asm, "add $r0, $r0, $r0  ");
                } else {
                    asm_gerador_char(linha_asm, &dec);
                    linha_asm[strcspn(linha_asm, "\n")] = '\0';
                }

                printf("\n+--[ STEP ]------------------------------------------+\n");
                printf("| PC Atual: %-3d | Estado Atual: %-15s / %i |\n", pc_antes, fsm_nomes[(int)estado_fsm_antes], estado->estado);
                printf("| ASM: %-45s |\n", linha_asm);
                printf("+----------------------------------------------------+\n");

                int8_t reg_antes[8];
                for (int i = 0; i < 8; i++) reg_antes[i] = estado->registrador.banco[i];

                caminho_de_dados(&estado, false);

                const char *ula_desc = ula_descricao(estado_fsm_antes, dec.opcode);
                printf("| ULA (%s) -> resultado: %-4d | zero: %s | overflow: %s  |\n",
                       ula_desc,
                       estado->dados.ula.R.resultado,
                       estado->dados.ula.R.zero     ? "sim" : "nao",
                       estado->dados.ula.R.overflow ? "sim" : "nao");

                printf("| PC: %d -> %d  (Prox Estado: %s)\n", pc_antes, estado->registrador.PC, fsm_nomes[(int)estado->estado]);
                printf("+----------------------------------------------------+\n");

                printf("| Registradores alterados:                           |\n");
                bool algum = false;
                for (int i = 0; i < 8; i++) {
                    if (estado->registrador.banco[i] != reg_antes[i]) {
                        printf("|   $r%d: %d -> %d\n", i, reg_antes[i], estado->registrador.banco[i]);
                        algum = true;
                    }
                }
                if (!algum) printf("|   (nenhum)\n");
                printf("+----------------------------------------------------+\n");

                break;
            }

            case 9: // backstep totalmente corrigido!
                if (backstep_pop(estado)) {
                    printf("\n>>> Backstep executado! Memoria, banco e PC restaurados. <<<\n");
                    printf("Restaurado para PC=%d, Estado=%s\n", estado->registrador.PC, fsm_nomes[(int)estado->estado]);
                    imprime_registradores(estado);
                } else {
                    printf("Pilha do backstep vazia! Nao ha instrucao anterior para voltar.\n");
                }
                break;


            case 10: 
                printf("\n--- ESTATISTICAS ---\n");
                printf("Total de instrucoes completas: %d\n", estado->total_instrucoes);
                printf("Tipo R: %i\n", estado->r_instrucoes);
                printf("Tipo I: %i\n", estado->i_instrucoes);
                printf("Tipo J: %i\n", estado->j_instrucoes);
                printf("Somas 0 (NOPs): %i\n", estado->nop_instrucoes);
                break;

            case 11: {
                char nome_arq[25];
                printf("Digite o nome do arquivo a ser gerado (ex: meu_codigo.asm): ");
                if (scanf("%24s", nome_arq) == 1) {
                    printf("Gerando...\n");
                    asm_gerador(&estado->memoria, num_instrucoes, nome_arq);
                    printf("Arquivo .asm pronto\n");
                }
                limpa_buff();
                break;
            }

            case 0:
                *estado = (typ_state) {0};
                inicia_registradores(estado);
                backstep_libera();
                num_instrucoes = 0;
                printf("Simulador resetado com sucesso!\n");
                break;

            case 123:
                printf("Saindo do simulador...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (menu != 123);

    backstep_libera(); // limpa memória na saída
    return 0;
}