# 📘 Guia de Apresentação - Métodos Numéricos
**Professor:** Marco Montebello
**Equipe:** Eduardo Spoletto, Gustavo Valim, Gustavo Freire, João Lucas

Este documento contém o resumo lógico apontando para as linhas de código e as prováveis perguntas para a Verificação de Conhecimento dos algoritmos de Dicotomia e Interpolação de Lagrange.

---

## 🟢 PARTE 1: Método da Dicotomia (Bissecção)

### 📝 Resumo do Código (Passo a Passo)

1. **Alocação Dinâmica:** Recebemos o grau do polinômio e usamos `malloc` para criar o ponteiro `multi`.
   * **No código:** `multi = (float *)malloc((grau + 1) * sizeof(float));`
2. **Entrada de Dados:** Recebemos os limites do intervalo inicial e a precisão (erro).
   * **No código:** `scanf("%f", &a);`, `scanf("%f", &b);` e `scanf("%f", &erro);`
3. **Análise Teórica:** Testamos se as extremidades do intervalo têm sinais opostos. Se a multiplicação for positiva ou zero, o cálculo é abortado.
   * **No código:** `if (fA * fB >= 0) { printf("...A dicotomia nao e valida..."); }`
4. **Cálculo de K:** Se a raiz existir, calculamos o número máximo de iterações.
   * **No código:** `K = (int)CalculaValorK(a, b, erro);`
5. **O Laço Iterativo (A Bissecção):** Entramos no loop de cálculo `while (1)`:
   * **Ponto Médio:** Calculado no início do laço: `m = (a + b) / 2.0;`
   * **Critérios de Parada:** O loop quebra (`break`) se atingir $K$, se o intervalo for menor que o erro, ou se $f(m)$ for menor que o erro.
     * **No código:** `if (I >= K || fabs(b - a) <= erro || fabs(fM) <= erro) { break; }`
   * **Atualização do Intervalo:** Verifica de qual lado ocorreu a troca de sinal para substituir $a$ ou $b$ pelo $m$.
     * **No código:** `if (fA * fM < 0) { b = m; } else { a = m; }`

### ❓ Prováveis Perguntas do Professor & Respostas

**Q1: Como funciona o Método da Dicotomia na teoria?**
> **Resposta:** O método encontra raízes em um intervalo fechado cortando-o pela metade repetidas vezes. Primeiro, garantimos que há uma troca de sinal ($f(a)*f(b) < 0$). Depois, calculamos o ponto médio $m$. Analisamos em qual das metades a troca de sinal se manteve ($f(a)*f(m) < 0$, por exemplo) e descartamos a outra metade, repetindo o processo até o intervalo ficar menor que o erro exigido.

**Q2: Onde vocês fizeram a Análise Teórica no código?**
> **Resposta:** Está na função `main`, na linha do `if (fA * fB >= 0)`. Calculamos a função nas extremidades antes de começar a tabela. Se a multiplicação não for negativa, avisamos o usuário que o intervalo não é válido e o cálculo nem começa.

**Q3: Onde ocorre a atualização do intervalo no código?**
> **Resposta:** No final do laço `while`. Temos um `if (fA * fM < 0) { b = m; } else { a = m; }`. Isso reduz nosso intervalo pela metade a cada iteração, guardando sempre o lado que contém a raiz.

**Q4: Quais foram os critérios de parada adotados e onde estão?**
> **Resposta:** Estão no meio do nosso `while`, no `if (I >= K || fabs(b - a) <= erro || fabs(fM) <= erro)`. O laço para se atingirmos o número calculado de iterações, se a diferença entre $b$ e $a$ for menor que o erro, ou se encontrarmos uma imagem de $m$ suficientemente perto de zero.

---

<br>

---

## 🔵 PARTE 2: Interpolação Polinomial de Lagrange

### 📝 Resumo do Código (Passo a Passo)

1. **Definição de Pontos e Alocação:** Com base no grau, definimos a quantidade de pontos (`grau + 1`) e alocamos memória para as "colunas" X e Y da tabela.
   * **No código:** `valoresX = (float *)malloc(pontos * sizeof(float));` e `valoresFX = (float *)malloc(pontos * sizeof(float));`
2. **Entrada de Dados:** Chamamos a função passando os ponteiros por referência para o usuário preencher a tabela.
   * **No código:** `ReceberPontos(pontos, valoresX, valoresFX);`
3. **Loop de Múltiplas Interpolações:** Mantemos o programa rodando para o usuário testar quantos valores de $X$ quiser.
   * **No código:** `do { ... } while (resp == 's' || resp == 'S');`
4. **Cálculo de Lagrange:** Dentro da função `CalculaLagrange`, temos os dois laços de repetição:
   * **Produtório ($L_i$):** O laço `for` interno ignora quando $i = j$ para não dar divisão por zero e multiplica os termos.
     * **No código:** `if(i != j) { Li = Li * ((valorCalcular - *(valoresX + j)) / (*(valoresX + i) - *(valoresX + j))); }`
   * **Somatório Final ($Px$):** O laço `for` externo pega o $L_i$ calculado e multiplica pelo $f(X_i)$ correspondente, somando ao total.
     * **No código:** `Px = Px + (Li * *(valoresFX + i));`
5. **Liberação de Memória:** Liberamos a memória alocada no final do programa.
   * **No código:** `free(valoresX); free(valoresFX);`

### ❓ Prováveis Perguntas do Professor & Respostas

**Q1: Como funciona a Interpolação pela Forma de Lagrange?**
> **Resposta:** A interpolação de Lagrange é usada para descobrir um valor $f(x)$ desconhecido a partir de um conjunto de pontos tabelados. Ela faz isso criando um polinômio $P(x)$ que é a soma de vários termos $L_i(x) * f(x_i)$. Cada $L_i(x)$ é calculado através de um produtório das diferenças entre o $X$ que queremos descobrir e os $X$ da tabela.

**Q2: Onde vocês calculam o $L_i(x)$ no código?**
> **Resposta:** Na função `CalculaLagrange`. Temos um laço `for` interno (com o índice `j`) que multiplica `Li = Li * ((valorCalcular - x_j) / (x_i - x_j))`. Ele tem um `if (i != j)` para garantir que não vamos subtrair um $X$ dele mesmo no denominador, o que daria divisão por zero.

**Q3: Como vocês fizeram para o usuário conseguir calcular vários valores sem fechar o programa?**
> **Resposta:** Implementamos a lógica principal dentro de um laço `do...while` na função `main`. Ao final do cálculo e da exibição do resultado, perguntamos se ele "Deseja calcular outro valor (s/n)?". Enquanto a resposta for 's', o laço reinicia pedindo um novo $X$ para interpolar usando a mesma tabela alocada na memória.

**Q4: O PDF pede que o programa não use variáveis globais e use ponteiros. Como vocês trataram isso?**
> **Resposta:** Todos os arrays de coeficientes e pontos (`valoresX`, `valoresFX`) foram declarados como ponteiros nulos dentro da `main` e receberam o tamanho exato da memória através da função `malloc()`. Na hora de fazer os cálculos, nós passamos esses ponteiros como parâmetros para as funções `ReceberPontos` e `CalculaLagrange`, operando a memória de forma segura e local.