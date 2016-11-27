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

	// Aplica um vetor que representa uma força à partícula atual
	void aplicarForca(Vetor forca);

	// Atualiza a posição do objeto após a aplicação da velocidade
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

	// Métodos de desenho
	void desenhaProjetil();

private:
	// Propriedade que define se o projétil está ativo
	bool ativo = false;
	bool atirado = false;

	// Ângulo de rotação
	GLfloat angulo;

	// Propriedades para o lançamento da banana
	char direcaoLancamento;
	GLfloat velocidadeLancamento;
	GLfloat magnitudeLancamento;

	// Vetores
	Vetor posicaoInicial;
	Vetor velocidade = Vetor(0.0f, 1.0f);
	Vetor aceleracao;

	// Massa pra controle da gravidade
	GLfloat massa;

	// Propriedades com o tamanho máximo para achar a caixa de colisão
	int largura = 10;
	int altura = 10;
};