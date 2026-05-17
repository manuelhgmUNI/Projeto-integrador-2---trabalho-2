#include <stdio.h>
#include "dcl_str_p2.h"
#include "assinaturas.h"

void asm_gerador(typ_memoria_principal *mem, int n, char *nome_arq)
{
    FILE *arquivo = NULL;
    arquivo = fopen(nome_arq, "w");
    if (arquivo == NULL)
    {
        printf("erro ao abrir o arquivo");
        return;
    }

    for (int k = 0; k < n; k++)
    {
        uint16_t word = mem->palavras[k];
        typ_decoded_instruction instrucao = decode_instruction(word);

        if (instrucao.instrucao_bruta == 0) {
            fprintf(arquivo, "add $r0, $r0, $r0\n");
            continue; 
        }

        switch (instrucao.tipo)
        {
            case r: // Tipo R 
                switch(instrucao.funct)
                {
                    case ADD: fprintf(arquivo, "add "); break;
                    case SUB: fprintf(arquivo, "sub "); break;
                    case AND: fprintf(arquivo, "and "); break;
                    case OR:  fprintf(arquivo, "or ");  break;
                    default:  fprintf(arquivo, "??? "); break;
                }
                fprintf(arquivo, "$r%i, $r%i, $r%i\n", instrucao.rd, instrucao.rs, instrucao.rt);
            break;

            case i: // Tipo I
                switch (instrucao.opcode)
                {
                    case beq:  fprintf(arquivo, "beq ");  break;
                    case addi: fprintf(arquivo, "addi "); break;
                    case lw:   fprintf(arquivo, "lw ");   break;
                    case sw:   fprintf(arquivo, "sw ");   break;
                    default:   fprintf(arquivo, "??? ");  break;
                }
                fprintf(arquivo, "$r%i, $r%i, %i\n", instrucao.rs, instrucao.rt, instrucao.immediato);
            break;

            case j:
                fprintf(arquivo, "jump %i\n", instrucao.addr);
            break;

            default:
                fprintf(arquivo, "unknown\n");
            break;
        }
    }
    fclose(arquivo);
}

int asm_gerador_char(char *assembly, typ_decoded_instruction *instrucao)
{
    if (instrucao->instrucao_bruta == 0) {
        sprintf(assembly, "add $r0, $r0, $r0");
        return 0;
    }

    switch (instrucao->tipo)
    {
        case r:
            switch(instrucao->funct)
            {
                case ADD: sprintf(assembly, "add $r%d, $r%d, $r%d", instrucao->rd, instrucao->rs, instrucao->rt); break;
                case SUB: sprintf(assembly, "sub $r%d, $r%d, $r%d", instrucao->rd, instrucao->rs, instrucao->rt); break;
                case AND: sprintf(assembly, "and $r%d, $r%d, $r%d", instrucao->rd, instrucao->rs, instrucao->rt); break;
                case OR:  sprintf(assembly, "or $r%d, $r%d, $r%d",  instrucao->rd, instrucao->rs, instrucao->rt); break;
                default:  sprintf(assembly, "??? $r%d, $r%d, $r%d", instrucao->rd, instrucao->rs, instrucao->rt); break;
            }
            break;
        case i:
            if (instrucao->opcode == lw) {
                sprintf(assembly, "lw $r%d, %d($r%d)", instrucao->rt, instrucao->immediato, instrucao->rs);
            } else if (instrucao->opcode == sw) {
                sprintf(assembly, "sw $r%d, %d($r%d)", instrucao->rt, instrucao->immediato, instrucao->rs);
            } else if (instrucao->opcode == beq) {
                sprintf(assembly, "beq $r%d, $r%d, %d", instrucao->rs, instrucao->rt, instrucao->immediato);
            } else if (instrucao->opcode == addi) {
                sprintf(assembly, "addi $r%d, $r%d, %d", instrucao->rt, instrucao->rs, instrucao->immediato);
            } else {
                sprintf(assembly, "??? $r%d, $r%d, %d", instrucao->rs, instrucao->rt, instrucao->immediato);
            }
            break;
        case j:
            sprintf(assembly, "jump %d", instrucao->addr);
            break;
        default:
            sprintf(assembly, "Desconhecido");
            break;
    }
    return 0;
}

