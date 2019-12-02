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
        Cilindro * rotor1 = nullptr;
        Cilindro * rotor2 = nullptr;
        Cilindro * rotor3 = nullptr;
        Cilindro * rotor4 = nullptr;
        Cubo * base = nullptr;
        Esfera * androide = nullptr;
    public:
        Motor();
        void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);

        //Modificadores colores
        void setColor(float R,float G,float B);
        void setColorBase(float R,float G,float B);
        void setColorRotores(float R,float G,float B);
        void setColorAndroide(float R,float G,float B);

        //Modificadores materiales
        void setMaterial(Material mat);
        void setMaterialBase(Material mat);
        void setMaterialRotores(Material mat);
        void setMaterialAndroide(Material mat);
};


#endif