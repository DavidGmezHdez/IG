#include "luzposicional.h"


LuzPosicional::LuzPosicional(GLenum id,Tupla3f posicion,Tupla4f ambiente,Tupla4f difuso,Tupla4f especular){
    this->id = id;
    this->colorAmbiente = ambiente;
    this->colorDifuso = difuso;
    this->colorEspecular = especular;

    this->posicion(0) = posicion(0);
    this->posicion(1) = posicion(1);
    this->posicion(2) = posicion(2);
    this->posicion(3) = 1;
}