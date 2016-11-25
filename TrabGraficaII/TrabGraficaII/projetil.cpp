#include "projetil.h"

Projetil::Projetil()
{
}

Projetil::Projetil(GLfloat x, GLfloat y)
{
	this->posicao = Vector(x, y);
}

Projetil::~Projetil()
{
}

void Projetil::setAngulo(GLfloat valor)
{
	this->angulo = valor;
}

void Projetil::setHeightJanela(GLfloat valor)
{
	this->heightJanela = valor;
}

void Projetil::setWidthJanela(GLfloat valor)
{
	this->widthJanela = valor;
}

void Projetil::setAtivo(bool valor)
{
	this->ativo = valor;
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
	glTranslatef(this->widthJanela / 2, this->heightJanela / 2, 0.0f);
	glRotatef(this->angulo, 0.0f, 0.0f, 1.0f);

	// Desenha o objeto
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(this->posicao.getX() - 10, this->posicao.getY());
		glVertex2f(this->posicao.getX() + 10, this->posicao.getY());
		glVertex2f(this->posicao.getX(), this->posicao.getY() + 10);
	}
	glEnd();

	// Adiciona a velocidade ao projétil
	this->posicao.add(this->velocidade);

	// Verifica se o projétil passou do fim da tela, nesse caso não há motivo para redesenhá-lo
	if (this->posicao.getY() > (this->heightJanela - 125))
	{
		this->setAtivo(false);
	}
}