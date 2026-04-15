# 📘 Guia de Apresentação - Métodos Numéricos
**Professor:** Marco Montebello
**Equipe:** João Lucas (Joli) e Grupo

Este documento contém o resumo lógico e as prováveis perguntas para a Verificação de Conhecimento dos algoritmos de Dicotomia e Interpolação de Lagrange.

---

## 🟢 PARTE 1: Método da Dicotomia (Bissecção)

### 📝 Resumo do Código (Passo a Passo)
1. **Alocação Dinâmica:** Recebemos o grau do polinômio (entre 2 e 6) e usamos `malloc` para criar o ponteiro `multi`, que armazena os coeficientes da equação sem desperdiçar memória.
2. **Entrada de Dados:** Recebemos os limites do intervalo inicial `[a, b]` e o `erro` (precisão) desejado.
3. **Análise Teórica:** Chamamos a `funcaoX` para $a$ e $b$. Se $f(a) * f(b) \ge 0$, o programa avisa que não há garantia de raiz e para por ali.
4. **Cálculo de K:** Se a raiz existir, calculamos o número máximo de iterações $K$ chamando a função `CalculaValorK`.
5. **O Laço Iterativo (A Bissecção):** Entramos num loop infinito `while (1)` onde:
   - Calculamos o ponto médio: $m = \frac{a+b}{2}$.
   - Imprimimos a linha da tabela com os sinais de $f(a)*f(m)$ e $f(m)*f(b)$.
   - Verificamos os **Critérios de Parada**: se a iteração atingiu $K$, se o tamanho do intervalo $|b-a|$ é menor que o erro, ou se $|f(m)|$ é menor que o erro, usamos o `break` para sair do laço.
   - **Atualização do Intervalo:** Se $f(a) * f(m) < 0$, o novo limite superior $b$ recebe $m$. Caso contrário, o limite inferior $a$ recebe $m$.

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
1. **Definição de Pontos e Alocação:** Recebemos o grau do polinômio e definimos a quantidade de pontos como `grau + 1`. Usamos `malloc` para alocar dinamicamente dois vetores (ponteiros): `valoresX` e `valoresFX`.
2. **Entrada de Dados:** A função `ReceberPontos` é chamada (passando os ponteiros por referência) para ler cada par de $x$ e $f(x)$ tabelado que o usuário digitar.
3. **Loop de Interpolação:** Entramos em um `do...while` que permite ao usuário calcular quantos valores de $X$ ele quiser sem fechar o programa.
4. **Cálculo de Lagrange:** A mágica acontece na função `CalculaLagrange`, que possui dois laços `for` aninhados:
   - O laço externo (índice $i$) percorre os pontos para somar o resultado final do polinômio $P(x)$.
   - O laço interno (índice $j$) calcula os produtórios para encontrar o $L_i(x)$, garantindo que $i \neq j$ para evitar divisão por zero.
   - O valor de cada $L_i$ calculado é impresso na tela a cada passagem do laço externo.
5. **Liberação de Memória:** Ao final (quando o usuário digita 'n'), usamos `free` para liberar a memória de `valoresX` e `valoresFX`.

### ❓ Prováveis Perguntas do Professor & Respostas

**Q1: Como funciona a Interpolação pela Forma de Lagrange?**
> **Resposta:** A interpolação de Lagrange é usada para descobrir um valor $f(x)$ desconhecido a partir de um conjunto de pontos tabelados. Ela faz isso criando um polinômio $P(x)$ que é a soma de vários termos $L_i(x) * f(x_i)$. Cada $L_i(x)$ é calculado através de um produtório das diferenças entre o $X$ que queremos descobrir e os $X$ da tabela.

**Q2: Onde vocês calculam o $L_i(x)$ no código?**
> **Resposta:** Na função `CalculaLagrange`. Temos um laço `for` interno (com o índice `j`) que multiplica `Li = Li * ((valorCalcular - x_j) / (x_i - x_j))`. Ele tem um `if (i != j)` para garantir que não vamos subtrair um $X$ dele mesmo no denominador, o que daria divisão por zero.

**Q3: Como vocês fizeram para o usuário conseguir calcular vários valores sem fechar o programa?**
> **Resposta:** Implementamos a lógica principal dentro de um laço `do...while` na função `main`. Ao final do cálculo e da exibição do resultado, perguntamos se ele "Deseja calcular outro valor (s/n)?". Enquanto a resposta for 's', o laço reinicia pedindo um novo $X$ para interpolar usando a mesma tabela alocada na memória.

**Q4: O PDF pede que o programa não use variáveis globais e use ponteiros. Como vocês trataram isso?**
> **Resposta:** Todos os arrays de coeficientes e pontos (`valoresX`, `valoresFX`) foram declarados como ponteiros nulos dentro da `main` e receberam o tamanho exato da memória através da função `malloc()`. Na hora de fazer os cálculos, nós passamos esses ponteiros como parâmetros para as funções `ReceberPontos` e `CalculaLagrange`, operando a memória de forma segura e local.