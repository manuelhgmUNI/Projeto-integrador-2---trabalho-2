#include "dcl_str_p2.h"
#include "assinaturas.h"

void Unidade_de_Controle(typ_state **c)
{

    /*
    Controle_sinais(c);
    controle_pc_fonte(c);
    controle_ula_fonte(c);
    controle_ula(c);
    */

    switch ((**c).estado)
    {
    case 0:
        (**c).sinais[PCEsc]      = 1;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 1;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1;
        (**c).sinais[UlaFonteA]  = 0;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 1;
        (**c).sinais[Branch]     = 0;
        (**c).prox_estado        = 1; 
   
    break;
    
    case 1:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 0;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 1;
        (**c).sinais[Branch]     = 0;
        switch ((**c).instrucao.opcode)
        {
        case lw:
            (**c).prox_estado        = 2;
        break;

        case sw:
            (**c).prox_estado        = 2;
        break;

        case addi:
            (**c).prox_estado        = 2;
        break;

        case r_op:
            (**c).prox_estado        = 7;
        break;

        case beq:
            (**c).prox_estado        = 9;
        break;

        case j_op:
            (**c).prox_estado        = 3;
        break;
        }
    break;
    
    case 2:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 0;
        switch ((**c).instrucao.opcode)
        {
        case lw:
            (**c).prox_estado        = 3;
        break;
        
        case sw:
            (**c).prox_estado        = 5;
        break;

        case addi:
            (**c).prox_estado        = 6;
        break;
        }
    break;
    
    case 3:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 1;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 4;
    break;
    
    case 4:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 1;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 1;
        (**c).sinais[EscReg]     = 1;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 0;
    break;
    
    case 5:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 1;
        (**c).sinais[EscMem]     = 1;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 0; 

    break;
    
    case 6:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 1;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = 0;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 0; 

    break;
    
    case 7:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = (**c).instrucao.funct;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 1;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 8; 

    break;
    
    case 8:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 1;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = (**c).instrucao.funct;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 1;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 0;
    break;
    
    case 9:
        (**c).sinais[PCEsc]      = 0;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 1;
        (**c).dados.ula.Op       = 2;
        (**c).sinais[PCFonte1]   = 0;
        (**c).sinais[PCFonte0]   = 1;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 1;
        
        (**c).prox_estado        = 0;
    break;
    
    case 10:
        (**c).sinais[PCEsc]      = 1;
        (**c).sinais[IouD]       = 0;
        (**c).sinais[EscMem]     = 0;
        (**c).sinais[IREsc]      = 0;
        (**c).sinais[MemParaReg] = 0;
        (**c).sinais[EscReg]     = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
        (**c).sinais[UlaFonteA]  = 0;
        (**c).dados.ula.Op       = (**c).instrucao.funct;
        (**c).sinais[PCFonte1]   = 1;
        (**c).sinais[PCFonte0]   = 0;
        (**c).sinais[RegDst]     = 0;
        (**c).sinais[Branch]     = 0;
        
        (**c).prox_estado        = 0;
    break;
    
    
    default:
        break;
    }

    //decodifica_sinais_para_estado(*c);
    //(**c).estado = calcula_proximo_estado((**c).estado, (**c).instrucao.opcode);
    //decodifica_estado_para_sinais(*c);

}


void Controle_sinais(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];

    (**c).sinais[Branch] = e0 && e3;

    (**c).sinais[PCEsc] = (( (!e3 && !e2) && (!e1 && !e0) ) || (e3 && e1));

    (**c).sinais[IouD] = (((!e2 && e1) && e0) || ((e2 && !e1) && e0));

    (**c).sinais[EscMem] = ((e2 && !e1) && e0);

    (**c).sinais[IREsc] = ((!e3 && !e2) && (!e1 && !e0));

    (**c).sinais[MemParaReg] = ((e2 && !e1) && !e0);

    (**c).sinais[RegDst] = ( ( ( (!e3 && !e2) & !e1 ) || ( (!e3 && e2) && (e1 && e0) ) ) || ( (e3 && !e1) && !e0) );

    (**c).sinais[EscReg] = ( (e2 && !e0) || ( (e3 && !e1) && !e0) );

}
/*
void controle_ula_fonte(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];


    (**c).sinais[UlaFonteA] = 0;
    (**c).sinais[UlaFonteB0] = 0;
    (**c).sinais[UlaFonteB1] = 0;

    // PC + 1

    if ((!e3 && !e2) && (!e1 && !e0))
    {
        (**c).sinais[UlaFonteA] = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1;
    }

    if ((**c).instrucao.tipo == r)
    {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
    }

    // LW / SW / ADDI

    if ((**c).instrucao.opcode == 11 || // lw
        (**c).instrucao.opcode == 15 || // sw
        (**c).instrucao.opcode == 4)    // addi
    {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
    }

    // BEQ

    if ((**c).instrucao.opcode == 8)
    {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
    }
}
*/

