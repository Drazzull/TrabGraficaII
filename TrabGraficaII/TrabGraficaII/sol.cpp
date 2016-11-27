#include "sol.h"
#include <math.h>

Sol::Sol()
{
	this->solAcertado = false;
	this->posicaoInicial = Vetor(0, 0);
	this->raioCentral = 40;
}

Sol::Sol(GLfloat xInicial, GLfloat yInicial)
{
	this->solAcertado = false;
	this->posicaoInicial = Vetor(xInicial, yInicial);
	this->raioCentral = 40;
}

Sol::~Sol()
{
}

// Getters
Vetor Sol::getPosicao()
{
	return this->posicaoInicial;
}

int Sol::getRaio()
{
	return this->raioCentral;
}

// Setters
void Sol::setSolAcertado(bool valor)
{
	this->solAcertado = valor;
}

void Sol::coeficientesBezier(int n, int *c)
{
	int k, i;
	for (k = 0; k <= n; k++)
	{
		c[k] = 1;
		for (i = n; i >= k + 1; i--)
		{
			c[k] *= i;
		}

		for (i = n - k; i >= 2; i--)
		{
			c[k] /= i;
		}
	}
}

void Sol::desenhaBoca()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Desenha a boca normal
	if (!this->solAcertado)
	{
		// Inicializa o objeto
		glTranslatef(this->posicaoInicial.getX() - 25, this->posicaoInicial.getY() - 17, 1.0f);

		// Pontos utilizados para desenhar a curva da boca
		int cp[4][2] = { { 0, 0 },{ 5, -10 },{ 45, -10 },{ 50, 0 } };
		int c[4];
		int k;
		int n = 3;
		GLfloat x;
		GLfloat y;
		GLfloat u;
		GLfloat blend;

		// Calcula os coeficientes para a curva
		coeficientesBezier(n, c);

		// Desenha a curva
		glBegin(GL_LINE_STRIP);
		{
			for (u = 0; u < 1.0; u += 0.01)
			{
				x = 0;
				y = 0;
				for (k = 0; k < 4; k++)
				{
					blend = c[k] * pow(u, k) * pow(1 - u, n - k);
					x += cp[k][0] * blend;
					y += cp[k][1] * blend;
				}

				glVertex2f(x, y);
			}
		}
		glEnd();


		// Sai do método
		return;
	}

	// Desenha a boca se ela foi acertada
	// Inicializa o objeto
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY() - 17, 1.0f);

	// Desenha o objeto
	glColor3ub(0, 0, 0);
	GLfloat raio = 12;
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

void Sol::desenhaOlhos()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Desenha os olhos
	glTranslatef(this->posicaoInicial.getX() - 15, this->posicaoInicial.getY() + 10, 1.0f);

	// Desenha o objeto
	glColor3ub(0, 0, 0);
	GLfloat raio = 5;
	glBegin(GL_POLYGON);
	{
		for (int angulo = 0; angulo <= 360; angulo++)
		{
			GLfloat x = (GLfloat)raio * cos(angulo * PI / 180);
			GLfloat y = (GLfloat)raio * sin(angulo * PI / 180) * 2;
			glVertex2f(x, y);
		}
	}
	glEnd();

	// Carrega a matriz de identidade
	glLoadIdentity();

	// Desenha os olhos
	glTranslatef(this->posicaoInicial.getX() + 15, this->posicaoInicial.getY() + 10, 1.0f);

	// Desenha o objeto
	glColor3ub(0, 0, 0);
	raio = 5;
	glBegin(GL_POLYGON);
	{
		for (int angulo = 0; angulo <= 360; angulo++)
		{
			GLfloat x = (GLfloat)raio * cos(angulo * PI / 180);
			GLfloat y = (GLfloat)raio * sin(angulo * PI / 180) * 2;
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void Sol::desenhaSol()
{
	// Carrega a matriz de identidade
	glLoadIdentity();

	// Inicializa a posição do objeto
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY(), 1.0f);

	// Desenha o objeto
	glColor3ub(255, 255, 255);
	GLfloat raio = this->raioCentral + 10;
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

	// Desenha o objeto
	glColor3ub(255, 255, 150);
	raio = this->raioCentral + 7;
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

	// Desenha o objeto
	glColor3ub(255, 255, 100);
	raio = this->raioCentral + 5;
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

	// Desenha o objeto
	glColor3ub(255, 255, 0);
	raio = this->raioCentral;
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

	// Desenha os olhos
	desenhaOlhos();

	// Desenha a boca
	desenhaBoca();
}