#include "alax.h"

AlaX::AlaX(){
    morro = new Morro();
    trasera = new Trasera();
    direccion = {0,0,0};
    rotacion = {0,0,0};
}

void AlaX::draw(bool modoDibujado,bool points,bool lines,bool fill, bool chess){
glPushMatrix();

    glTranslatef(direccion(0),direccion(1),direccion(2));
    glRotatef(rotacion(0),1,0,0);
    glRotatef(rotacion(1),0,1,0);
    glRotatef(rotacion(2),0,0,1);

    glPushMatrix();
        morro->draw( modoDibujado,points,lines,fill,chess);
    glPopMatrix();

    glPushMatrix();
        trasera->draw( modoDibujado,points,lines,fill,chess);
    glPopMatrix();

glPopMatrix();
}


void AlaX::switchAlas(float grado){
    trasera->switchAlas(grado);
}

void AlaX::desplegarAlas(float incremento){
    trasera->desplegarAlas(incremento);
}

void AlaX::plegarAlas(float incremento){
    trasera->plegarAlas(incremento);
}


void AlaX::sacarTrenAterrizaje(int incremento){
    morro->sacarTrenAterrizaje(incremento);
}

void AlaX::guardarTrenAterrizaje(int incremento){
    morro->guardarTrenAterrizaje(incremento);
}

void AlaX::girarAndroide(float incremento){
    trasera->girarAndroide(incremento);
}

void AlaX::rotarNave(int angulo, int incremento,int max){
    switch(angulo){
        case 0:
                if(rotacion(0)+incremento!=max)
                    rotacion(0) = (rotacion(0)+incremento)%360;
            break;
        case 1:
                if(rotacion(1)+incremento!=max)
                    rotacion(1) = (rotacion(1)+incremento)%360;
            break;
        case 2:
                if(rotacion(2)+incremento!=max)
                    rotacion(2) = (rotacion(2)+incremento)%360;
        break;
    }

}


void AlaX::dirigirNave(int dir, int incremento, int posicionFinal){
    switch(dir){
        case 0:
                if(direccion(0)+incremento!=posicionFinal)
                    direccion(0)= direccion(0)+incremento;
            break;
        case 1:
                if(direccion(1)+incremento!=posicionFinal)
                    direccion(1)= direccion(1)+incremento;
            break;
        case 2:
                if(direccion(2)+incremento!=posicionFinal)
                    direccion(2)= direccion(2)+incremento;
            break;
    }

}


//Animaciones
void AlaX::aterrizar(){
     /*
      Angulo 0:   
                  +30 --> derecha
                  -30 -->izquierda
      Angulo 1:
                  +30 --> izquierda
                  -30 --> derecha
      
      Angulo 2:   +30 --> arriba
                  -30 --> abajo
      */
    //velocidad = velocidad*0.1; 

    switch(fase){
        case 0:
            if(getDireccion()(0) != -201){
                desplegarAlas(1.0);
                guardarTrenAterrizaje(1.0);
                rotarNave(0,1.0,30);
                rotarNave(1,-1.0,-40);
                rotarNave(2,-1.0,-20);
                dirigirNave(0,1,-200);
                dirigirNave(1,-1,200);
                dirigirNave(2,1,-200);
                cout<<direccion(0)<<endl;
            }
            else
                fase = 1;
            break;
        case 1:
            if(getDireccion()(0) != -1){
                rotarNave(0,-1.0,0);
                rotarNave(1,1.0,0);
                rotarNave(2,1.0,0);
                dirigirNave(0,1,0);
                dirigirNave(2,1,0);
            }
            else
                fase = 2;
            break;
        case 2:
            plegarAlas(-1.0);
            sacarTrenAterrizaje(-1.0);
            dirigirNave(1,-1,17);
        break;
    }
}


void AlaX::animacionManual(int grado, float incremento){
    switch(grado){
        case 0:
            if(incremento>0)
                desplegarAlas(incremento);
            else
                plegarAlas(incremento);
            break;
        case 1:
            if(incremento>0)
                guardarTrenAterrizaje(incremento);
            else
                sacarTrenAterrizaje(incremento);
            break;
        case 2:
            if(incremento>0)
                rotarNave(0,incremento,360);
            else
                rotarNave(0,incremento,-360);
            break;
    }
}



//Modificadores colores
void AlaX::setColor(float R,float G,float B){
    setColorTrasera(R,G,B);
    setColorMorro(R,G,B);
}

void AlaX::setColorTrasera(float R,float G,float B){
    trasera->setColor(R,G,B);
}

void AlaX::setColorMorro(float R,float G,float B){
    morro->setColor(R,G,B);
}

//Modificadores materiales
void AlaX::setMaterial(Material mat){
    setMaterialTrasera(mat);
    setMaterialMorro(mat);
}

void AlaX::setMaterialTrasera(Material mat){
    trasera->setMaterial(mat);
}

void AlaX::setMaterialMorro(Material mat){
    morro->setMaterial(mat);
}
