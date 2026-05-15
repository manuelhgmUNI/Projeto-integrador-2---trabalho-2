#include <stdio.h>
#include "dcl_str_p2.h"

typ_ulaR ula(int A, int B, typ_ulaOp operacao) {
    typ_ulaR res= {0, false, false};
    int inter_Resul = 0;

    switch (operacao) {
        case ADD:
            inter_Resul = A + B;
            res.overflow = (inter_Resul > 127 || inter_Resul < -128);
            break;
        case SUB:
            inter_Resul = A - B;
            res.overflow = (inter_Resul > 127 || inter_Resul < -128);
            break;
        case AND:
            inter_Resul = A & B;
            break;
        case OR:
            inter_Resul = A | B;
            break;
    }

    res.resultado = (int8_t) inter_Resul;
    res.zero = (res.resultado == 0);
    return res;
}