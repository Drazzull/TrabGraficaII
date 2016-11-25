#pragma once
#include <GL/glut.h>
#include "vector.h"

class Sol
{
public:
	// Construtores
	Sol();
	Sol(GLfloat xInicial, GLfloat yInicial);

	// Destrutor
	~Sol();

	// M�todos de desenho
	void desenhaSol();

private:
	// Propriedades
	Vector posicaoInicial;
	bool solAcertado;
	int controleSolAcertado;

	// Fazer os coeficientes de bezier
	void coeficientesBezier(int n, int *c);

	// M�todos de desenho
	void desenhaOlhos();
	void desenhaBoca();
};

