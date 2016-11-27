#pragma once
#include <GL/glut.h>
#include "vetor.h"

class Projetil
{
public:
	// Construtores
	Projetil();
	Projetil(GLfloat x, GLfloat y);

	// Destrutor
	~Projetil();

	// Aplica um vetor que representa uma for�a � part�cula atual
	void aplicarForca(Vetor forca);

	// Atualiza a posi��o do objeto ap�s a aplica��o da velocidade
	void atualizar();

	// Getters
	int getLargura();
	int getAltura();
	Vetor getPosicaoInicial();
	bool isAtirado();
	GLfloat getMagnitudeLancamento();
	GLfloat getMassa();

	// Setters
	void setAtirado(bool valor);
	void setAngulo(GLfloat valor);
	void setAtivo(bool valor);
	void setPosicaoInicial(GLfloat x, GLfloat y);
	void setDirecaoLancamento(char valor);
	void setVelocidadeLancamento(GLfloat valor);
	void setMagnitudeLancamento(GLfloat valor);

	// M�todos de desenho
	void desenhaProjetil();

private:
	// Propriedade que define se o proj�til est� ativo
	bool ativo = false;
	bool atirado = false;

	// �ngulo de rota��o
	GLfloat angulo;

	// Propriedades para o lan�amento da banana
	char direcaoLancamento;
	GLfloat velocidadeLancamento;
	GLfloat magnitudeLancamento;

	// Vetores
	Vetor posicaoInicial;
	Vetor velocidade = Vetor(0.0f, 1.0f);
	Vetor aceleracao;

	// Massa pra controle da gravidade
	GLfloat massa;

	// Propriedades com o tamanho m�ximo para achar a caixa de colis�o
	int largura = 10;
	int altura = 10;
};