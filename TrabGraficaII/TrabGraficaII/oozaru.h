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
	void setAnimarEsquerdo(bool valor);
	void setAnimarDireito(bool valor);

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
	int larguraMaxima;
	int alturaMaxima;

	// Anima o braço de lançamento
	bool animarDireito = false;

	// Anima ambos os braços
	bool animarEsquerdo = false;
};