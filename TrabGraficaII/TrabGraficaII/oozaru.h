#pragma once
#include <GL/glut.h>
#include "vetor.h"

class Oozaru
{
public:
	// Construtores
	Oozaru();
	Oozaru(GLfloat xInicial, GLfloat yInicial);

	// Destrutor
	~Oozaru();

	// Setters
	void setMorto(bool valor);

	// Getters
	Vetor getPosicaoInicial();

	// Métodos de desenho
	void animarBraco();
	void desenhaOozaru();

private:
	Vetor posicaoInicial;
	bool morto = false;
	bool animar = false;
	int contadorAnimacao = 0;
};