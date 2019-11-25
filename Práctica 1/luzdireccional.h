// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: LuzDireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
    protected:
        const float PI = 3.141592653;
        float alpha;
        float beta;
    public:
    LuzDireccional(GLenum id,const Tupla2f &orientacion,Tupla4f ambiente,Tupla4f difuso,Tupla4f especular);

    void variarAnguloAlpha(float incremento);

    void variarAnguloBeta(float incremento);

    void cambiarPosicionamiento();
};

#endif