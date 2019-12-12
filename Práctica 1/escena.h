#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "alax.h"
#include "objrevolucion.h"
#include "objply.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "material.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "textura.h"
#include "cuadro.h"


typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:   
 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

    menu modoMenu=NADA;
    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr; 
    Tetraedro * tetraedro= nullptr;
    Cilindro * cilindro = nullptr;
    AlaX * alaX = nullptr;
    Cuadro * cuadro = nullptr;
    Cono * cono = nullptr;
    Esfera * esfera = nullptr;
    ObjPLY * hormiga = nullptr;
    ObjRevolucion * peon = nullptr;
    ObjRevolucion * peon2 = nullptr;
    Material oro,plata,bronce,negro;
    Textura  madera;
    LuzPosicional *luzpos = nullptr;
    LuzDireccional *luzdir = nullptr;
    bool luces[8] = {false};
    bool metodoDibujado;
    int seleccionDibujo;
    int modoVisualizacion;
    float velocidad = 1.0;
    int grado; float inc;
    bool puntos = false, lineas = false, solido = false, ajedrez = false, tapas = true, luz = false, angulo, 
    objeto,animacionAutomatica,animacionManual,animacionLuz;

    public:

        Escena();
        void inicializar( int UI_window_width, int UI_window_height );
        void redimensionar( int newWidth, int newHeight ) ;

        // Dibujar
        void dibujar() ;

        // Interacción con la escena
        bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
        void teclaEspecial( int Tecla1, int x, int y );

        void animarModeloJerarquico();
        void animarManual();

};
#endif
