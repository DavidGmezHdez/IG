// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Camara.h

//
// #############################################################################


#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"

class Camara
{
    private:
        
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;

        int tipo; //0 = ortogonal | 1 = perspectiva

        float fov,aspect,near,far;
    
    public:
        Camara(){};
        Camara(Tupla3f e, Tupla3f a, Tupla3f u, int t, float f, float as, float n, float fa);
        void rotarXExaminar(float angulo);
        void rotarYExaminar(float angulo);
        void rotarZExaminar(float angulo);
        
        void rotarXPrimeraPersona(float angulo);
        void rotarYPrimeraPersona(float angulo);
        void rotarZPrimeraPersona(float angulo);

        void mover(float x, float y, float z);
        void zoom(float factor);
        
        void setObserver();
        void setProyeccion();




};


#endif