#include "projetil.h"

Projetil::Projetil()
{
}

Projetil::Projetil(GLfloat x, GLfloat y)
{
	this->posicaoInicial = Vetor(x, y);
}

Projetil::~Projetil()
{
}

void Projetil::setAngulo(GLfloat valor)
{
	this->angulo = valor;
}

void Projetil::setPosicaoInicial(GLfloat x, GLfloat y)
{
	this->posicaoInicial = Vetor(x, y);
}

int Projetil::getLargura()
{
	return this->largura;
}

int Projetil::getAltura()
{
	return this->altura;
}

Vetor Projetil::getPosicaoInicial()
{
	return this->posicaoInicial;
}

bool Projetil::isAtirado()
{
	return this->atirado;
}

GLfloat Projetil::getMagnitudeLancamento()
{
	return this->magnitudeLancamento;
}

void Projetil::setAtivo(bool valor)
{
	this->ativo = valor;
}

void Projetil::setAtirado(bool valor)
{
	this->atirado = valor;
}

void Projetil::setDirecaoLancamento(char valor)
{
	this->direcaoLancamento = valor;
}

void Projetil::setVelocidadeLancamento(GLfloat valor)
{
	this->velocidadeLancamento = valor;
}

void Projetil::setMagnitudeLancamento(GLfloat valor)
{
	this->magnitudeLancamento = valor;
}

void Projetil::desenhaProjetil()
{
	// Não desenha se não tiver ativo
	if (!this->ativo)
	{
		return;
	}

	// Carrega a matriz de identidade
	glLoadIdentity();

	// Inicializa a posição do objeto
	glTranslatef(this->posicaoInicial.getX(), this->posicaoInicial.getY(), 1.0f);

	// Define a cor do objeto
	glColor3ub(255, 255, 0);

	// Desenha o 
	glBegin(GL_QUADS);
	{
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 10.0f);
		glVertex2f(5.0f, 10.0f);
		glVertex2f(5.0f, 0.0f);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(10.0f, 0.0f);
		glVertex2f(10.0f, 5.0f);
		glVertex2f(0.0f, 5.0f);
	}
	glEnd();
}