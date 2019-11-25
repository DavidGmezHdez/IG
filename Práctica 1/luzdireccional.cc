#include "luzdireccional.h"


LuzDireccional::LuzDireccional(GLenum id,const Tupla2f &orientacion,Tupla4f ambiente,Tupla4f difuso,Tupla4f especular){
    this->id = id;
    
    this->alpha = orientacion(0);
    this->beta = orientacion(1);
    this->cambiarPosicionamiento();
    this->posicion(3) = 0.0;

    this->colorAmbiente = ambiente;
    this->colorDifuso = difuso;
    this->colorEspecular = especular;    
}


void LuzDireccional::variarAnguloAlpha(float incremento){
    this->alpha += incremento;
    this->cambiarPosicionamiento();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    this->beta += incremento;
    this->cambiarPosicionamiento();
}

void LuzDireccional::cambiarPosicionamiento(){
    this->posicion(0) = sin(alpha*(PI/180));
    this->posicion(1) = sin(beta*(PI/180));
    this->posicion(2) = cos(alpha*(PI/180))*cos(beta*(PI/180));
}