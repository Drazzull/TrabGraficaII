#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include "vetor.h"
#include "projetil.h"
#include "predio.h"
#include "oozaru.h"
#include "sol.h"
#include "explosao.h"
#include "atrator.h"

#pragma region Propriedades
// Tempo de refresh da tela
int tempoRefresh = 30;

// Predios
int numeroPredios = 10;
std::vector<Predio> predios;

// Gorilas
std::vector<Oozaru> oozarus;
int oozaruAtual = 0;

// Explosões
std::vector<Explosao> explosoes;

// Sol
Sol sol;

// Projétil
Projetil projetil;

// Atração para gravidade
Atrator atracao;

// Define os tamanhos da janela
GLfloat width = 1024.0f;
GLfloat height = 768.0f;

// Propriedades para o lançamneto
int anguloLancamento = 0;
int velocidadeLancamento = 0;
bool emLancamento = false;
bool podeJogar = false;
bool jogoTerminado = false;

// Strings das mensagens
int atributo = 0;
std::string atributoEditado;
std::string anguloString0;
std::string velocidadeString0;
std::string anguloString1;
std::string velocidadeString1;

// Controle para animação
int contadorAnimacaoSol = 0;
int contadorAnimacaoGorila0 = 0;
int contadorAnimacaoGorila1 = 0;

// Controle para inicialização
bool jogoIniciado = false;
#pragma endregion

#pragma region Inicialização
// Método pra definir os prédios
void carregarPredios()
{
	// Limpa a lista
	predios.clear();

	// Define as posições iniciais do primeiro prédio
	GLfloat yInicial = 10.0f;
	GLfloat xInicial = 2.0f;

	// Variáveis pra controle da altura e largura
	int largura = 0;
	int altura = 0;
	int percTela = (int)(height * 25) / 100;

	// Percorre o array dos prédios
	for (int i = 0; i < numeroPredios; i++)
	{
		// Definir a altura e largura randonômicamente
		altura = rand() % percTela + percTela;
		largura = rand() % 100 + 120;

		// Define o prédio
		predios.push_back(Predio(xInicial, yInicial, largura, altura));

		// Define a posição inicial do próximo prédio
		xInicial = xInicial + largura + 2;
	}
}

GLfloat ObterAlturaPredio(GLfloat x)
{
	// Desenha os prédios
	for (int i = 0; i < numeroPredios; i++)
	{
		if (predios[i].getPosicao().getX() + predios[i].getLargura() >= x)
		{
			return predios[i].getPosicao().getY() + predios[i].getAltura();
		}
	}

	return 0.0f;
}

GLfloat ObterLarguraPredio(GLfloat x)
{
	// Desenha os prédios
	for (int i = 0; i < numeroPredios; i++)
	{
		if (predios[i].getPosicao().getX() + predios[i].getLargura() >= x)
		{
			return predios[i].getPosicao().getX();
		}
	}

	return 0.0f;
}

// Método pra definir os gorilas
void carregarOozarus()
{
	// Limpa a lista
	oozarus.clear();

	// Calcula o tamanho da tela pela metade
	int percTela = (int)(35 * width / 100);

	// Calcula o X Inicial do primeiro gorila
	GLfloat xInicial = rand() % percTela;
	if (xInicial < 0)
	{
		xInicial = 0;
	}

	// Obtém a altura do prédio abaixo do gorila
	GLfloat yInicial = ObterAlturaPredio(xInicial + 52);

	// Recalcula o X para garantir que vá ficar sobre o prédio
	xInicial = ObterLarguraPredio(xInicial + 52);

	// Define as posições iniciais do primeiro gorila
	oozarus.push_back(Oozaru(xInicial, yInicial));

	// Calcula o X Inicial do segundo gorila
	percTela = (int)(65 * width / 100);
	xInicial = rand() % percTela + percTela;
	if (xInicial > 904)
	{
		xInicial = 904;
	}

	// Obtém a altura do prédio abaixo do gorila
	yInicial = ObterAlturaPredio(xInicial + 52);

	// Recalcula o X para garantir que vá ficar sobre o prédio
	xInicial = ObterLarguraPredio(xInicial + 52);

	// Define as posições iniciais do segundo gorila
	oozarus.push_back(Oozaru(xInicial, yInicial));
}

