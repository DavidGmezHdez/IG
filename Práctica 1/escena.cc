#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   cubo = new Cubo();
   tetraedro = new Tetraedro();
   cuadro = new Cuadro();
   alaX = new AlaX();
   hormiga = new ObjPLY("plys/ant.ply");
   peon = new ObjRevolucion("plys/peon.ply",30,tapas,tapas);
   peon2 = new ObjRevolucion("plys/peon.ply",30,tapas,tapas);
   cilindro = new Cilindro(50,25,10);
   cono = new Cono(50,25,10);
   esfera = new Esfera(50,50,10);
   plata = Material({0.19225,0.19225,0.19225, 1.0},{0.50754, 0.50754,0.50754, 1.0},{0.0, 0.0,0.0, 1.0},128.0);//Sin brillos especulares
   oro = Material({0.24725,0.1995, 0.0745, 0.6},{0.0, 0.0, 0.0, 0.1},{0.628281, 0.555802, 0.366065, 0.1},128.0);//Sin reflectividad difusa
   bronce = Material({0.2125,0.1275,0.054,1.0},{0.714, 0.4284, 0.18144,1.0},{0.393548, 0.271906, 0.166721, 1.0},0.2);
   negro = Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.50,0.50,0.50,1.0},128*0.25);

   madera = Textura("archivosP5/text-madera.jpg",1);

   luces[0] = new LuzPosicional(GL_LIGHT1,{-100, 100, 100},{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   luces[1] = new LuzDireccional(GL_LIGHT2,{0, 0},{0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

   camaras[0] = new Camara({100,100,500},{0,0,0},{0,1,0},1,50,50);

   animacionAutomatica = animacionManual = animacionLuz = false;
   grado = -1;


   peon->setMaterial(plata);
   peon2->setMaterial(negro);
   tetraedro->setMaterial(bronce);
   cubo->setMaterial(bronce);
   hormiga->setMaterial(bronce);
   cilindro->setMaterial(plata);
   esfera->setMaterial(plata);
   alaX->setMaterial(plata);
   cuadro->setMaterial(bronce);
   
   cuadro->calcularCoordenadas();
   cuadro->setTextura(madera);
   cubo->calcularCoordenadas();
   cubo->setTextura(madera);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
    
	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
   glDisable(GL_LIGHTING);
   glEnable(GL_SMOOTH);
	change_observer();
   ejes.draw();
   

   
   if(luz){
      if(!glIsEnabled(GL_LIGHTING)){
         glEnable(GL_LIGHTING);
      }

      for(int i=0;i<8;i++){
         if(luces[i]!=nullptr && switchLuces[i])
            luces[i]->activar();
         else if(luces[i]!=nullptr && !switchLuces[i])
            glDisable(luces[i]->getID());
      }
      
      glShadeModel(GL_SMOOTH);
   }
   else{
      if(glIsEnabled(GL_LIGHTING))
         glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
   }



   glPushMatrix();
   glPointSize(6);
   switch (seleccionDibujo){
      case 1:
         glPushMatrix();
         glTranslatef(100,0,0);
         glScalef(25,25,25);
         tetraedro->setColor(0,0,1);
         tetraedro->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,100);
         glScalef(25,25,25);
         cubo->setColor(0,1,0);
         cubo->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glPushMatrix();
         glScalef(25.0,25.0,25.0);
         peon->setColor(1,0,0);
         peon->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,0);
         glScalef(3,3,3);
         hormiga->setColor(1,0,1);
         hormiga->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,-100);
         glScalef(3,3,3);
         cilindro->setColor(0,0,1);
         cilindro->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glPushMatrix();
         glTranslatef(100,0,100);
         glScalef(5,5,5);
         esfera->setColor(1,0,1);
         esfera->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         break;
      case 2:
         glEnable(GL_TEXTURE_2D);
         glPushMatrix();
         cuadro->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         
         glTranslatef(-100,0,100);
         glScalef(25,25,25);
         cubo->setColor(0,1,0);
         cubo->draw(metodoDibujado,puntos,lineas,solido,ajedrez);

         glDisable(GL_TEXTURE_2D);
         break;
      case 3:
         glPushMatrix();
         alaX->setColor(0.7,0.7,0.7);
         alaX->draw(metodoDibujado,puntos,lineas,solido,ajedrez);
         glPopMatrix();
         break;
   }
   glPopMatrix();
}



