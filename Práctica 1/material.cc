#include "material.h"

 Material::Material(Tupla4f mdifuso,Tupla4f mespecular,Tupla4f mambiente,float mbrillo){
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = mbrillo;
}


Material::aplicar{
    glMaterialfv(GL_FRONT,GL_AMBIENT,this->ambiente.data());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->difuso.data());
    glMaterialfv(GL_FRONT,GL_SPECULAR,this->especular.data());
    glMaterialfv(GL_FRONT,GL_SHININESS,this->brillo);
}
