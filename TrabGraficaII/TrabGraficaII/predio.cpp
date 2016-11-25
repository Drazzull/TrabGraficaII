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

// Getters
Vector Predio::getPosicao()
{
	return this->posicaoInicial;
}

int Predio::getLargura()
{
	return this->largura;
}

int Predio::getAltura()
{
	return this->altura;
}

void Predio::desenhaPredio()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Inicializa a posição do objeto
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY(), 1.0f);

	// Desenha o objeto
	glColor3ub(192, 192, 192);
	glBegin(GL_QUADS);
	{
		glVertex2f(0.0f, 0.0f);
		glVertex2f((GLfloat)this->largura, 0.0f);
		glVertex2f((GLfloat)this->largura, (GLfloat)this->altura);
		glVertex2f(0.0f, (GLfloat)this->altura);
	}
	glEnd();
}