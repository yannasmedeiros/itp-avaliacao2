# Projeto: Boletim Escolar da Turma (ITP - Avaliação 2)

## Identificação
* **Nome do Estudante:** [Seu Nome Completo]
* **Opção de Projeto Escolhida:** Boletim de uma pequena turma (Problema 1)

## Descrição
Este programa foi desenvolvido na linguagem C para automatizar o registro de notas e a geração do boletim final de uma turma pequena.

### Problema Resolvido
O sistema resolve o problema de consolidação das notas de uma turma, permitindo que uma pessoa insira os dados dos estudantes e obtenha um resumo detalhado com médias individuais, situação de desempenho de cada aluno, média geral da turma e destaque dos estudantes com maior nota.

### Funcionalidades Implementadas
* **Validação da Quantidade de Alunos:** Solicita a quantidade de estudantes no limite de 1 a 10, rejeitando valores inválidos ou entradas com letras.
* **Validação de Nomes:** Coleta os nomes dos estudantes evitando entradas vazias ou que ultrapassem 50 caracteres.
* **Leitura e Validação de Notas:** Lê três notas por estudante, armazenando-as em uma matriz do tipo `float` (`notas[10][3]`). O sistema rejeita notas fora do intervalo [0.0, 10.0].
* **Cálculo de Médias com Ponteiros:** Calcula as médias através de uma função que escreve o resultado diretamente em um vetor alocado dinamicamente.
* **Alocação Dinâmica de Memória:** Aloca a área de memória do vetor de médias na Heap via `malloc` com base na quantidade exata de alunos, verificando o ponteiro e liberando com `free` ao término da execução.
* **Exibição do Boletim Formatado:** Imprime a tabela no terminal listando Nome, Notas, Média e Situação ("Atingiu a meta" para média maior ou igual a 6.0 e "Abaixo da meta" para as demais).
* **Estatísticas da Turma:** Calcula e exibe a média geral da turma e os nomes dos estudantes com a maior média (tratando empates).

## Compilação e Execução

### Pré-requisitos
* Compilador **GCC** instalado.

### Comando para Compilação
No terminal, navegue até a pasta onde o arquivo `itp_av2.c` está salvo e execute:

`bash
gcc -std=c11 -Wall -Wextra itp_av2.c -o programa`

### Comando para Execução
* No Linux / macOS:

`Bash
./programa`

* No Windows (Prompt de Comando ou PowerShell):

`DOS
programa.exe`

## Testes do Sistema

### Teste 1: Funcionamento Normal (Entrada Válida)

* **Entradas:**
  * Quantidade de estudantes: `2`
  * Estudante 1: `Maria`
    * Nota 1: `5.0`
    * Nota 2: `6.0`
    * Nota 3: `7.0`
  * Estudante 2: `João`
    * Nota 1: `4.0`
    * Nota 2: `5.0`
    * Nota 3: `3.0`

* **Resultados Esperados:**
  * Maria: Média `6.00` | Situação: `Atingiu a meta`
  * João: Média `4.00` | Situação: `Abaixo da meta`
  * Média geral da turma: `5.00`
  * Maior média: `6.00` (Estudante com maior média: Maria)

---

### Teste 2: Entrada Inválida / Situação de Limite

* **Entradas:**
  * Quantidade de estudantes: `15` (Inválida: o sistema rejeita e solicita novamente)
  * Quantidade corrigida: `1`
  * Estudante 1: `Ana`
  * Nota 1: `11.0` (Inválida por exceder 10.0: o sistema rejeita e solicita novamente)
  * Notas válidas inseridas: `8.0`, `9.0`, `10.0`

* **Resultados Esperados:**
  * Rejeição e nova cobrança imediata para cada dado fora das regras do sistema.
  * Ana: Média `9.00` | Situação: `Atingiu a meta`
  * Média geral da turma: `9.00`
  * Maior média: `9.00` (Estudante com maior média: Ana)

## Vídeo de Apresentação
Link no YouTube: (https://youtu.be/ZrdNXFroK8M)

### Referências
Documentação C: Biblioteca Padrão C (stdio.h, stdlib.h, string.h, ctype.h).
Material Didático: Aulas sobre Alocação Dinâmica de Memória, Matrizes e Ponteiros na linguagem C.
