#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include "vector.h"
#include "projetil.h"
#include "predio.h"
#include "oozaru.h"
#include "sol.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Tempo de refresh da tela
int tempoRefresh = 30;

// Predios
const int numeroPredios = 10;
Predio predios[numeroPredios];

// Gorilas
Oozaru oozarus[2];

// Sol
Sol sol;

// Define os tamanhos da janela
GLfloat width = 1024.0f;
GLfloat height = 768.0f;

// M�todo pra definir os pr�dios
void carregarPredios()
{
	// Define as posi��es iniciais do primeiro pr�dio
	GLfloat yInicial = 10.0f;
	GLfloat xInicial = 2.0f;

	// Vari�veis pra controle da altura e largura
	int largura = 0;
	int altura = 0;
	int percTela = (int)(height * 25) / 100;

	// Percorre o array dos pr�dios
	for (int i = 0; i < numeroPredios; i++)
	{
		// Definir a altura e largura randon�micamente
		altura = rand() % percTela + percTela;
		largura = rand() % 150 + 50;

		// Define o pr�dio
		predios[i] = Predio(xInicial, yInicial, largura, altura);

		// Define a posi��o inicial do pr�ximo pr�dio
		xInicial = xInicial + largura + 2;
	}
}

GLfloat ObterAlturaPredio(GLfloat x)
{
	// Desenha os pr�dios
	for (int i = 0; i < numeroPredios; i++)
	{
		if (predios[i].getPosicao().getX() + predios[i].getLargura() >= x)
		{
			return predios[i].getPosicao().getY() + predios[i].getAltura();
		}
	}

	return 0.0f;
}

GLfloat ObterLarguraPredio(GLfloat x)
{
	// Desenha os pr�dios
	for (int i = 0; i < numeroPredios; i++)
	{
		if (predios[i].getPosicao().getX() + predios[i].getLargura() >= x)
		{
			return predios[i].getPosicao().getX();
		}
	}

	return 0.0f;
}

// M�todo pra definir os gorilas
void carregarOozarus()
{
	// Calcula o tamanho da tela pela metade
	int percTela = (int)(width / 2);

	// Calcula o X Inicial do primeiro gorila
	GLfloat xInicial = rand() % percTela;
	if (xInicial < 0)
	{
		xInicial = 0;
	}

	// Obt�m a altura do pr�dio abaixo do gorila
	GLfloat yInicial = ObterAlturaPredio(xInicial + 50);

	// Recalcula o X para garantir que v� ficar sobre o pr�dio
	xInicial = ObterLarguraPredio(xInicial + 50);

	// Define as posi��es iniciais do primeiro gorila
	oozarus[0] = Oozaru(xInicial, yInicial);

	// Calcula o X Inicial do segundo gorila
	xInicial = rand() % percTela + percTela;
	if (xInicial > 904)
	{
		xInicial = 904;
	}

	// Obt�m a altura do pr�dio abaixo do gorila
	yInicial = ObterAlturaPredio(xInicial + 50);

	// Recalcula o X para garantir que v� ficar sobre o pr�dio
	xInicial = ObterLarguraPredio(xInicial + 50);

	// Verifica se os dois gorilas ficaram com a mesma posi��o
	if (xInicial == oozarus[0].getPosicaoInicial().getX())
	{
		xInicial += 200;
		xInicial = ObterLarguraPredio(xInicial + 50);
	}

	// Define as posi��es iniciais do segundo gorila
	oozarus[1] = Oozaru(xInicial, yInicial);
}

// M�todo principal de desenho
void desenha()
{
	// Limpa as matrizes
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Desenha os pr�dios
	for (int i = 0; i < numeroPredios; i++)
	{
		predios[i].desenhaPredio();
	}

	// Desenha os gorillas
	oozarus[0].desenhaOozaru();
	oozarus[1].desenhaOozaru();

	// Desenha o sol
	sol.desenhaSol();

	glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		//Tecla ESC
		exit(0);
		break;

	case 32:
		// Tecla SPACE
		break;
	}
}

void timer(int valor)
{
	glutPostRedisplay();
	glutTimerFunc(tempoRefresh, timer, 0);
}

int main(int argc, char **argv)
{
	// Inicializa o seed do random
	srand(time(NULL));

	// Inicializa a biblioteca do glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize((int)width, (int)height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Gorillas - Arthur B. Bilibio, Johnatan da Rosa, Wagner Casagrande");

	// Definir Pr�dios
	carregarPredios();

	// Definir posi��o dos gorillas
	carregarOozarus();

	// Define a posi��o inicial do sol
	sol = Sol(width / 2, height - 70);

	// Define o tipo da proje��o
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

	glutDisplayFunc(desenha);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(teclado);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return(0);
}