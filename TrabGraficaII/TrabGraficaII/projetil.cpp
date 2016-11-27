#include "projetil.h"

Projetil::Projetil()
{
	this->massa = (this->largura / this->altura * 5);
	this->velocidade = Vetor(0.f, 0.f);
	this->aceleracao = Vetor(0.f, 0.f);
}

Projetil::Projetil(GLfloat x, GLfloat y)
{
	this->posicaoInicial = Vetor(x, y);
	this->massa = (this->largura / this->altura * 5);
	this->velocidade = Vetor(0.f, 0.f);
	this->aceleracao = Vetor(0.f, 0.f);
}

Projetil::~Projetil()
{
}

void Projetil::aplicarForca(Vetor forca)
{
	forca.div(this->massa);
	this->aceleracao.add(forca);
}

void Projetil::atualizar()
{
	this->velocidade.add(this->aceleracao);
	this->posicaoInicial.add(this->velocidade);
	this->aceleracao.mult(0);
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

GLfloat Projetil::getMassa()
{
	return this->massa;
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
	// N�o desenha se n�o tiver ativo
	if (!this->ativo)
	{
		return;
	}

	// Carrega a matriz de identidade
	glLoadIdentity();

	// Inicializa a posi��o do objeto
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