#include "dcl_str_p2.h"

typ_ulaOp controle_ula(bool c1, bool c2, bool c3, uint8_t funct)
{
    //ControleUla1 = c1 ControleUla2 = c2 ControleUla3 = c3

    // 000 -> ADD
    if (!c1 && !c2 && !c3)
    {
        return ADD;
    }

    // 001 -> SUB
    if (!c1 && !c2 && c3)
    {
        return SUB;
    }

    // 010 -> tipo R
    if (!c1 && c2 && !c3)
    {
        switch (funct)
        {
            case 0:
                return ADD;

            case 2:
                return SUB;

            case 4:
                return AND;

            case 5:
                return OR;

            default:
                return ADD;
        }
    }

    // 011 -> AND
    if (!c1 && c2 && c3)
    {
        return AND;
    }

    // 100 -> OR
    if (c1 && !c2 && !c3)
    {
        return OR;
    }

    return ADD;
}