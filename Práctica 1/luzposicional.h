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

class LuzPosicional : public Luz
{
    public:
    LuzPosicional(Tupla3f posicion,GLenum id,Tupla4f ambiente,Tupla4f difuso,Tupla4f especular);
};  

#endif