// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Ala.h

//
// #############################################################################

#ifndef ALA_H_INCLUDED
#define ALA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "cubo.h"
#include "tetraedro.h"

class Ala : public Malla3D
{
    private:
        Cilindro * rotor = nullptr;
        Cubo * base = nullptr;
        Cilindro * laser = nullptr;
        Tetraedro * canon = nullptr;
        int gradoAla;
   public:
        Ala();
        void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);
        void cambiarGradoAla(int incremento);
        int getGradoAla();
        //Modificadores de colores
        void setColor(float R,float G,float B);
        void setColorRotor(float R,float G,float B);
        void setColorBase(float R,float G,float B);
        void setColorLaser(float R,float G,float B);
        void setColorCanon(float R,float G,float B);

        //Modificadores de materiales
        void setMaterial(Material mat);
        void setMaterialBase(Material mat);
        void setMaterialRotor(Material mat);
        void setMaterialLaser(Material mat);
        void setMaterialCanon(Material mat);
} ;

#endif
