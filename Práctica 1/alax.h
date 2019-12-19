// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: AlaX.h

//
// #############################################################################

#ifndef ALAX_H_INCLUDED
#define ALAX_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "morro.h"
#include "trasera.h"


using namespace std;
class AlaX : public Malla3D
{
    private:
        Trasera * trasera = nullptr;
        Morro * morro = nullptr;
        Tupla3i rotacion;
        float anguloMaxRot = 45;
        int fase = 0;
                
    public:
        AlaX();
        void draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess);

        //Modificadores alas
        void switchAlas(float grado);
        void desplegarAlas(float incremento);
        void plegarAlas(float incremento);

        void sacarTrenAterrizaje(int incremento);
        void guardarTrenAterrizaje(int incremento);

        void girarAndroide(float incremento);

        Tupla3i getRotacion(){return rotacion;};
        float getAnguloMax(){return anguloMaxRot;};

        //Modificadores movimiento
        void rotarNave(int angulo, int incremento,int max);
        void dirigirNave(int dir, int incremento, int posicionFinal);

        

        //Animaciones
        void animacionAutomatica();
        void animacionManual(int grado, float incremento);

        //Modificadores colores
        void setColor(float R,float G,float B);
        void setColorTrasera(float R,float G,float B);
        void setColorMorro(float R,float G,float B);

        //Modificadores materiales
        void setMaterial(Material mat);
        void setMaterialTrasera(Material mat);
        void setMaterialMorro(Material mat);
};


#endif