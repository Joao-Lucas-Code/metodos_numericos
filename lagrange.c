/*
Alunos e RA: Eduardo Furlanetto|252210 , Gustavo Freire|251524, Gustavo Valim|250777 ,João Lucas|252192
Turma: CP004TIN1
Disciplina: Métodos Numéricos
Professor: Marco Montebello
Descrição: Programa que descobre os zeros de equações através do Método da Dicotomia ou Bissecção.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ReceberPontos(int pontos, float *valoresX, float *valoresFX);
float CalculaLagrange(int pontos, float *valoresX, float *valoresFX, float valorCalcular);

int main()
{
    int grau, pontos;
    float *valoresX = NULL;
    float *valoresFX = NULL;
    float valorCalcular, Px;
    char resp;

    printf("Digite o grau da funcao que deseja obter: ");
    scanf("%i", &grau);

    pontos = grau + 1;

    valoresX = (float *)malloc(pontos * sizeof(float));
    valoresFX = (float *)malloc(pontos * sizeof(float));

    if (valoresX == NULL || valoresFX == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    ReceberPontos(pontos, valoresX, valoresFX);

    do
    {
        printf("\nDigite o valor de X que deseja calcular (interpolar): ");
        scanf("%f", &valorCalcular);

        Px = CalculaLagrange(pontos, valoresX, valoresFX, valorCalcular);

        printf("\nO valor interpolado de f(%.5f) e: %.5f\n\n", valorCalcular, Px);

        fflush(stdin);
        printf("Deseja calcular outro valor (s/n)? ");
        scanf(" %c", &resp);

    } while (resp == 's' || resp == 'S');

    free(valoresX);
    free(valoresFX);

    system("pause");
    return 0;
}

void ReceberPontos(int pontos, float *valoresX, float *valoresFX)
{
    int cont;
    for(cont = 0; cont < pontos; cont++)
    {
        printf("Digite o valor do %i.o valor de X: ", cont + 1);
        scanf("%f", valoresX + cont);
        
        printf("Digite o valor de f(X) para X = %.2f: ", *(valoresX + cont));
        scanf("%f", valoresFX + cont);
    }
}

float CalculaLagrange(int pontos, float *valoresX, float *valoresFX, float valorCalcular)
{
    float Px = 0;
    float Li;
    int i, j;

    for(i = 0; i < pontos; i++)
    {
        Li = 1;
        
        for(j = 0; j < pontos; j++)
        {
            if(i != j)
            {
                Li = Li * ((valorCalcular - *(valoresX + j)) / (*(valoresX + i) - *(valoresX + j)));
            }
        }
        
        printf("L%i(x) = %.5f\n", i, Li);
        
        Px = Px + (Li * *(valoresFX + i));
    }

    return Px;
}