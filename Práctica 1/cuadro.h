// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cuadro.h

//
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"
#include "malla.h"

class Cuadro : public Malla3D
{
    float lado;
    public:
        Cuadro(float l = 1);
        void calcularCoordenadas();
        inline float getLado(){return lado;};
};

#endif