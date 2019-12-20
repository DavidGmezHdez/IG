// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Semiesfera.h

//
// #############################################################################

#ifndef SEMIESFERA_H_INCLUDED
#define SEMIESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Semiesfera : public ObjRevolucion
{
    public:
    Semiesfera(const int num_vert_perfil, const int num_instancias_perf, const float radio);
    void crearTriangulos(std::vector<Tupla3f> perfil_original,int num_instancias);
};

#endif