void controle_ula_fonte(typ_state **c)
{
    estado_fsm st = (**c).estado;

    if (st == FETCH) {
        (**c).sinais[UlaFonteA] = 0;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 1;
        return;
    }

    if (st == DECODE) {
        (**c).sinais[UlaFonteA] = 0;
        if ((**c).instrucao.opcode == beq) {
            (**c).sinais[UlaFonteB1] = 1;
            (**c).sinais[UlaFonteB0] = 0;
        } else {
            (**c).sinais[UlaFonteB1] = 0;
            (**c).sinais[UlaFonteB0] = 1;
        }
        return;
    }

    if (st == MEM_ADDR || st == MEM_READ || st == MEM_WRITE || st == EXEC_I) {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 1;
        (**c).sinais[UlaFonteB0] = 0;
        return;
    }

    if (st == EXEC_R || st == BRANCH_COMP) {
        (**c).sinais[UlaFonteA] = 1;
        (**c).sinais[UlaFonteB1] = 0;
        (**c).sinais[UlaFonteB0] = 0;
        return;
    }

    (**c).sinais[UlaFonteA] = 0;
    (**c).sinais[UlaFonteB1] = 0;
    (**c).sinais[UlaFonteB0] = 0;
}

void controle_pc_fonte(typ_state **c)
{
    bool e0 = (**c).sinais[estado0];
    bool e1 = (**c).sinais[estado1];
    bool e2 = (**c).sinais[estado2];
    bool e3 = (**c).sinais[estado3];

    (**c).sinais[PCFonte1] = (((e3 && !e2) && e1) || ((e3 && e2) && e0));
    (**c).sinais[PCFonte0] = (((e3 && !e2) && e1));
}

estado_fsm calcula_proximo_estado(estado_fsm estado_atual, uint16_t opcode) {
    estado_fsm proximo = FETCH; // Padrão
    
    switch (estado_atual) {
        case FETCH:
            proximo = DECODE;
            break;

        case DECODE:
            switch (opcode) {
                case lw:
                case sw:    proximo = MEM_ADDR;     break;
                case r_op:  proximo = EXEC_R;       break;
                case beq:   proximo = BRANCH_COMP;  break;
                case j_op:  proximo = JUMP_COMP;    break;
                case addi:  proximo = EXEC_I;       break;
                default:    proximo = FETCH;        break; //  NOP
            }
            break;

        case MEM_ADDR:
            proximo = (opcode == lw) ? MEM_READ : MEM_WRITE;
            break;

        case MEM_READ:
            proximo = MEM_WRITEBACK;
            break;

        case EXEC_R:
            proximo = REG_WRITEBACK;
            break;
        case EXEC_I:
            proximo = REG_WRITEBACK;
            break;

        case MEM_WRITEBACK:
        case MEM_WRITE:
        case BRANCH_COMP:
        case JUMP_COMP:
            //finalizam e retornam pra fetch
            proximo = FETCH;
            break;
    }
    return proximo;
}

void controle_ula(typ_state **c)
{
    (**c).sinais[ControleUla1] = 0;
    (**c).sinais[ControleUla2] = 0;
    (**c).sinais[ControleUla3] = 0;
    (**c).dados.ula.Op = ADD;

    if ((**c).instrucao.tipo == r)
    {
        switch ((**c).instrucao.funct)
        {
            // ADD
            case 0:
                (**c).sinais[ControleUla1] = 0;
                (**c).sinais[ControleUla2] = 0;
                (**c).sinais[ControleUla3] = 0;
                (**c).dados.ula.Op = ADD;
                break;

            // SUB
            case 2:
                (**c).sinais[ControleUla1] = 0;
                (**c).sinais[ControleUla2] = 0;
                (**c).sinais[ControleUla3] = 1;
                (**c).dados.ula.Op = SUB;
                break;

            // AND
            case 4:
                (**c).sinais[ControleUla1] = 0;
                (**c).sinais[ControleUla2] = 1;
                (**c).sinais[ControleUla3] = 1;
                (**c).dados.ula.Op = AND;
                break;

            // OR
            case 5:
                (**c).sinais[ControleUla1] = 1;
                (**c).sinais[ControleUla2] = 0;
                (**c).sinais[ControleUla3] = 0;
                (**c).dados.ula.Op = OR;
                break;
        }
    }

    // LW / SW / ADDI

    if ((**c).instrucao.opcode == 11 || // lw
        (**c).instrucao.opcode == 15 || // sw
        (**c).instrucao.opcode == 4)    // addi
    {
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 0;
        (**c).sinais[ControleUla3] = 0;
        (**c).dados.ula.Op = ADD;
    }

    // BEQ

    if ((**c).instrucao.opcode == 8)
    {
        (**c).sinais[ControleUla1] = 0;
        (**c).sinais[ControleUla2] = 1;
        (**c).sinais[ControleUla3] = 0;
        (**c).dados.ula.Op = SUB;
    }
}

void decodifica_estado_para_sinais(typ_state *s) {
    int v = (int)s->estado; // pega o int do enum 0-9

    /*
    s->prox_estado[PE0] = (v >> 0) & 1; // bit 0
    s->prox_estado[PE1] = (v >> 1) & 1; // bit 1
    s->prox_estado[PE2] = (v >> 2) & 1; // bit 2
    s->prox_estado[PE3] = (v >> 3) & 1; // bit 3
    */
}

void decodifica_sinais_para_estado(typ_state *s)
{
    s->estado = 0;

    s->estado |= s->sinais[estado0];
    s->estado |= s->sinais[estado1] << 1;
    s->estado |= s->sinais[estado2] << 2;
    s->estado |= s->sinais[estado3] << 3;
    return;
}