//**************************************************************************
// Funcion que anima automaticamente el modelo
//**************************************************************************

void Escena::animarModeloJerarquico(){
   if(animacionAutomatica)
      alaX->aterrizar();

   if(animacionLuz)
      luces[0]->animarLuz();
   
   
}


//**************************************************************************
// Funcion que controla si se ha pulsado alguna tecla del raton
//**************************************************************************

void Escena::clickRaton(int boton, int estado, int x, int y){
   switch(boton){
      case GLUT_RIGHT_BUTTON:
         if(estado == GLUT_DOWN){
            boton = false;
            xraton = x;
            yraton = y;
         }
         break;
      case GLUT_LEFT_BUTTON:
         boton = true;
         break;
      case 3:
         if(estado == GLUT_UP)
            camaras[numCamaraActiva]->zoom(1);
         break;
      case 4:
         if(estado == GLUT_DOWN)
            camaras[numCamaraActiva]->zoom(-1);
         break;
   }

}


//**************************************************************************
// Funcion que controla si se ha pulsado el boton derecho
//**************************************************************************
void Escena::ratonMovido(int x, int y){
   if(!boton){
      camaras[numCamaraActiva]->rotarXPrimeraPersona((x-xraton)*0.1);
      camaras[numCamaraActiva]->rotarYPrimeraPersona((y-yraton)*0.1);
      xraton = x;
      yraton = y;
   }
   else{
      
   }

}


