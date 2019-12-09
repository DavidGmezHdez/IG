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
    LuzPosicional(GLenum id,Tupla3f posicion,Tupla4f ambiente,Tupla4f difuso,Tupla4f especular);
    void moverLuz(int dir, int incremento, int posicionFinal);
    void animarLuz();
};  

#endif