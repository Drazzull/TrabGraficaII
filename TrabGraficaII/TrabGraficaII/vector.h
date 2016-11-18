#pragma once
#include <math.h>

#define PI 3.141592

class Vector
{
public:
    /**
     * @brief Vector - Cria um objeto do tipo Vetor com os dados pr�-definidos
     * @param x - posi��o do eixo x pr�-definida
     * @param y - posi��o do eixo y pr�-definida
     */
    Vector(GLfloat x = 0, GLfloat y = 0)
    {
        this->x = x;
        this->y = y;
    }

    /**
     * @brief Vector - Cria um novo objeto do tipo Vetor copiando os dados de um j� existente
     * @param obj - Objeto a ser copiado
     */
    Vector(const Vector& obj)
    {
        this->x = obj.x;
        this->y = obj.y;
    }

    /**
     * @brief add - Adiciona ao vetor atual os dados de um vetor existente
     * @param v - Vetor que ser� adicionado
     */
    void add(Vector v)
    {
        this->x += v.getX();
        this->y += v.getY();
    }

    /**
     * @brief sub - Subtrai do vetor atual os dados de um vetor existente
     * @param v - Vetor que ser� subtra�do
     */
    void sub(Vector v)
    {
        this->x -= v.getX();
        this->y -= v.getY();
    }

    /**
     * @brief mult - Multiplica uma constante ao vetor atual
     * @param s - Constante que ser� multiplicada
     */
    void mult(float s)
    {
        this->x *= s;
        this->y *= s;
    }

    /**
     * @brief div - Divide o vetor atual por uma constante
     * @param s - Constante pela qual o vetor ser� dividido
     */
    void div(float s)
    {
        this->x /= s;
        this->y /= s;
    }

    /**
     * @brief mag - Calcula a magnitude do vetor
     * @return Magnitude calculada
     */
    GLfloat mag()
    {
        return (GLfloat)sqrt(pow(this->x, 2) + pow(this->y, 2));
    }

    /**
     * @brief normalize - Normaliza o vetor
     */
    void normalize()
    {
        if (mag() > 0)
        {
            div(mag());
        }
    }

    /**
     * @brief getX - Retorna o valor do eixo X
     * @return Eixo X
     */
    GLfloat getX()
    {
        return this->x;
    }

    /**
     * @brief getY - Retorna o valor do eixo y
     * @return Eixo Y
     */
    GLfloat getY()
    {
        return this->y;
    }

    /**
     * @brief sub - Subtrai dois vetores (v1 - v2)
     * @param v1 - Vetor prim�rio da subtra��o
     * @param v2 - Vetor secund�rio da subtra��o
     * @return Resultado da subtra��o
     */
    static Vector sub(Vector v1, Vector v2)
    {
        return Vector(v1.getX() - v2.getX(), v1.getY() - v2.getY());
    }

    /**
     * @brief magnitudeEntreVetores - Calcula a magnitude entre dois vetores
     * @param vetorInicial - Vetor prim�rio
     * @param vetorFinal - Vetor secund�rio
     * @return Magnitude da distância entre dois vetores
     */
    static GLfloat magnitudeEntreVetores(Vector vetorInicial, Vector vetorFinal)
    {
        float x = vetorInicial.x - vetorFinal.x;
        float y = vetorInicial.y - vetorFinal.y;
        return (GLfloat)sqrt(pow(x, 2) + pow(y, 2));
    }

    /**
     * @brief anguloEntreVetores - Obt�m o angulo entre dois vetores
     * @param vetorInicial - Vetor com a posi��o inicial do p�ssaro no momento do lan�amento
     * @param vetorFinal - Vetor com a posi��o no momento em que o usu�rio soltou o mouse
     * @param hipotenusa - Hipotenusa
     * @return Angulo entre os vetores
     */
    static GLfloat anguloEntreVetores(Vector vetorInicial, Vector vetorFinal, GLfloat hipotenusa)
    {
        // Calcula o arcocoseno entre os dois vetores
        if(vetorFinal.y > vetorInicial.y)
        {
            float catetoAdjacente = vetorInicial.x - vetorFinal.x;
            GLfloat valor = catetoAdjacente / hipotenusa;
            return (GLfloat)(acos(valor) * 180 / PI);
        }

        // Calcula o arcoseno entre os dois vetores
        if(vetorFinal.y < vetorInicial.y)
        {
            float catetoOposto = vetorInicial.y - vetorFinal.y;
            GLfloat valor = catetoOposto / hipotenusa;
            return (GLfloat)(asin(valor) * 180 / PI);
        }

        return 0.0f;
    }

private:
    GLfloat x, y;
};
