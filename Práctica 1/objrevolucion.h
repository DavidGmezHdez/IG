// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
private:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf);
    
    void crearPuntos(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapaSup, bool hayTapaSup, bool tapaInf, bool hayTapaInf);
    void crearPuntosReversos(std::vector<Tupla3f> perfil_original, int num_instancias);
    
    void crearTriangulos(std::vector<Tupla3f> perfil_original, int num_instancias);
    
    bool buscarTapaSup(std::vector<Tupla3f> perfil_original, int num_instancias);
    bool buscarTapaInf(std::vector<Tupla3f> perfil_original, int num_instancias);
    
    Tupla3f sacarTapaInf(std::vector<Tupla3f> perfil_original, int num_instancias);
    Tupla3f sacarTapaSup(std::vector<Tupla3f> perfil_original, int num_instancias);
    
    void crearTapaSup(std::vector<Tupla3f> perfil_original, int num_instancias);
    void crearTapaInf(std::vector<Tupla3f> perfil_original, int num_instancias);


} ;

#endif
