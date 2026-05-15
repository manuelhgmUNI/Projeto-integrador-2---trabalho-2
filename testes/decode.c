#include <string.h>
#include "assinaturas.h"

typ_decoded_instruction decode_instruction(uint16_t instruction_word) {
    typ_decoded_instruction decoded_ins;
    memset(&decoded_ins, 0, sizeof(typ_decoded_instruction));

    decoded_ins.instrucao_bruta = instruction_word;

    
    for (int i = 0; i < 16; i++) {
        if ((instruction_word >> (15 - i)) & 1) 
        {
            decoded_ins.total[i] = '1';
        } else {
            decoded_ins.total[i] = '0';
        }
    }
    decoded_ins.total[16] = '\0';

    
    decoded_ins.opcode = (instruction_word >> 12) & 0x0F;
    decoded_ins.rs     = (instruction_word >> 9)  & 0x07;
    decoded_ins.rt     = (instruction_word >> 6)  & 0x07;
    decoded_ins.rd     = (instruction_word >> 3)  & 0x07;
    decoded_ins.funct  =  instruction_word        & 0x07;
    decoded_ins.addr   =  instruction_word        & 0x7F;

   
    int16_t imm6 = (int16_t)(instruction_word & 0x3F);
    if (imm6 & 0x20) imm6 |= (int16_t)0xFFC0;
    decoded_ins.immediato = imm6;

    if (decoded_ins.opcode == r_op) {
        decoded_ins.tipo = r;
    } else if (decoded_ins.opcode == j_op) {
        decoded_ins.tipo = j;
    } else {
        decoded_ins.tipo = i;
    }

    return decoded_ins;
}
