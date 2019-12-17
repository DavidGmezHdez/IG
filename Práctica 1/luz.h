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
    protected:
        Tupla4f posicion, colorAmbiente, colorDifuso, colorEspecular;
        GLenum id;
    public:
        void activar();
        virtual void variarAnguloAlpha(float incremento){};
        virtual void variarAnguloBeta(float incremento){};
        virtual void setPosicion(Tupla3f posicion){};
        virtual void animarLuz(){};
        inline GLenum getID(){return id;};
};




#endif