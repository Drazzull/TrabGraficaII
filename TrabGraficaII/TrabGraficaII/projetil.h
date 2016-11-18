#pragma once
#include <GL/glut.h>
#include "vector.h"

class Projetil
{
public:
	// Construtores
	Projetil();
	Projetil(GLfloat x, GLfloat y);

	// Destrutor
	~Projetil();

	// Setters
	void setAngulo(GLfloat valor);
	void setWidthJanela(GLfloat valor);
	void setHeightJanela(GLfloat valor);
	void setAtivo(bool valor);

	// Métodos de desenho
	void desenhaProjetil();

private:
	GLfloat angulo;
	GLfloat widthJanela;
	GLfloat heightJanela;

	bool ativo = false;

	Vector posicao;
	Vector velocidade = Vector(0.0f, 1.0f);
};