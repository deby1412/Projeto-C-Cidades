# Cálculo de Vizinhança entre Cidades

Este é um programa em C que analisa a vizinhança entre cidades em uma estrada, determinando a menor vizinhança e identificando a cidade associada a essa condição.

---

## Funcionalidades

- Lê um arquivo de texto com informações sobre uma estrada e as cidades localizadas nela.
- Calcula a menor vizinhança entre cidades ao longo da estrada.
- Determina a cidade associada à menor vizinhança.
- Ordena as cidades com base em suas posições ao longo da estrada.

---

## Estrutura do Código

1. **`typedef struct Cidade`** (definida em `cidades.h`):
   - Representa as informações de uma cidade, incluindo nome e posição na estrada.

2. **Função `getEstrada`**:
   - Lê os dados do arquivo de entrada e cria uma estrutura representando a estrada e suas cidades.

3. **Função `calcularMenorVizinhanca`**:
   - Calcula o menor intervalo entre as cidades, considerando suas posições ao longo da estrada.

4. **Função `cidadeMenorVizinhanca`**:
   - Identifica a cidade com a menor vizinhança.

5. **Função `compare`**:
   - Ordena as cidades pela posição para facilitar os cálculos.

6. **Exemplo de `main`**:
   - Realiza a leitura dos dados, chama as funções de cálculo e exibe os resultados no console.

---

## Arquivo de Entrada

O arquivo de entrada deve seguir o seguinte formato:
1. Primeira linha: comprimento total da estrada (T).
2. Segunda linha: número de cidades (N).
3. Linhas subsequentes: posição e nome de cada cidade.

---

## Como Usar

1. Certifique-se de ter um arquivo de entrada (por exemplo, `teste01.txt`) no mesmo diretório do programa.
2. Compile o código:
   ```bash
   gcc -o vizinhanca vizinhanca.c -lm

---

## O programa exibirá
O menor intervalo entre cidades.
A cidade associada à menor vizinhança.

---

## Requisitos
GCC (Compilador de C).
Arquivo de entrada no formato especificado.

---

## Estrutura do Projeto
vizinhanca.c: Código-fonte principal do programa.
cidades.h: Header file com definições de estruturas e funções.
teste01.txt: Arquivo de entrada contendo as informações da estrada e das cidades.

---

## Autor
[Débora Rezende Valeriano]

