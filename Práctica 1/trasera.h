// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Trasera.h

//
// #############################################################################


#ifndef TRASERA_H_INCLUDED
#define TRASERA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "motor.h"
#include "ala.h"

class Trasera : public Malla3D
{
    private:
        Ala * alaSupDer = nullptr;
        Ala * alaSupIzq = nullptr;
        Ala * alaInfDer = nullptr;
        Ala * alaInfIzq = nullptr;
        Motor * motor = nullptr;
        int gradoMax = 20;
        int gradoAla1, gradoAla2;
        bool desplegadas;
   public:
        Trasera();
        void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);

        //Modificadores alas
        void switchAlas(float grado);
        void desplegarAlas(float incremento);
        void plegarAlas(float incremento);

        //Modificadores de colores
        void setColor(float R,float G,float B);
        void setColorAlas(float R,float G,float B);
        void setColorMotor(float R,float G,float B);

        //Modificadores de materiales
        void setMaterial(Material mat);
        void setMaterialAlas(Material mat);
        void setMaterialMotor(Material mat);
} ;

#endif
