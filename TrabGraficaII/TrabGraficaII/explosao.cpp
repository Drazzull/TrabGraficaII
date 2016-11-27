#include "explosao.h"

Explosao::Explosao(GLfloat xInicial, GLfloat yInicial)
{
	this->explosaoTerminada = false;
	this->contadorTermino = 0;
	this->posicaoInicial = Vetor(xInicial, yInicial);
}


Explosao::~Explosao()
{
}

void Explosao::desenhaExplosao()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Inicializa a posição do objeto
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY(), 1.0f);

	// Desenha o objeto
	if (this->explosaoTerminada)
	{
		glColor3ub(0, 0, 0);
	}
	else
	{
		glColor3ub(255, 255, 0);

		// Verifica se a explosão terminou
		contadorTermino++;
		if (contadorTermino == 5)
		{
			this->explosaoTerminada = true;
		}
	}

	int raio = 15;
	glBegin(GL_POLYGON);
	{
		for (int angulo = 0; angulo <= 360; angulo++)
		{
			GLfloat x = (GLfloat)raio * cos(angulo * PI / 180);
			GLfloat y = (GLfloat)raio * sin(angulo * PI / 180);
			glVertex2f(x, y);
		}
	}
	glEnd();
}