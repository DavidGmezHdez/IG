// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Textura.h
// -- declaraciones de clase Textura
//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"


class Textura{
    private:
        GLuint textura_id = 0;
        std::vector<unsigned char*> data;
        jpg::Imagen * pimg = nullptr;
        int ancho, alto;
    public:
        Textura(){};
        Textura(std::string archivo,GLuint id);
        void activar();
        inline GLuint getID(){return textura_id;};
        inline int getAncho(){return ancho;};
        inline int getAlto(){return alto;};
};

#endif