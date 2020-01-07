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
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
            cabina->draw(modoDibujado,points,lines,fill,chess);
            glDisable(GL_BLEND);
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


void Morro::sacarTrenAterrizaje(int incremento){
    if(gradoRemolque != 0)
        gradoRemolque+=incremento;
    else
        gradoRemolque = 0;
}

void Morro::guardarTrenAterrizaje(int incremento){
    if(gradoRemolque != 90)
        gradoRemolque+=incremento;
    else
        gradoRemolque = 90;

}

//void switchAterrizaje()

//Modificadores de colores
void Morro::setColor(Tupla3f cabina,Tupla3f boca,Tupla3f remolque,Tupla3f torso){
    this->cabina->setColor(cabina(0),cabina(1),cabina(2));
    this->boca->setColor(boca(0),boca(1),boca(2));
    this->rem->setColor(remolque(0),remolque(1),remolque(2));
    this->torso->setColor(torso(0),torso(1),torso(2));
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