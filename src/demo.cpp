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

// NOVO: imagem a ser renderizada
static Image img( 0xAC, 10, 12 );

unsigned char colorA = 0;
unsigned char colorB = 255;

// =========================================================================================
void flipH()
{
	const int W = img.getWidth();
	const int halfW = img.getWidth()/2;

	for( int r=0 ; r<img.getHeight() ; ++r  )
	{
		for( int c=0 ; c<halfW ; ++c  )
		{
			std::swap( img[r][c], img[r][W-c-1] );
		}
	}
}
// =========================================================================================
void flipV()
{
	const int H = img.getHeight();
	const int halfH = img.getHeight()/2;

	for( int r=0 ; r<halfH ; ++r  )
	{
		for( int c=0 ; c<img.getWidth() ; ++c  )
		{
			std::swap( img[r][c], img[H-r-1][c] );
		}
	}
}
// =========================================================================================
void noise()
{
	// novo: preenchimento da imagem com padrão aleatório e uma linha diagonal		
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = rand() & 0xFF;
}
// =========================================================================================
void invert()
{
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
		img.getPixels()[i] = ~img.getPixels()[i];
}
// =========================================================================================
void multiply( float f )
{
	for( int i=0 ; i<img.getPixelCount() ; ++i  )
	{
		img.getPixels()[i] = std::max( (pixel)0, (pixel)std::min( (int)0xFF, (int)(img.getPixels()[i]*f)) );
	}
}
// =========================================================================================
void rotate( int a )
{
	Image rot( '@', img.getHeight(), img.getWidth() );

	if (a == 1){
		for( int i=0; i<img.getHeight(); ++i )
			for( int j=0; j<img.getWidth(); ++j )
			{
				rot[j][i] = img[i][ img.getWidth() - 1 - j];
			}

		img = rot;

		glutReshapeWindow(img.getWidth()*PIXEL_SIZE, img.getHeight()*PIXEL_SIZE );
	} else if (a == -1){
		for( int i=0; i<img.getHeight(); ++i )
			for( int j=0; j<img.getWidth(); ++j )
			{
				rot[j][i] = img[ img.getHeight() - 1 - i][j];
			}

		img = rot;

		glutReshapeWindow(img.getWidth()*PIXEL_SIZE, img.getHeight()*PIXEL_SIZE );	
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
	case '1':
		img.hline( 0x66, img.getHeight()/2, 0, img.getWidth());
		break;
	case '2':
		img.vline( 0x66, img.getWidth()/2, 0, img.getHeight());
		break;
	case '3':
		img.drawRect( 0x99, 0, 0, img.getHeight()/2, img.getWidth() / 2);
		break;
	case '4':
		img.fillRect( 0x66, 0, 0 ,img.getHeight()/2, img.getWidth() / 2);
		break;
	case 'A': case 'a': 
		std::cout << std::endl << "Comandos do Editor:" << std::endl;
		std::cout << "\tW para limpar a imagem com branco" << std::endl;
		std::cout << "\tB para limpar a imagem com branco" << std::endl;
		std::cout << "\tN para uma imagem com ruído" << std::endl;
		std::cout << "\tI para inverter a imagem" << std::endl;
		std::cout << "\tH para espelhar a imagem horizontalmente" << std::endl;
		std::cout << "\tV para espelhar a imagem verticalmente" << std::endl;
		std::cout << "\tR para rotacionar imagem no sentido anti" << std::endl;
		std::cout << "\tE para rotacionar imagem no sentido anti-horario" << std::endl;
		std::cout << "\t+ e - para alterar a cor principal" << std::endl;
		std::cout << "\tZ e X para alterar a cor da imagem inteira" << std::endl;
		std::cout << "\tEsc para sair do jogo" << std::endl;
		break;
	case '-':
		colorA -= 1;
		break;
	case '+':
		colorA += 1;
		break;
	case 'h': case 'H':
		flipH();
		break;
	case 'r': case 'R':
	{
		rotate(1);
		break;
	}
	case 'e': case 'E':
	{
		rotate(-1);
		break;
	}
	case 'v': case 'V':
		flipV();
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
	case 'z':  case 'Z':
		multiply(1.1f);
		break;
	case 'x':  case 'X':
		multiply(0.9f);
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