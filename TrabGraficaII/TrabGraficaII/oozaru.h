#pragma once
#include <GL/glut.h>
#include "vector.h"

class Oozaru
{
public:
	// Construtores
	Oozaru();
	Oozaru(GLfloat xInicial, GLfloat yInicial);

	// Destrutor
	~Oozaru();

	// Getters
	Vector getPosicaoInicial();

	// Métodos de desenho
	void desenhaOozaru();

private:
	Vector posicaoInicial;
};