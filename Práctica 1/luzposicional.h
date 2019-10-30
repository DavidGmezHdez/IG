// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: LuzPosicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional :: public Luz
{
    public:
    LuzPosicional(const Tupla2f & posicion);
}

#endif