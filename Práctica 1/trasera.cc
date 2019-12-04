#include "trasera.h"

Trasera::Trasera(){
    alaSupDer = new Ala();
    alaSupIzq = new Ala();
    alaInfDer = new Ala();
    alaInfIzq = new Ala();
    motor = new Motor();

    gradoAla1 = 0;
    gradoAla2 = 0;
    desplegadas = false;
}

void Trasera::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
glPushMatrix();
    
    glPushMatrix();
        motor->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,12,22);
        glRotatef(gradoAla1,1,0,0);
        alaSupDer->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,12,-22);
        glRotatef(gradoAla2,1,0,0);
        glRotatef(180,1,0,0);
        alaSupIzq->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-12,22);
        glRotatef(gradoAla2,1,0,0);
        alaInfDer->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-12,-22);
        glRotatef(gradoAla1,1,0,0);
        glRotatef(180,1,0,0);
        alaInfIzq->draw(modoDibujado,points,lines,fill,chess);
    glPopMatrix();


glPopMatrix();
}


void Trasera::desplegarAlas(float incremento){
    if(!desplegadas){
        if((gradoAla2+incremento)<gradoMax && (gradoAla1-incremento)>-gradoMax){
            gradoAla2+=incremento;
            gradoAla1-=incremento;
        }
        else{
            gradoAla2 = gradoMax;
            gradoAla1 = -gradoMax;
            desplegadas = true;
        }
    }
}

void Trasera::plegarAlas(float incremento){
    if(desplegadas){
        if((gradoAla2+incremento)>0 && (gradoAla1-incremento)<0){
            gradoAla2+=incremento;
            gradoAla1-=incremento;
        }
        else{
            gradoAla2 = 0;
            gradoAla1 = 0;
            desplegadas = false;
        }
    }
}

void Trasera::switchAlas(float grado){
    if(!desplegadas)
        desplegarAlas(grado);
    else
        plegarAlas(-grado);
}

void Trasera::girarAndroide(float incremento){
    motor->girarAndroide(incremento);
}

//Modificadores de colores
void Trasera::setColor(float R,float G,float B){
    setColorAlas(R,G,B);
    setColorMotor(R,G,B);
}

void Trasera::setColorAlas(float R,float G,float B){
    alaSupDer->setColorBase(R,G,B);
    alaSupDer->setColorRotor(1,0,0);
    alaSupDer->setColorLaser(0.2,0.2,0.2);
    alaSupDer->setColorCanon(0,0,0);

    alaSupIzq->setColorBase(R,G,B);
    alaSupIzq->setColorRotor(1,0,0);
    alaSupIzq->setColorLaser(0.2,0.2,0.2);
    alaSupIzq->setColorCanon(0,0,0);
    
    alaInfDer->setColorBase(R,G,B);
    alaInfDer->setColorRotor(1,0,0);
    alaInfDer->setColorLaser(0.2,0.2,0.2);
    alaInfDer->setColorCanon(0,0,0);

    alaInfIzq->setColorBase(R,G,B);
    alaInfIzq->setColorRotor(1,0,0);
    alaInfIzq->setColorLaser(0.2,0.2,0.2);
    alaInfIzq->setColorCanon(0,0,0);

}

void Trasera::setColorMotor(float R,float G,float B){
    motor->setColorBase(R,G,B);
    motor->setColorCola(0,0,0);
    motor->setColorAndroide(0,0,1);
}

//Modificadores de materiales
void Trasera::setMaterial(Material mat){
    setMaterialAlas(mat);
    setMaterialMotor(mat);
}

void Trasera::setMaterialAlas(Material mat){
    alaSupDer->setMaterial(mat);
    alaSupIzq->setMaterial(mat);
    alaInfDer->setMaterial(mat);
    alaInfIzq->setMaterial(mat);
}

void Trasera::setMaterialMotor(Material mat){
    motor->setMaterial(mat);
}