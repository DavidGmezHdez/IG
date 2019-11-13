#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

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
   hormiga = new ObjPLY("plys/ant.ply");
   peon = new ObjRevolucion("plys/peon.ply",30,tapas,tapas);
   peon2 = new ObjRevolucion("plys/peon.ply",30,tapas,tapas);
   cilindro = new Cilindro(50,25,10);
   cono = new Cono(50,25,10);
   esfera = new Esfera(50,50,10);
   m = Material({1.0,1.0,1.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},128.0);
   
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
	change_observer();
   ejes.draw();

   ajedrez = false;
   switch (modoVisualizacion){
      case 1:
         glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
         break;
      case 2:
         glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         break;
      case 3:
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         break;
      case 4:
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         ajedrez = true;
         break;
   }
   glPushMatrix();
   glPointSize(6);

   if(luces)
      glEnable(GL_LIGHTING);
   else
      glDisable(GL_LIGHTING);
   
   switch (seleccionDibujo){
      case 1:
         glPushMatrix();
         glScalef(25,25,25);
         tetraedro->setColor(0,0,1);
         tetraedro->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
      
      case 2:
         glPushMatrix();
         glScalef(25,25,25);
         cubo->setColor(0,1,0);
         cubo->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
      
      case 3:
         glPushMatrix();
         glScalef(25.0,25.0,25.0);
         peon->setColor(1,0,0);
         peon->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
      
      case 4:
         glPushMatrix();
         glScalef(3,3,3);
         hormiga->setColor(1,0,1);
         hormiga->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
      
      case 5:
         glPushMatrix();
         glScalef(3,3,3);
         cilindro->setColor(0,0,1);
         cilindro->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
      
      case 6:
         glPushMatrix();
         glScalef(3,3,3);
         cono->setColor(0,1,0);
         cono->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;    

      case 7:
         glPushMatrix();
         glScalef(5,5,5);
         esfera->setColor(1,0,1);
         esfera->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix(); 
         break;

      case 8:
         glPushMatrix();
         glTranslatef(100,0,0);
         glScalef(25,25,25);
         tetraedro->setColor(0,0,1);
         tetraedro->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,100);
         glScalef(25,25,25);
         cubo->setColor(0,1,0);
         cubo->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         
         glPushMatrix();
         glScalef(25.0,25.0,25.0);
         peon->setColor(1,0,0);
         peon->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,0);
         glScalef(3,3,3);
         hormiga->setColor(1,0,1);
         hormiga->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-100,0,-100);
         glScalef(3,3,3);
         cilindro->setColor(0,0,1);
         cilindro->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(100,0,-100);
         glScalef(3,3,3);
         cono->setColor(0,1,0);
         cono->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix(); 

         glPushMatrix();
         glTranslatef(100,0,100);
         glScalef(5,5,5);
         esfera->setColor(1,0,1);
         esfera->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
      case 9:
         glPushMatrix();
         glTranslatef(-100,0,0);
         glScalef(25.0,25.0,25.0);
         peon->setColor(1,0,0);
         peon->setMaterial(m);
         peon->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(100,0,0);
         glScalef(25.0,25.0,25.0);
         peon2->setColor(1,0,0);
         peon2->setMaterial(m);
         peon2->draw(metodoDibujado,ajedrez,luces);
         glPopMatrix();
         break;
   }
   glPopMatrix();
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
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
      case 'C' :
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 2;
         break;
      case 'T' :
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 1;
         break;
      
      case 'K' :
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 3;
         break;
      
      case 'J':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 4;
         break;

      case 'H':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 5;
         break;
      
      case 'G':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 6;
         break;
      
      case 'E':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 7;
         break;
      
      case 'Y':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 8;
         break;
      case 'N':
         if(modoMenu == SELOBJETO)
            seleccionDibujo = 9;
         break;


      case 'P':
         if(modoMenu == SELVISUALIZACION)
            modoVisualizacion = 1;
         break;
      case 'L':
         if(modoMenu == SELVISUALIZACION)
            modoVisualizacion = 2;
         break;
      case 'S':
         if(modoMenu == SELVISUALIZACION)
            modoVisualizacion = 3;
         break;
      case 'A':
         if(modoMenu == SELVISUALIZACION)
            modoVisualizacion = 4;
         break;
      case 'M':
         if(modoMenu == SELVISUALIZACION){
            peon->switchTapas(tapas);
            cilindro->switchTapas(tapas);
            cono->switchTapas(tapas);
         }
         break;
      case 'I':
         if(modoMenu == SELVISUALIZACION)
            luces = !luces;
      case 1 :
         if(modoMenu == SELDIBUJADO)
            metodoDibujado = false;
         break;
      case 2:
         if(modoMenu == SELDIBUJADO)
            metodoDibujado = true;
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
