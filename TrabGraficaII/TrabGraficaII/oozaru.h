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
	void setAnimar(bool valor);

	// Getters
	Vetor getPosicaoInicial();
	int getAlturaMaxima();
	int getLarguraMaxima();
	bool isMorto();

	// Métodos de desenho
	void desenhaOozaru();

private:
	Vetor posicaoInicial;
	bool morto = false;
	bool animar = false;
	int larguraMaxima;
	int alturaMaxima;
};