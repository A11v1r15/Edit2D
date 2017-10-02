#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <algorithm>

#include "image2dx.h"

#define PIXEL_SIZE 15

static void meuPintaCena();

static void trataTeclado(unsigned char key, int x, int y);
static void trataMouseClick( int button, int state, int x, int y);
static void trataMouseMove( int x, int y);

// Imagem a ser renderizada
static Image img( 0xFF, 10, 12 );
// Imagem resolvida
static Image res( 0xFF, 10, 12 );

unsigned char colorA = 0;
unsigned char colorB = 255;

void newGame( ){
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = ((rand() & 0xFF) > 0xE0) ? 0x00 : 0xFF;
	for( int i=0; i<img.getHeight(); ++i )
		for( int j=0; j<img.getWidth(); ++j ){
			if (i > 0 && img.getPixel( i - 1, j) == 0x00)
				img.setPixel( img.getPixel(i, j) - 25, i, j);
			if (i < img.getWidth() - 1 && img.getPixel( i + 1, j) == 0x00)
				img.setPixel( img.getPixel(i, j) - 25, i, j);
			if (j > 0 && img.getPixel( i, j - 1) == 0x00)
				img.setPixel( img.getPixel(i, j) - 25, i, j);
			if (j < img.getHeight() - 1 && img.getPixel( i, j + 1) == 0x00)
				img.setPixel( img.getPixel(i, j) - 25, i, j);
		}
}

int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitWindowSize( img.getWidth()*PIXEL_SIZE, img.getHeight()*PIXEL_SIZE );
	glutInitWindowPosition(10,10);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL );
	
	glutCreateWindow( "Campo Minado - Pressione 'A' para Ajuda" );	
	glutDisplayFunc( meuPintaCena );	
	glutKeyboardFunc( trataTeclado );
	glutMouseFunc( trataMouseClick );
	glutMotionFunc( trataMouseMove );
	
	newGame();
	glutMainLoop();
	
	return 0;
}

static void meuPintaCena()
{	
	// =======================================================
	glClearColor(0,0,0,0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	
	// =======================================================
	glLoadIdentity();	
	
	// exibe a imagem
	img.display();	
	
	glutSwapBuffers();
	glutPostRedisplay();	
}

void trataTeclado( unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'A': case 'a': 
		std::cout << std::endl << "Comandos d'O Jogo (você perdeu):" << std::endl;
		std::cout << "\tN para iniciar um novo jogo" << std::endl;
		std::cout << "\tEsc para sair do jogo" << std::endl;
		break;
	case 'n':  case 'N':
		newGame();
		break;
	// Tecla "ESC"
	case 27:
		exit(-1);
		break; 	
	}
}

int color = -1;

void trataMouseClick( int button, int state, int x, int y)
{
	x/=PIXEL_SIZE, y/=PIXEL_SIZE;
	
	if( state == GLUT_DOWN )
	{
		color = (button==0)?  res.getPixel( x , y ) : colorB;
		img.setPixelSafe( color, x, y );

	}else
	if( state == GLUT_UP )
	{
		color = -1;
	}
}

void trataMouseMove( int x, int y)
{/*
	x/=PIXEL_SIZE, y/=PIXEL_SIZE;

	if( color != -1 )
	{		
		img.setPixelSafe( color, x, y );
	}
*/}
