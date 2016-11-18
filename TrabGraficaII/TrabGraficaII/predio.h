#pragma once
#include <GL/glut.h>
#include "vector.h"

class Predio
{
public:
	// Construtores
	Predio();
	Predio(GLfloat xInicial, GLfloat yInicial, int largura, int altura);

	// Destrutor
	~Predio();

	// Métodos de desenho
	void desenhaPredio();

private:
	Vector posicaoInicial;
	int largura;
	int altura;
};