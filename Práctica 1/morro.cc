#include "morro.h"

Morro::Morro(){
    torso = new Cilindro(50,25,10);
    boca = new Boca();
    rem = new Remolque();
    cabina = new Cabina();
    gradoRemolque = 0;
    aterrizaje = true;
}


void Morro::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
    glPushMatrix();
        glPushMatrix();
            glScalef(5,0.75,0.75);
            glRotatef(-90,0,0,1);
            torso->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(130,0,0);
            glRotatef(90,0,1,0);
            glScalef(7.0,7.0,7.0);
            boca->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(6,12,0);
            glScalef(5.5,5.5,5.5);
            glRotatef(90,0,1,0);
            cabina->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(75,0,0);
            glScalef(10.0,10.0,10.0);
            glRotatef(90,0,1,0);
            glRotatef(gradoRemolque,1,0,0);
            rem->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

    glPopMatrix();
}


void Morro::cambiarGradoRemolque(int incremento){
    if(gradoRemolque+incremento > 90)
        gradoRemolque = 90;
    else if(gradoRemolque+incremento < 0)
        gradoRemolque = 0;
    else
        gradoRemolque+=incremento;
}

//void switchAterrizaje()

//Modificadores de colores
void Morro::setColor(float R,float G,float B){
    setColorTorso(R,G,B);
    setColorCabina(0.9,0.9,0.9);
    setColorRemolque(0,0,0);
    setColorBoca(0.5,0.5,0.5);
}

void Morro::setColorTorso(float R,float G,float B){
    torso->setColor(R,G,B);
}

void Morro::setColorCabina(float R,float G,float B){
    cabina->setColor(R,G,B);
}

void Morro::setColorRemolque(float R,float G,float B){
    rem->setColor(R,G,B);
}
void Morro::setColorBoca(float R,float G,float B){
    boca->setColor(R,G,B);
}

//Modificadores de materiales
void Morro::setMaterial(Material mat){
    torso->setMaterial(mat);
    boca->setMaterial(mat);
    cabina->setMaterial(mat);
    rem->setMaterial(mat);
}

void Morro::setMaterialTorso(Material mat){
    torso->setMaterial(mat);
}

void Morro::setMaterialCabina(Material mat){
    cabina->setMaterial(mat);
}

void Morro::setMaterialRemolque(Material mat){
    rem->setMaterial(mat);
}

void Morro::setMaterialBoca(Material mat){
    boca->setMaterial(mat);
}