// Método para inicializar os objetos
void inicializarObjetos()
{
	// Limpa as listas
	predios.clear();
	oozarus.clear();
	explosoes.clear();

	// Zera as propriedades
	oozaruAtual = 0;
	anguloLancamento = 0;
	velocidadeLancamento = 0;
	emLancamento = false;
	atributo = 0;
	atributoEditado = "";
	anguloString0 = "";
	velocidadeString0 = "";
	anguloString1 = "";
	velocidadeString1 = "";
	contadorAnimacaoGorila0 = 0;
	contadorAnimacaoGorila1 = 0;
	contadorAnimacaoSol = 0;
	jogoTerminado = false;

	// Definir Prédios
	carregarPredios();

	// Definir posição dos gorillas
	carregarOozarus();

	// Define a posição inicial do sol
	sol = Sol(width / 2, height - 70);
	sol.setSolAcertado(false);

	// Define a posição inicial do projétil
	projetil = Projetil(
		oozarus[0].getPosicaoInicial().getX() + 50,
		oozarus[0].getPosicaoInicial().getY() + 10);
	projetil.setAngulo(0);
	projetil.setAtirado(false);
	projetil.zerarForcas();

	// Define que o jogador pode jogar
	podeJogar = true;
}

void inicializarJogo()
{
	jogoIniciado = false;
}
#pragma endregion

#pragma region Funções privadas
Vetor obterVetorLancamento()
{
	switch (oozaruAtual)
	{
	case 0:
		return Vetor(cos(anguloLancamento * PI / 180) * velocidadeLancamento,
			(sin(anguloLancamento * PI / 180) * velocidadeLancamento));

	case 1:
		return Vetor(cos(anguloLancamento * PI / 180) * velocidadeLancamento * -1,
			(sin(anguloLancamento * PI / 180) * velocidadeLancamento));

	default:
		return Vetor(0, 0);
	}
}

bool detectarColisaoPredios()
{
	for (int i = 0; i < predios.size(); i++)
	{
		if (((predios[i].getPosicao().getY() + predios[i].getAltura()) > projetil.getPosicaoInicial().getY()) &&
			(predios[i].getPosicao().getY() < (projetil.getPosicaoInicial().getY() + projetil.getAltura())) &&
			(predios[i].getPosicao().getX() < (projetil.getPosicaoInicial().getX() + projetil.getLargura())) &&
			((predios[i].getPosicao().getX() + predios[i].getLargura()) > projetil.getPosicaoInicial().getX()))
		{
			// Cria uma nova explosão
			explosoes.push_back(
				Explosao(
					projetil.getPosicaoInicial().getX(),
					projetil.getPosicaoInicial().getY()));
			return true;
		}
	}

	return false;
}

bool detectarColisaoSol()
{
	return (((sol.getPosicao().getY() + sol.getRaio() + 5) > projetil.getPosicaoInicial().getY()) &&
		((sol.getPosicao().getY() - sol.getRaio() - 5) < (projetil.getPosicaoInicial().getY() + projetil.getAltura())) &&
		((sol.getPosicao().getX() - sol.getRaio() - 5) < (projetil.getPosicaoInicial().getX() + projetil.getLargura())) &&
		((sol.getPosicao().getX() + sol.getRaio() + 5) > projetil.getPosicaoInicial().getX()));
}

bool detectarColisaoOozarus()
{
	for (int i = 0; i < oozarus.size(); i++)
	{
		if (((oozarus[i].getPosicaoInicial().getY() + oozarus[i].getAlturaMaxima()) > projetil.getPosicaoInicial().getY()) &&
			(oozarus[i].getPosicaoInicial().getY() < (projetil.getPosicaoInicial().getY() + projetil.getAltura())) &&
			(oozarus[i].getPosicaoInicial().getX() < (projetil.getPosicaoInicial().getX() + projetil.getLargura())) &&
			((oozarus[i].getPosicaoInicial().getX() + oozarus[i].getLarguraMaxima()) > projetil.getPosicaoInicial().getX()))
		{
			// Cria uma nova explosão
			explosoes.push_back(
				Explosao(
					projetil.getPosicaoInicial().getX(),
					projetil.getPosicaoInicial().getY()));
			oozarus[i].setMorto(true);
			return true;
		}
	}

	return false;
}

bool detectarColisaoLimitesHorizontaisTela()
{
	return ((projetil.getPosicaoInicial().getX() > width + 10) ||
		(projetil.getPosicaoInicial().getX() + projetil.getLargura() < -10));
}

void atirarProjetil()
{
	// Anima o gorila atual
	oozarus[oozaruAtual].setAnimarDireito(true);
	projetil.setPosicaoInicial(
		projetil.getPosicaoInicial().getX(),
		projetil.getPosicaoInicial().getY() + 30);

	// Obtém o vetor de lançamento e atira o projétil
	Vetor forcaLancamento = obterVetorLancamento();
	projetil.aplicarForca(forcaLancamento);
	projetil.setAtirado(true);
}
#pragma endregion

