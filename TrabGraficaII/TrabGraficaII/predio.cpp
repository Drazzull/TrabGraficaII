#include "predio.h"

Predio::Predio()
{
}

Predio::Predio(GLfloat xInicial, GLfloat yInicial, int largura, int altura)
{
	this->posicaoInicial = Vector(xInicial, yInicial);
	this->largura = largura;
	this->altura = altura;
}

Predio::~Predio()
{
}

void Predio::desenhaPredio()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Rotaciona os objetos
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY(), 1.0f);

	// Desenha o objeto
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f((GLfloat)this->largura, 0.0f);
		glVertex2f((GLfloat)this->largura, (GLfloat)this->altura);
		glVertex2f(0.0f, (GLfloat)this->altura);
	}
	glEnd();
}