// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Material.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

class Material{
    private:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
    
    public:
        Material(Tupla4f mdifuso,Tupla4f mespecular,Tupla4f mambiente,float mbrillo);

        void aplicar();

}
#endif