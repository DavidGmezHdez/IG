#include "ala.h"


Ala::Ala(){
    rotor = new Cilindro(50,25,10);
    base = new Cubo();
    laser = new Cilindro(50,25,10);
    canon = new Tetraedro();
    gradoAla = 0;
}

void Ala::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
    glPushMatrix();

        glPushMatrix();
        glTranslatef(-25,0,0);
        glScalef(2,1,1);
        glRotatef(-90,0,0,1);
        rotor->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,40);
        glScalef(20,1.5,35);
        base->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-15,0,75);
        glScalef(3,0.15,0.15);
        glRotatef(-90,0,0,1);
        laser->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(60,0,76);
        glScalef(5,5,5);
        glRotatef(-90,0,0,1);
        canon->draw(modoDibujado,points,lines,fill,chess);
        glPopMatrix();
        
    
    glPopMatrix();
}

void Ala::cambiarGradoAla(int incremento){
    gradoAla+=incremento;
}


int Ala::getGradoAla(){return gradoAla;}

//Modificadores de colores
void Ala::setColor(float R,float G,float B){
    base->setColor(R,G,B);
    rotor->setColor(R,G,B);
    laser->setColor(R,G,B);
    canon->setColor(R,G,B);
}

void Ala::setColorRotor(float R,float G,float B){
    rotor->setColor(R,G,B);
}

void Ala::setColorBase(float R,float G,float B){
    base->setColor(R,G,B);
}

void Ala::setColorLaser(float R,float G,float B){
    laser->setColor(R,G,B);
}

void Ala::setColorCanon(float R,float G,float B){
    canon->setColor(R,G,B);
}

//Modificadores de materiales
void Ala::setMaterial(Material mat){
    base->setMaterial(mat);
    rotor->setMaterial(mat);
    canon->setMaterial(mat);
    laser->setMaterial(mat);
}

void Ala::setMaterialBase(Material mat){
    base->setMaterial(mat);
}

void Ala::setMaterialRotor(Material mat){
    rotor->setMaterial(mat);
}

void Ala::setMaterialLaser(Material mat){
    laser->setMaterial(mat);
}

void Ala::setMaterialCanon(Material mat){
    canon->setMaterial(mat);
}