#pragma region Controles do Glut
void displayText(float x, float y, int r, int g, int b, const std::string mensagem, void *font)
{
	glColor3ub(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < mensagem.length(); i++)
	{
		glutBitmapCharacter(font, mensagem[i]);
	}
}

// Método de desenho da tela principal

// Método principal de desenho
void desenha()
{
	// Limpa as matrizes
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	/*if (!jogoIniciado)
	{

	}*/

	// Desenha os prédios
	for (int i = 0; i < predios.size(); i++)
	{
		predios[i].desenhaPredio();
	}

	// Desenha os gorilas
	for (int i = 0; i < oozarus.size(); i++)
	{
		oozarus[i].desenhaOozaru();
	}

	// Desenha as explosões
	for (int i = 0; i < explosoes.size(); i++)
	{
		explosoes[i].desenhaExplosao();
	}

	// Desenha o sol
	sol.desenhaSol();

	// Calcula a atração, aplica a força da mesma
	projetil.desenhaProjetil();

	// Carrega a matriz de identidade
	glLoadIdentity();

	// Desenha os textos do player 1
	displayText(
		30, height - 30, 255, 0, 0, "Player 1", GLUT_BITMAP_HELVETICA_18);
	displayText(
		30, height - 50, 255, 0, 0, "Angulo: " + anguloString0, GLUT_BITMAP_HELVETICA_18);
	displayText(
		30, height - 70, 255, 0, 0, "Velocidade: " + velocidadeString0, GLUT_BITMAP_HELVETICA_18);

	// Desenha os textos do player 2
	displayText(
		width - 160, height - 30, 255, 0, 0, "Player 2", GLUT_BITMAP_HELVETICA_18);
	displayText(
		width - 160, height - 50, 255, 0, 0, "Angulo: " + anguloString1, GLUT_BITMAP_HELVETICA_18);
	displayText(
		width - 160, height - 70, 255, 0, 0, "Velocidade: " + velocidadeString1, GLUT_BITMAP_HELVETICA_18);

	// Se o jogo foi terminado, desenha a tela de game over
	if (jogoTerminado)
	{
		// Carrega a matriz de identidade
		glLoadIdentity();

		// Desenha o texto de game over
		displayText(width / 2, (height / 2) - 30, 255, 0, 0, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
		for (int i = 0; i < oozarus.size(); i++)
		{
			if (oozarus[i].isMorto())
			{
				std::string ganhador = i == 0 ? "2" : "1";
				displayText(
					width / 2,
					height / 2,
					255, 0, 0,
					"Player " + ganhador + " ganhou",
					GLUT_BITMAP_TIMES_ROMAN_24);
				continue;
			}

			oozarus[i].setAnimarDireito(true);
			oozarus[i].setAnimarEsquerdo(true);
		}
	}

	glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y)
{
	// Não permite a digitação se estiver em lançamento
	if (emLancamento)
	{
		return;
	}

	// Tecla ESC
	if (key == 18)
	{
		//jogoIniciado = false;
		//inicializarJogo();
		inicializarObjetos();
		return;
	}

	// Tecla ESC
	if (key == 27)
	{
		exit(0);
		return;
	}

	// Verifica se o jogador pode alterar os valores
	if (!podeJogar || jogoTerminado)
	{
		return;
	}

	// Tecla Enter
	if (key == 13)
	{
		atributoEditado = "";

		// Se estava editando o ângulo, apenas passa para o próximo atributo
		if (atributo == 0)
		{
			atributo = 1;
			return;
		}

		// Altera o atributo em edição
		atributo = 0;

		// Atira o projétil
		atirarProjetil();

		// Altera para a edição do segundo gorila
		if (oozaruAtual == 0)
		{
			oozaruAtual = 1;
			anguloString1 = "";
			velocidadeString1 = "";
			return;
		}

		// Altera para a edição do primeiro gorila
		oozaruAtual = 0;
		anguloString0 = "";
		velocidadeString0 = "";
		return;
	}

	// Backspace
	if (key == 8)
	{
		atributoEditado = atributoEditado.substr(0, atributoEditado.length() - 1);
	}

	// Não permite números maiores que 4 dígitos
	if (atributoEditado.length() == 4)
	{
		return;
	}

	switch (key)
	{
	case 48:
		atributoEditado += "0";
		break;

	case 49:
		atributoEditado += "1";
		break;

	case 50:
		atributoEditado += "2";
		break;

	case 51:
		atributoEditado += "3";
		break;

	case 52:
		atributoEditado += "4";
		break;

	case 53:
		atributoEditado += "5";
		break;

	case 54:
		atributoEditado += "6";
		break;

	case 55:
		atributoEditado += "7";
		break;

	case 56:
		atributoEditado += "8";
		break;

	case 57:
		atributoEditado += "9";
		break;
	}

	switch (atributo)
	{
	case 1:
		switch (oozaruAtual)
		{
		case 0:
			velocidadeString0 = atributoEditado;
			velocidadeLancamento = velocidadeString0 != "" ? stoi(velocidadeString0) : 0;
			break;

		case 1:
		default:
			velocidadeString1 = atributoEditado;
			velocidadeLancamento = velocidadeString1 != "" ? stoi(velocidadeString1) : 0;
			break;
		}
		break;

	default:
		switch (oozaruAtual)
		{
		case 0:
			anguloString0 = atributoEditado;
			anguloLancamento = anguloString0 != "" ? stoi(anguloString0) : 0;
			break;

		case 1:
		default:
			anguloString1 = atributoEditado;
			anguloLancamento = anguloString1 != "" ? stoi(anguloString1) : 0;
			break;
		}
		break;
	}
}

void timer(int valor)
{
	// Atualiza as forças do projetil
	Vetor force = atracao.calcularAtracao(projetil);
	projetil.aplicarForca(force);
	projetil.atualizar();

	// Detecta a colisão entre o projétil e os prédios, sol e gorila
	if (detectarColisaoPredios())
	{
		// Define que o projétil não está mais sendo atirado
		projetil.setAtirado(false);
		podeJogar = true;

		// Zera as forças do projétil
		projetil.zerarForcas();

		// Define a nova posição do projétil
		projetil = Projetil(
			oozarus[oozaruAtual].getPosicaoInicial().getX() + 50,
			oozarus[oozaruAtual].getPosicaoInicial().getY() + 10);
	}

	if (detectarColisaoSol())
	{
		// Define que o sol será animado
		sol.setSolAcertado(true);

		// Define que o projétil não está mais sendo atirado
		projetil.setAtirado(false);
		podeJogar = true;

		// Zera as forças do projétil
		projetil.zerarForcas();

		// Define a nova posição do projétil
		projetil = Projetil(
			oozarus[oozaruAtual].getPosicaoInicial().getX() + 50,
			oozarus[oozaruAtual].getPosicaoInicial().getY() + 10);
	}

	if (detectarColisaoOozarus())
	{
		// Define que o projétil não está mais sendo atirado
		projetil.setAtirado(false);
		podeJogar = true;

		// Zera as forças do projétil
		projetil.zerarForcas();

		// Define a nova posição do projétil
		projetil = Projetil(
			oozarus[oozaruAtual].getPosicaoInicial().getX() + 50,
			oozarus[oozaruAtual].getPosicaoInicial().getY() + 10);

		// Terminou o jogo
		jogoTerminado = true;
	}

	if (detectarColisaoLimitesHorizontaisTela())
	{
		// Define que o projétil não está mais sendo atirado
		projetil.setAtirado(false);
		podeJogar = true;

		// Zera as forças do projétil
		projetil.zerarForcas();

		// Define a nova posição do projétil
		projetil = Projetil(
			oozarus[oozaruAtual].getPosicaoInicial().getX() + 50,
			oozarus[oozaruAtual].getPosicaoInicial().getY() + 10);
	}

	// Anima o sol
	contadorAnimacaoSol++;
	if (contadorAnimacaoSol == 40)
	{
		contadorAnimacaoSol = 0;
		sol.setSolAcertado(false);
	}

	// Anima o braço do primeiro gorila
	contadorAnimacaoGorila0++;
	if (contadorAnimacaoGorila0 == 30)
	{
		contadorAnimacaoGorila0 = 0;
		oozarus[0].setAnimarEsquerdo(false);
		oozarus[1].setAnimarDireito(false);
	}

	// Anima o braço do segundo gorila
	contadorAnimacaoGorila1++;
	if (contadorAnimacaoGorila1 == 30)
	{
		contadorAnimacaoGorila1 = 0;
		oozarus[1].setAnimarEsquerdo(false);
		oozarus[1].setAnimarDireito(false);
	}

	glutPostRedisplay();
	glutTimerFunc(tempoRefresh, timer, 0);
}
#pragma endregion

int main(int argc, char **argv)
{
	// Inicializa o seed do random
	srand(time(NULL));

	// Inicializa a biblioteca do glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize((int)width, (int)height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Gorillas - Arthur B. Bilibio, Johnatan da Rosa, Wagner Casagrande");

	//inicializarJogo();
	inicializarObjetos();

	// Define o tipo da projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

	glutDisplayFunc(desenha);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(teclado);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return(0);
}