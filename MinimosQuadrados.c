#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Alunos e RA: Eduardo Furlanetto|252210, Gustavo Freire|251524, Gustavo Valim|250777, João Lucas|252192
Turma: CP004TIN1
Disciplina: Métodos Numéricos
Professor: Marco Montebello
Descrição: Ajuste de Curvas utilizando o Método dos Mínimos Quadrados (MMQ) e resolução do sistema linear por Eliminação de Gauss.
*/

// Estrutura para armazenar os pares ordenados (xi, f(xi))
typedef struct {
    float x;
    float y;
} Ponto;

// Protótipos das funções
void EntradaDados(int *m, int *n, Ponto **pontos);
void MontarSistemaMMQ(int m, int n, Ponto *pontos, float ***matriz);
void ImprimirMatriz(int ordem, float **matriz, const char *mensagem);
void EliminacaoGauss(int ordem, float **matriz);
void SubstituicaoRetroativa(int ordem, float **matriz, float **coeficientes);
void ExibirPolinomio(int n, float *coeficientes);
void LiberarMatriz(int ordem, float **matriz);

int main() {
    int m, n;
    Ponto *pontos = NULL;
    float **matriz = NULL;
    float *coeficientes = NULL;

    // 1. Entrada dos Dados
    EntradaDados(&m, &n, &pontos);

    // 2. Implementacao do Metodo dos Minimos Quadrados (MMQ)
    MontarSistemaMMQ(m, n, pontos, &matriz);
    
    // Ordem do sistema linear é n + 1
    int ordemSistema = n + 1;
    
    printf("\n--- Sistema Linear Original (Matriz Aumentada) ---\n");
    ImprimirMatriz(ordemSistema, matriz, "Matriz Inicial [A|b]");

    // 3. Resolucao do Sistema Linear (Eliminacao de Gauss)
    EliminacaoGauss(ordemSistema, matriz);

    // Substituicao retroativa para encontrar as incognitas
    SubstituicaoRetroativa(ordemSistema, matriz, &coeficientes);

    // 4. Resultado Final
    ExibirPolinomio(n, coeficientes);

    // Liberacao da memoria alocada dinamicamente
    free(pontos);
    free(coeficientes);
    LiberarMatriz(ordemSistema, matriz);

    printf("\n");
    system("pause");
    return 0;
}

// Funcao para receber a quantidade de pontos, o grau e alocar a struct de pontos
void EntradaDados(int *m, int *n, Ponto **pontos) {
    printf("Informe a quantidade de pontos experimentais (m): ");
    scanf("%i", m);

    do {
        printf("Informe o grau do polinomio desejado (1 a 5): ");
        scanf("%i", n);
        if (*n < 1 || *n > 5) {
            printf("Grau invalido! O grau deve ser entre 1 e 5.\n");
        }
    } while (*n < 1 || *n > 5);

    // Alocacao dinamica da estrutura de pontos
    *pontos = (Ponto *)malloc((*m) * sizeof(Ponto));
    if (*pontos == NULL) {
        printf("Erro de alocacao de memoria para os pontos.\n");
        exit(1);
    }

    printf("\n--- Digite os pares ordenados (x, y) ---\n");
    for (int i = 0; i < *m; i++) {
        printf("Ponto %i - Valor de x: ", i + 1);
        scanf("%f", &((*pontos)[i].x));
        printf("Ponto %i - Valor de f(x): ", i + 1);
        scanf("%f", &((*pontos)[i].y));
    }
}

