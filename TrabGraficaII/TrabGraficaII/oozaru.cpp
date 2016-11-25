#include "oozaru.h"

Oozaru::Oozaru()
{
}

Oozaru::Oozaru(GLfloat xInicial, GLfloat yInicial)
{
	this->posicaoInicial = Vector(xInicial, yInicial);
}

Oozaru::~Oozaru()
{
}

Vector Oozaru::getPosicaoInicial()
{
	return this->posicaoInicial;
}

void Oozaru::desenhaOozaru()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Inicializa a posição do objeto
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY(), 1.0f);

	// Define a cor do objeto
	glColor3ub(255, 100, 255);

	// Desenha o objeto
	glBegin(GL_QUADS);
	{
		glVertex2f(10.0f, 0.0f);
		glVertex2f(20.0f, 0.0f);
		glVertex2f(20.0f, 30.0f);
		glVertex2f(10.0f, 30.0f);

		glVertex2f(20.0f, 10.0f);
		glVertex2f(30.0f, 10.0f);
		glVertex2f(30.0f, 40.0f);
		glVertex2f(20.0f, 40.0f);

		glVertex2f(30.0f, 0.0f);
		glVertex2f(40.0f, 0.0f);
		glVertex2f(40.0f, 30.0f);
		glVertex2f(30.0f, 30.0f);

		glVertex2f(0.0f, 30.0f);
		glVertex2f(0.0f, 10.0f);
		glVertex2f(5.0f, 10.0f);
		glVertex2f(5.0f, 30.0f);

		glVertex2f(0.0f, 20.0f);
		glVertex2f(0.0f, 30.0f);
		glVertex2f(50.0f, 30.0f);
		glVertex2f(50.0f, 20.0f);

		glVertex2f(45.0f, 30.0f);
		glVertex2f(45.0f, 10.0f);
		glVertex2f(50.0f, 10.0f);
		glVertex2f(50.0f, 30.0f);

	}
	glEnd();
}