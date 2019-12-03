// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Motor.h

//
// #############################################################################

#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"

class Motor : public Malla3D
{
    private:
        Cubo * base = nullptr;
        Cubo * cola = nullptr;
        Esfera * androide = nullptr;
        float gradoAndroide;
    public:
        Motor();
        void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);
        void girarAndroide(float incremento);
        //Modificadores colores
        void setColor(float R,float G,float B);
        void setColorBase(float R,float G,float B);
        void setColorCola(float R,float G,float B);
        void setColorAndroide(float R,float G,float B);

        //Modificadores materiales
        void setMaterial(Material mat);
        void setMaterialBase(Material mat);
        void setMaterialCola(Material mat);
        void setMaterialAndroide(Material mat);
};


#endif