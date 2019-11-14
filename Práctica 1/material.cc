
#include "material.h"


Material::Material(){
    this->difuso(0) = 0;
    this->difuso(1) = 0;
    this->difuso(2) = 0;
    this->difuso(3) = 0;

    this->especular(0) = 0;
    this->especular(1) = 0;
    this->especular(2) = 0;
    this->especular(3) = 0;

    this->ambiente(0) = 0;
    this->ambiente(1) = 0;
    this->ambiente(2) = 0;
    this->ambiente(3) = 0;

    this->brillo = 0.0;


}

Material::Material(const Material &material){
    this->difuso = material.difuso;
    this->especular = material.especular;
    this->ambiente = material.ambiente;
    this->brillo = material.brillo;

}

 Material::Material(Tupla4f mambiente,Tupla4f mdifuso,Tupla4f mespecular,float mbrillo){
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = mbrillo;
}


void Material::aplicar(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,this->ambiente);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->difuso);
    glMaterialfv(GL_FRONT,GL_SPECULAR,this->especular);
    glMaterialf(GL_FRONT,GL_SHININESS,this->brillo);
}
