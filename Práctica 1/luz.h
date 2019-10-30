// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Luz.h
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz
{
    private:
        Tupla4f posicion, colorAmbiente, colorDifuso, colorEspecular;
        glEnum id;
        
    public:
        void activar();
}




#endif