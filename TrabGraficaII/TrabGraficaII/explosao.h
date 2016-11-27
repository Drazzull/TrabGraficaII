#pragma once
#include <GL/glut.h>
#include "vetor.h"

class Explosao
{
public:
	// Construtores
	Explosao(GLfloat xInicial, GLfloat yInicial);

	// Destrutor
	~Explosao();

	// M�todos de desenho
	void desenhaExplosao();

private:
	// Propriedades
	Vetor posicaoInicial;
	bool explosaoTerminada;
	int contadorTermino;

	// Define a cor da explos�o
	void definirCorExplosao();
};