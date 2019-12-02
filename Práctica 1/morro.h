// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Morro.h

//
// #############################################################################

#ifndef MORRO_H_INCLUDED
#define MORRO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "boca.h"
#include "cilindro.h"
#include "remolque.h"
#include "cabina.h"

class Morro : public Malla3D
{
    private:
        Cilindro * torso = nullptr;
        Boca * boca = nullptr;
        Remolque * rem = nullptr;
        Cabina * cabina = nullptr;
        int gradoRemolque;
   public:
        Morro();
        void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);
        void cambiarGradoRemolque(int incremento);
        //Modificadores de colores
        void setColor(float R,float G,float B);
        void setColorTorso(float R,float G,float B);
        void setColorCabina(float R,float G,float B);
        void setColorRemolque(float R,float G,float B);
        void setColorBoca(float R,float G,float B);

        //Modificadores de materiales
        void setMaterial(Material mat);
        void setMaterialTorso(Material mat);
        void setMaterialCabina(Material mat);
        void setMaterialRemolque(Material mat);
        void setMaterialBoca(Material mat);
} ;

#endif
