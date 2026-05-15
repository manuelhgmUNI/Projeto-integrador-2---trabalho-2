#include "assinaturas.h"

typ_ulaR ula(int A, int B, typ_ulaOp operacao) {
    typ_ulaR res;
    res.zero = false;
    res.overflow = false;
    res.resultado = 0;

    switch (operacao) {
        case ADD:
            res.resultado = A + B;
            // Checagem simples de overflow 
            if (((A > 0 && B > 0) && (res.resultado < 0)) || ((A < 0 && B < 0) && (res.resultado >= 0)))
            {
                res.overflow = true;
            }
            break;
        case SUB:
            res.resultado = A - B;
            if (((A > 0 && B < 0) && (res.resultado < 0)) || ((A < 0 && B > 0) && (res.resultado >= 0)))
            {
                res.overflow = true;
            }
            break;
        case AND:
            res.resultado = A & B;
            break;
        case OR:
            res.resultado = A | B;
            break;
    }

    if (res.resultado == 0) 
    {
        res.zero = true;
    }

    return res;
}
