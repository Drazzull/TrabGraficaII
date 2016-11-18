#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include "vector.h"
#include "projetil.h"
#include "predio.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Tempo de refresh da tela
int tempoRefresh = 30;

// Predios
const int numeroPredios = 10;
Predio predios[numeroPredios];

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
		largura = rand() % 150 + 75;

		// Define o prédio
		predios[i] = Predio(xInicial, yInicial, largura, altura);

		// Define a posição inicial do próximo prédio
		xInicial = xInicial + largura + 2;
	}
}

void desenha()
{
	// Limpa as matrizes
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Desenha os projéteis
	for (int i = 0; i < numeroPredios; i++)
	{
		predios[i].desenhaPredio();
	}
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