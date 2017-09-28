#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <algorithm>

#include "image2dx.h"

#define PIXEL_SIZE 20

static void meuPintaCena();

static void trataTeclado(unsigned char key, int x, int y);
static void trataMouseClick( int button, int state, int x, int y);
static void trataMouseMove( int x, int y);

// NOVO: imagem a ser renderizada
static Image img( 0xAC, 32, 16 );

unsigned char colorA = 0;
unsigned char colorB = 255;

void noise()
{
	// novo: preenchimento da imagem com padrão aleatório e uma linha diagonal		
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = rand() & 0xFF;
}
// =========================================================================================
void invert( )
{
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = ~img.getPixels()[i];
}
// =========================================================================================
void darker( )
{
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = (img.getPixels()[i] < 0x1) ? 0x0 : img.getPixels()[i] - 0x1;
}
// =========================================================================================
void lighter( )
{
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = (img.getPixels()[i] > 0xFE) ? 0xFF : img.getPixels()[i] + 0x1;
}
// =========================================================================================
void flipX( )
{
	for( int i=0 ; i<img.getHeight() ; ++i  )
		for( int j=0 ; j<img.getWidth()/2 ; ++j ){
			std::swap(img[i][j],img[i][img.getWidth()-1-j]);
			}
}
// =========================================================================================
void flipY( )
{
	for( int i=0 ; i<img.getHeight()/2 ; ++i  )
		for( int j=0 ; j<img.getWidth() ; ++j ){
			std::swap(img[i][j],img[img.getHeight()-1-i][j]);
			}
}
// =========================================================================================
int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitWindowSize( img.getWidth()*PIXEL_SIZE, img.getHeight()*PIXEL_SIZE );
	glutInitWindowPosition(10,10);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL );
	
	glutCreateWindow( "Editor de Imagens 2D - Pressione 'A' para Ajuda" );	
	glutDisplayFunc( meuPintaCena );	
	glutKeyboardFunc( trataTeclado );
	glutMouseFunc( trataMouseClick );
	glutMotionFunc( trataMouseMove );
	
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
	
	// gera a imagem com ruído
	//noise();
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
		std::cout << std::endl << "Comandos do Editor:" << std::endl;
		std::cout << "\tW para limpar a imagem com branco" << std::endl;
		std::cout << "\tB para limpar a imagem com branco" << std::endl;
		std::cout << "\tN para uma imagem com ruído" << std::endl;
		std::cout << "\t+ e - para alterar a cor principal" << std::endl;
		break;
	case '-':
		colorA -= 1;
		break;
	case '+':
		colorA += 1;
		break;
	case 'w': case 'W': 
		img.clear( 255 );		
		break;
	case 'b': case 'B': 
		img.clear(0);
		break;
	case 'n':  case 'N':
		noise();
		break;
	case 'i':  case 'I':
		invert();
		break;
	case '/':
		lighter();
		break;
	case '*':
		darker();
		break;
	case '6':
		flipX();
		break;
	case '2':
		flipY();
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
		color = (button==0)?  colorA : colorB;
		img.setPixelSafe( color, x, y );

	}else
	if( state == GLUT_UP )
	{
		color = -1;
	}
}

void trataMouseMove( int x, int y)
{
	x/=PIXEL_SIZE, y/=PIXEL_SIZE;

	if( color != -1 )
	{		
		img.setPixelSafe( color, x, y );
	}
}