// Funcao que monta a matriz aumentada do sistema linear associado ao MMQ
void MontarSistemaMMQ(int m, int n, Ponto *pontos, float ***matriz) {
    int ordem = n + 1;

    // Alocacao dinamica da matriz (linhas)
    *matriz = (float **)malloc(ordem * sizeof(float *));
    if (*matriz == NULL) {
        printf("Erro de alocacao de memoria para as linhas da matriz.\n");
        exit(1);
    }

    // Alocacao dinamica da matriz (colunas -> ordem + 1 para a matriz aumentada)
    for (int i = 0; i < ordem; i++) {
        (*matriz)[i] = (float *)malloc((ordem + 1) * sizeof(float));
        if ((*matriz)[i] == NULL) {
            printf("Erro de alocacao de memoria para as colunas da matriz.\n");
            exit(1);
        }
    }

    // Preenchimento da matriz A e vetor b
    for (int i = 0; i < ordem; i++) {
        // Montando a matriz A (somatorio de x^(i+j))
        for (int j = 0; j < ordem; j++) {
            float somaA = 0;
            for (int k = 0; k < m; k++) {
                somaA += pow(pontos[k].x, i + j);
            }
            (*matriz)[i][j] = somaA;
        }

        // Montando o vetor b (somatorio de y * x^i)
        float somaB = 0;
        for (int k = 0; k < m; k++) {
            somaB += pontos[k].y * pow(pontos[k].x, i);
        }
        (*matriz)[i][ordem] = somaB;
    }
}

// Funcao auxiliar para exibir a matriz na tela
void ImprimirMatriz(int ordem, float **matriz, const char *mensagem) {
    printf("%s:\n", mensagem);
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j <= ordem; j++) {
            if (j == ordem) {
                printf("| %10.4f ", matriz[i][j]);
            } else {
                printf("%10.4f ", matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Funcao que resolve a Eliminacao Progressiva de Gauss
void EliminacaoGauss(int ordem, float **matriz) {
    printf("--- Iniciando Eliminacao de Gauss ---\n\n");
    
    // Para cada coluna k
    for (int k = 0; k < ordem - 1; k++) {
        
        // Verifica se o pivo eh zero (tratamendo basico de pivo)
        if (matriz[k][k] == 0) {
            // Procura linha abaixo para trocar
            for (int i = k + 1; i < ordem; i++) {
                if (matriz[i][k] != 0) {
                    float *temp = matriz[k];
                    matriz[k] = matriz[i];
                    matriz[i] = temp;
                    break;
                }
            }
        }

        // Para cada linha abaixo do pivo
        for (int i = k + 1; i < ordem; i++) {
            // Calcula o multiplicador
            float m_ik = matriz[i][k] / matriz[k][k];
            
            // Atualiza a linha inteira, incluindo a coluna do termo independente
            for (int j = k; j <= ordem; j++) {
                matriz[i][j] = matriz[i][j] - (m_ik * matriz[k][j]);
            }
        }
        
        // Exibe a matriz apos o passo k
        char msg[50];
        sprintf(msg, "Matriz apos o passo k = %i", k);
        ImprimirMatriz(ordem, matriz, msg);
    }
}

// Funcao para encontrar as incognitas na matriz triangular superior
void SubstituicaoRetroativa(int ordem, float **matriz, float **coeficientes) {
    *coeficientes = (float *)malloc(ordem * sizeof(float));
    if (*coeficientes == NULL) {
        printf("Erro de alocacao de memoria para os coeficientes.\n");
        exit(1);
    }

    // Resolvendo de tras para frente
    for (int i = ordem - 1; i >= 0; i--) {
        float soma = 0;
        for (int j = i + 1; j < ordem; j++) {
            soma += matriz[i][j] * (*coeficientes)[j];
        }
        (*coeficientes)[i] = (matriz[i][ordem] - soma) / matriz[i][i];
    }
}

// Funcao para exibir explicitamente o polinomio ajustado
void ExibirPolinomio(int n, float *coeficientes) {
    printf("--- Resultado Final ---\n");
    printf("Coeficientes encontrados:\n");
    for (int i = 0; i <= n; i++) {
        printf("a%i = %.6f\n", i, coeficientes[i]);
    }

    printf("\nPolinomio ajustado: p(x) = ");
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("%.4f", coeficientes[i]);
        } else {
            // Imprime o sinal dependendo se o coeficiente eh positivo ou negativo
            if (coeficientes[i] >= 0) {
                printf(" + %.4fx^%i", coeficientes[i], i);
            } else {
                printf(" - %.4fx^%i", fabs(coeficientes[i]), i);
            }
        }
    }
    printf("\n\n");
}

// Funcao para liberar a memoria dinamica da matriz bidimensional
void LiberarMatriz(int ordem, float **matriz) {
    for (int i = 0; i < ordem; i++) {
        free(matriz[i]);
    }
    free(matriz);
}