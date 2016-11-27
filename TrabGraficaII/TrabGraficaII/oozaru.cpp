#include "oozaru.h"

Oozaru::Oozaru()
{
	this->posicaoInicial = Vetor(0.0f, 0.0f);
	this->alturaMaxima = 45;
	this->larguraMaxima = 45;
}

Oozaru::Oozaru(GLfloat xInicial, GLfloat yInicial)
{
	this->posicaoInicial = Vetor(xInicial, yInicial);
	this->alturaMaxima = 45;
	this->larguraMaxima = 45;
}

Oozaru::~Oozaru()
{
}

void Oozaru::setMorto(bool valor)
{
	this->morto = valor;
}

void Oozaru::setAnimar(bool valor)
{
	this->animar = valor;
}

Vetor Oozaru::getPosicaoInicial()
{
	return this->posicaoInicial;
}

int Oozaru::getAlturaMaxima()
{
	return this->alturaMaxima;
}

int Oozaru::getLarguraMaxima()
{
	return this->larguraMaxima;
}

bool Oozaru::isMorto()
{
	return this->morto;
}

void Oozaru::desenhaOozaru()
{
	// Não desenha se estiver morto
	if (this->morto)
	{
		return;
	}

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

		if (this->animar)
		{
			glVertex2f(45.0f, 30.0f);
			glVertex2f(45.0f, 40.0f);
			glVertex2f(50.0f, 40.0f);
			glVertex2f(50.0f, 30.0f);
		}
		else
		{
			glVertex2f(45.0f, 30.0f);
			glVertex2f(45.0f, 10.0f);
			glVertex2f(50.0f, 10.0f);
			glVertex2f(50.0f, 30.0f);
		}
	}
	glEnd();
}