//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   bool angulo;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout<<"Entrando en modo selección objeto"<<endl; 
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout<<"Entrando en modo selección visualización"<<endl; 
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout<<"Entrando en modo selección dibujado"<<endl; 
         break ;
         // COMPLETAR con los diferentes opciones de teclado
      case 'Y':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 1;
         break;
      case 'N':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 2;
            cout<<"Dibujando objetos texturas"<<endl; 
         break;
      case 'X':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 3;
            cout<<"Dibujando modelo jerárquico"<<endl; 
         break;
      case 'P':
         if(modoMenu == SELVISUALIZACION && !luz){
            luz = false;
            puntos = !puntos;
            cout<<"Entrando en modo puntos"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && luz)
            animacionLuz = true;
            cout<<"Animando luz puntual automáticamente"<<endl; 
         break;
      case 'L':
         if(modoMenu == SELVISUALIZACION){
            luz = false;
            lineas = !lineas;
            cout<<"Entrando en modo lineas"<<endl; 
         }
         break;
      
      case 'S':
         if(modoMenu == SELVISUALIZACION){
            luz = false;
            solido = !solido;
            cout<<"Entrando en modo caras"<<endl; 
         }
         break;
      
      case 'A':
         if(modoMenu == SELVISUALIZACION && !luz){
            luz = false;
            ajedrez = !ajedrez;
            cout<<"Entrando en modo ajedrez"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && luz){
            angulo = true;
            cout<<"Seleccion del angulo ALPHA"<<endl; 
         }
         else{
            animacionAutomatica = !animacionAutomatica;
            alaX->puntoSalida(-700,700,-700);
            cout<<"Animando modelo jerárquico automáticamente"<<endl; 
         }
         break;
         
      
      case 'M':
         if(modoMenu == SELVISUALIZACION){
            animacionAutomatica = false;
            cout<<"Selección de animación manual del modelo jerárquico"<<endl; 
         }
         break;
         
      case 'B':
         if(luz){
            angulo = false;
            cout<<"Entrando en modo selección objeto"<<endl; 
         }
         break;
      
      case 'T':
         if(modoMenu == SELVISUALIZACION){
            peon->switchTapas(tapas);
            cilindro->switchTapas(tapas);
            cono->switchTapas(tapas);
            peon2->switchTapas(tapas);
            cout<<"Activando/Desactivando tapas"<<endl; 
         }
         break;
      
      case 'I':
         if(modoMenu == SELVISUALIZACION){
            luz = !luz;
            cout<<"Activando modo iluminación"<<endl; 
         }
      case '0':
         if(modoMenu == SELVISUALIZACION && luz){
            switchLuces[0] = !switchLuces[0];
            if(switchLuces[0])
               cout<<"Activando luz 0"<<endl; 
            else
               cout<<"Desactivando luz 0"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && !luz && !animacionAutomatica){
            grado = 0;
            cout<<"Seleccion del grado 0"<<endl; 
         }
         break;
      
      case '1' :
         if(modoMenu == SELDIBUJADO)
            metodoDibujado = false;
         else if(modoMenu == SELVISUALIZACION && luz){
            switchLuces[1] = !switchLuces[1];
            if(switchLuces[1])
               cout<<"Activando luz 1"<<endl; 
            else
               cout<<"Desactivando luz 1"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION &&!luz && !animacionAutomatica){
            grado = 1;
            cout<<"Seleccion del grado 1"<<endl; 
         }
         break;
      
      case '2':
         if(modoMenu == SELDIBUJADO)
            metodoDibujado = true;
         else if(modoMenu == SELVISUALIZACION && luz){
            switchLuces[2] = !switchLuces[2];
            if(switchLuces[0])
               cout<<"Activando luz 2"<<endl; 
            else
               cout<<"Desactivando luz 2"<<endl; 
         }
         else if(modoMenu == SELVISUALIZACION && !luz && !animacionAutomatica){
            grado = 2;
            cout<<"Seleccion del grado 2"<<endl; 
         }
         break;
      
      case '3':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[3] = !switchLuces[3];
               if(switchLuces[3])
                  cout<<"Activando luz 3"<<endl; 
               else
                  cout<<"Desactivando luz 3"<<endl; 
            }
            else if(!luz && !animacionAutomatica){
               grado = 3;
               cout<<"Seleccion del grado 3"<<endl; 
            }
         break;
      
      case '4':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[4] = !switchLuces[4];
               if(switchLuces[4])
                  cout<<"Activando luz 4"<<endl; 
               else
                  cout<<"Desactivando luz 4"<<endl; 
            }
            else if(!luz && !animacionAutomatica){
               grado = 4;
               cout<<"Seleccion del grado 4"<<endl; 
            }
         break;
      
      case '5':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[5] = !switchLuces[5];
               if(switchLuces[5])
                  cout<<"Activando luz 5"<<endl; 
               else
                  cout<<"Desactivando luz 5"<<endl; 
            }
            else if(!luz && !animacionAutomatica){
               grado = 5;
               cout<<"Seleccion del grado 5"<<endl; 
            }
         break;
      
      case '6':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[6] = !switchLuces[6];
               if(switchLuces[6])
                  cout<<"Activando luz 6"<<endl; 
               else
                  cout<<"Desactivando luz 6"<<endl; 
            }
            else if(!luz && !animacionAutomatica){
               grado = 6;
               cout<<"Seleccion del grado 6"<<endl; 
            }
         break;
      
      case '7':
            if(modoMenu == SELVISUALIZACION && luz){
               switchLuces[7] = !switchLuces[7];
               if(switchLuces[7])
                  cout<<"Activando luz 7"<<endl; 
               else
                  cout<<"Desactivando luz 7"<<endl; 
            }
            else if(!luz && !animacionAutomatica){
               grado = 7;
               cout<<"Seleccion del grado 7"<<endl; 
            }
         break;
      
      case '>':
         if(luz && angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloAlpha(-1.0);
            cout<<"Variando > del angulo alfa"<<endl; 
         }
         else if(luz && !angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloBeta(-1.0);
            cout<<"Variando > del angulo beta"<<endl;  
         }
         break;
      
      case '<':
         if(luz && angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloAlpha(1.0);
            cout<<"Variando < del angulo alfa"<<endl;  
         }
         else if(luz && !angulo && modoMenu == SELVISUALIZACION){
            this->luces[1]->variarAnguloBeta(1.0);
            cout<<"Variando < del angulo beta"<<endl;  
         }
         break;
      
      case '+':
         if(modoMenu == SELVISUALIZACION){
            if(!animacionAutomatica){
               inc = 1.0;
               alaX->animacionManual(grado,inc);
            }
         }
         break;
      
      case '-':
         if(modoMenu == SELVISUALIZACION){
            if(!animacionAutomatica){
               inc = -1.0;
               alaX->animacionManual(grado,inc);
            }
         }
         break;
      

   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

