#ifndef _ESCENA_H
#define _ESCENA_H

#include "aux.h"
#include "iostream"
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
#include "camara.h"


using namespace std;

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELANIMAUTO,SELANIMMAN,SELCAM} menu;
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
    Malla3D* mallas[8]= {nullptr};

    //Materiales
    Material oro,plata,bronce,negro;

    //Texturas
    Textura  madera;

    //Luces
    Luz*  luces[8] = {nullptr};
    bool switchLuces[8] = {false};

    //Camaras
    Camara* camaras[8] = {nullptr};
    bool switchCamaras[8] = {false};
    int numCamaraActiva = 0;

    //Modos visualizacion, dibujado y dibujo
    bool metodoDibujado;
    int seleccionDibujo;
    int modoVisualizacion;

    //Variables modelo jerarquico
    int grado; float inc;
    
    //Modos visualuzacion
    bool puntos = false, lineas = false, solido = false, ajedrez = false, tapas = true, luz = false, camara = false;
    bool angulo,objeto,animacionAutomatica,animacionManual,animacionLuz;

    //Parametros raton
    bool boton,objetoSeleccionado = false; //false->derecho, true->izquierdo
    int xraton, yraton,xpixel, ypixel, objsel;

    public:

        Escena();
        void inicializar( int UI_window_width, int UI_window_height );
        void redimensionar( int newWidth, int newHeight ) ;

        //Funciones para las camaras
        void clickRaton(int boton, int estado, int x, int y);
        void ratonMovido(int x, int y);

        // Dibujar
        void dibujar() ;

        // Interacción con la escena
        bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
        void teclaEspecial( int Tecla1, int x, int y );
        
        //Funciones de animacion
        void animarModeloJerarquico();
        void animarManual();

        //Funciones de seleccion
        void dibujaSeleccion();
        void seleccionarObjetivo(int obj);

};
#endif
