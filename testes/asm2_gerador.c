#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dcl_str_p2.h"
#include "assinaturas.h"

int asm_gerador_char(char *asembly, typ_decoded_instruction *instrucao)
{

    if (instrucao->instrucao_bruta == 0) {
        sprintf(asembly, "add $r0, $r0, $r0\n");
        return 0;
    }
    switch ((*instrucao).tipo)
    {
        case r: // Tipo R 
            switch((*instrucao).funct)
            {
                case ADD:
                    sprintf(asembly, "add ");
                break;

                case SUB:
                    sprintf(asembly, "sub ");
                break;

                case AND:
                    sprintf(asembly, "and ");
                break;

                case OR:
                    sprintf(asembly, "or ");
                break;
            }
            sprintf(asembly + strlen(asembly), "$r%i, $r%i, $r%i\n", (*instrucao).rd, (*instrucao).rs, (*instrucao).rt);

        break;

        case i: // Tipo I
            switch ((*instrucao).opcode)
            {
            case beq:
                sprintf(asembly, "beq ");
            break;
                
            case addi:    
                sprintf(asembly, "addi ");
            break;    

            case lw:
                sprintf(asembly, "lw ");
            break;

            case sw:
                sprintf(asembly, "sw ");
            break;
            
            default:
                break;
            }
            sprintf(asembly + strlen(asembly), "$r%i, $r%i, %i\n", (*instrucao).rs, (*instrucao).rt, (*instrucao).immediato);
        break;

        case j:
            sprintf(asembly, "jump %i\n",(*instrucao).addr);
        break;
        default:
        break;
    }
    
    return 1; // Retorna 1 para indicar sucesso (adicionei caso a função precise de retorno)
}