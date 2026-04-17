/*
Alunos e RA: Eduardo Furlanetto|252210 , Gustavo Freire|251524, Gustavo Valim|250777 ,João Lucas|252192
Turma: CP004TIN1
Disciplina: Métodos Numéricos
Professor: Marco Montebello
Descrição: Interpolação Polinomial pela Forma de Lagrange.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float CalculaValorK(float a, float b, float erro);
float funcaoX(float ponto, int grau, float *multi);
void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);

int main()
{
    int i, grau;
    float *multi = NULL;
    float a, b, erro, m, fA, fB, fM;
    int I = 1, K;

    do {
        printf("Informe o grau da funcao (2 a 6): ");
        scanf("%i", &grau);
        if (grau < 2 || grau > 6) {
            printf("Grau invalido! Tente novamente.\n");
        }
    } while (grau < 2 || grau > 6);

    multi = (float *)malloc((grau + 1) * sizeof(float));
    if (multi == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    for(i = grau; i >= 0; i--)
    {
        printf("Informe o fator multiplicador de x^%i(%c): ", i, 65+(grau-i));
        scanf("%f", multi + i); 
    }

    printf("\nA funcao recebida foi: f(x) = ");
    for(i = grau; i >= 0; i--)
    {
        if(i == 0)
            printf("%.2f\n", *(multi + i));
        else
            printf("%.2fx^%i + ", *(multi + i), i);
    }

    printf("\n");
    system("pause");
    printf("\n");

    printf("Informe o inicio do intervalo [A]: ");
    scanf("%f", &a);
    
    do {
        printf("Informe o fim do intervalo [B] (maior que A): ");
        scanf("%f", &b);
        if (b <= a) {
            printf("O valor de B deve ser maior que A!\n");
        }
    } while(b <= a);

    printf("Informe a precisao (erro eps): ");
    scanf("%f", &erro);

    fA = funcaoX(a, grau, multi);
    fB = funcaoX(b, grau, multi);

    if (fA * fB >= 0) {
        printf("\nO intervalo fornecido nao garante a existencia de uma raiz (f(a) * f(b) >= 0).\nA dicotomia nao e valida para este intervalo.\n\n");
    } else {
        K = (int)CalculaValorK(a, b, erro);
        printf("\nNumero de iteracoes estimadas (K): %i\n\n", K);

        ImprimirCabecalhoTabela();

        while (1)
        {
            m = (a + b) / 2.0;
            fM = funcaoX(m, grau, multi);
            fA = funcaoX(a, grau, multi);
            fB = funcaoX(b, grau, multi);

            char sinal_fAfM = (fA * fM < 0) ? '-' : '+';
            char sinal_fMfB = (fM * fB < 0) ? '-' : '+';

            ImprimirTabela(I, a, b, m, fA, fB, fM, sinal_fAfM, sinal_fMfB);

            if (I >= K || fabs(b - a) <= erro || fabs(fM) <= erro) {
                break;
            }

            if (fA * fM < 0) {
                b = m;
            } else {
                a = m;
            }
            
            I++;
        }
        
        printf("\nRaiz aproximada encontrada: %f\n\n", m);
    }

    free(multi);

    system("pause");
    return 0;
}

float CalculaValorK(float a, float b, float erro)
{
    float fValorK;
    fValorK = (log10(b-a) - log10(erro))/(log10(2));
    return ceil(fValorK);
}

float funcaoX(float ponto, int grau, float *multi)
{
    int i;
    float resultado = 0;

    for(i=0; i<=grau; i++)
    {
        resultado = resultado + (*(multi + i)) * pow(ponto, i);
    }

    return resultado;
}

void ImprimirCabecalhoTabela()
{
    printf("I |\ta\t|\tb\t|\tm\t|\tf(a)\t|\tf(b)\t|\tf(m)\t|fa*fm\t|fm*fb\t|\n");
    printf("--+-------------+---------------+---------------+---------------+---------------+---------------+-------+-------+\n");
}

void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB)
{
    printf("%i |\t%.5f\t|\t%.5f\t|\t%.5f\t|\t%.5f\t|\t%.5f\t|\t%.5f\t|   %c\t|   %c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
}