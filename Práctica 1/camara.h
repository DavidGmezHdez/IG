// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Camara.h

//
// #############################################################################


#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
    private:
        
        Tupla3f eye,at,up,atAnterior;

        int tipo; //0 = ortogonal | 1 = perspectiva

        float fov,aspect,near,far,top,left;

        //Vectores de direccion y ejes de la cámara
        Tupla3f vectorDir, vectorX, vectorY;

        //Funciones sobre la matriz
        Tupla3f cambiarMatriz(Tupla3f eje, Tupla3f vector, float angulo);
        void rotarPP(float angulo, int eje);
        void rotarE(float angulo, int eje);
        
    public:
        Camara(){};
        Camara(int t,Tupla3f e, Tupla3f a, Tupla3f u, float ancho, float alto);
        void rotarXExaminar(float angulo);
        void rotarYExaminar(float angulo);
        //void rotarZExaminar(float angulo);
        
        void rotarXPrimeraPersona(float angulo);
        void rotarYPrimeraPersona(float angulo);
        //void rotarZPrimeraPersona(float angulo);

        void mover(float x, float y, float z);
        void zoom(float factor);
        
        void setObserver();
        void setProyeccion();

        void setAt(Tupla3f objetivo);
        void volverAtAnterior();



};


#endif