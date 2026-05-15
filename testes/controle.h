#include "dcl_str_p2.h"

#ifndef controle_H
#define controle_H

enum controle_interno
{
    PE3 = 0,
    PE2 = 1,
    PE1 = 2,
    PE0 = 3,
    Op3 = 4,
    Op2 = 5,
    Op1 = 6,
    Op0 = 7,
    Funct2 = 8,
    Funct1 = 9,
    Funct0 = 10,
};

void controle(typ_state **C);



#endif