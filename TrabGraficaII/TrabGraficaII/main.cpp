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

// Método pra definir os prédios
void carregarPredios()
{
	// Define as posições iniciais do primeiro prédio
	GLfloat yInicial = 10.0f;
	GLfloat xInicial = 2.0f;

	// Variáveis pra controle da altura e largura
	int largura = 0;
	int altura = 0;
	int percTela = (int)(height * 25) / 100;

	// Percorre o array dos prédios
	for (int i = 0; i < numeroPredios; i++)
	{
		// Definir a altura e largura randonômicamente
		altura = rand() % percTela + percTela;
		largura = rand() % 150 + 50;

		// Define o prédio
		predios[i] = Predio(xInicial, yInicial, largura, altura);

		// Define a posição inicial do próximo prédio
		xInicial = xInicial + largura + 2;
	}
}

GLfloat ObterAlturaPredio(GLfloat x)
{
	// Desenha os prédios
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
	// Desenha os prédios
	for (int i = 0; i < numeroPredios; i++)
	{
		if (predios[i].getPosicao().getX() + predios[i].getLargura() >= x)
		{
			return predios[i].getPosicao().getX();
		}
	}

	return 0.0f;
}

// Método pra definir os gorilas
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

	// Obtém a altura do prédio abaixo do gorila
	GLfloat yInicial = ObterAlturaPredio(xInicial + 50);

	// Recalcula o X para garantir que vá ficar sobre o prédio
	xInicial = ObterLarguraPredio(xInicial + 50);

	// Define as posições iniciais do primeiro gorila
	oozarus[0] = Oozaru(xInicial, yInicial);

	// Calcula o X Inicial do segundo gorila
	xInicial = rand() % percTela + percTela;
	if (xInicial > 904)
	{
		xInicial = 904;
	}

	// Obtém a altura do prédio abaixo do gorila
	yInicial = ObterAlturaPredio(xInicial + 50);

	// Recalcula o X para garantir que vá ficar sobre o prédio
	xInicial = ObterLarguraPredio(xInicial + 50);

	// Verifica se os dois gorilas ficaram com a mesma posição
	if (xInicial == oozarus[0].getPosicaoInicial().getX())
	{
		xInicial += 200;
		xInicial = ObterLarguraPredio(xInicial + 50);
	}

	// Define as posições iniciais do segundo gorila
	oozarus[1] = Oozaru(xInicial, yInicial);
}

// Método principal de desenho
void desenha()
{
	// Limpa as matrizes
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Desenha os prédios
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

	// Definir Prédios
	carregarPredios();

	// Definir posição dos gorillas
	carregarOozarus();

	// Define a posição inicial do sol
	sol = Sol(width / 2, height - 70);

	// Define o tipo da projeção
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