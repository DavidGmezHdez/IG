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


void LuzPosicional::moverLuz(int dir, int incremento, int posicionFinal){
    switch(dir){
        case 0:
                if(posicion(0)+incremento!=posicionFinal)
                    posicion(0)= posicion(0)+incremento;
            break;
        case 1:
                if(posicion(1)+incremento!=posicionFinal)
                    posicion(1)= posicion(1)+incremento;
            break;
        case 2:
                if(posicion(2)+incremento!=posicionFinal)
                    posicion(2)= posicion(2)+incremento;
            break;
    }
}

void LuzPosicional::animarLuz(){
glPushMatrix();
    moverLuz(0,1.0,700);
glPopMatrix();
}