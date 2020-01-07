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
        void girarAndroide(float incremento);

        //Modificadores de colores
        void setColor(Tupla3f rotor, Tupla3f base, Tupla3f laser, Tupla3f canon,Tupla3f baseMotor, Tupla3f cola, Tupla3f androide);
        void setColorAlas(Tupla3f rotor, Tupla3f base, Tupla3f laser, Tupla3f canon);
        void setColorMotor(Tupla3f base, Tupla3f cola, Tupla3f androide);

        //Modificadores de materiales
        void setMaterialAlas(Material rotor, Material base, Material laser, Material canon);
        void setMaterialMotor(Material base, Material cola, Material androide);
} ;

#endif
