#pragma once
#include <GL/glut.h>
#include "vetor.h"

class Predio
{
public:
	// Construtores
	Predio();
	Predio(GLfloat xInicial, GLfloat yInicial, int largura, int altura);

	// Destrutor
	~Predio();

	// Getters
	Vetor getPosicao();
	int getLargura();
	int getAltura();

	// M�todos de desenho
	void desenhaPredio();

private:
	Vetor posicaoInicial;
	int largura;
	int altura;
};