// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Skybox.h
//
// #############################################################################

#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED

#include "aux.h"
#include "malla.h"

class Skybox : public Malla3D
{
   public:
   Skybox(float lado=1) ;
   void calcularCoordenadas();
};

#endif
