#pragma once
#include <GL/glut.h>
#include "vetor.h"

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

	// Getters
	Vetor getPosicao();
	int getRaio();

	// Setters
	void setSolAcertado(bool valor);

private:
	// Propriedades
	Vetor posicaoInicial;
	bool solAcertado;
	int raioCentral;

	// Fazer os coeficientes de bezier
	void coeficientesBezier(int n, int *c);

	// M�todos de desenho
	void desenhaOlhos();
	void desenhaBoca();
};