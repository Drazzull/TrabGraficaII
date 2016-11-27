#include "atrator.h"

Atrator::Atrator()
{
	this->pos = Vetor(0, 0);
	this->massa = 20;
	this->G = 10;
}

Atrator::~Atrator()
{
}

float Atrator::constrain(float value, float min, float max)
{
	return (value > max) ? max : min;
}

void Atrator::setGravidade(GLfloat valor)
{
	this->G = valor;
}

Vetor Atrator::calcularAtracao(Projetil m)
{
	if (!m.isAtirado())
	{
		return Vetor(0, 0);
	}

	// Cálculo da direção da força
	Vetor centroGravidade = Vetor(m.getPosicaoInicial().getX(), this->pos.getY());
	Vetor forca = Vetor::sub(centroGravidade, m.getPosicaoInicial());

	// Distância entre objetos
	float distance = forca.mag();

	// Limitar a distância para eliminar resultados extremos
	// para objetos muito próximos ou muito distantes
	distance = constrain(distance, 5, 25);

	// Normalizar vetor
	forca.normalize();

	// Calcular a magnitude da força gravitacional
	float strength = (this->G * this->massa * m.getMassa()) / pow(distance, 2);

	// Pegar o vetor força --> magnitude * direction
	forca.mult(strength);

	return forca;
}