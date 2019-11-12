#include "luzdireccional.h"


LuzDireccional::LuzDireccional(GLenum id,const Tupla3f &orientacion,Tupla4f ambiente,Tupla4f difuso,Tupla4f especular){
    this->id = id;
    this->colorAmbiente = ambiente;
    this->colorDifuso = difuso;
    this->colorEspecular = especular;


    this->posicion(0) = orientacion(0);
    this->posicion(1) = orientacion(1);
    this->posicion(2) = orientacion(2);
    this->posicion(3) = 0.0;
}


void LuzDireccional::variarAnguloAlpha(float incremento){
    this->alpha += incremento;
}

void LuzDireccional::variarAnguloBeta(float incremento){
    this->beta += incremento;
}