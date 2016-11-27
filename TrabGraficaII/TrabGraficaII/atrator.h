#pragma once
#include "projetil.h"

class Atrator
{
public:
	Atrator();
	~Atrator();
	
	// Setters
	void setGravidade(GLfloat valor);

	// Calcula a atração
	Vetor calcularAtracao(Projetil m);

private:
	Vetor pos;
	Vetor dragOffset;
	GLfloat massa, G;

	float constrain(float value, float min, float max);
};

