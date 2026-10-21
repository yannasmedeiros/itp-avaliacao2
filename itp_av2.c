#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_alunos 10
#define num_notas 3
#define tam_nome 50

//ler um numero inteiro (numero de alunos) dentro do intervalo permitido (1 a 10)
int lerquantidade(void) {
    int quantidade;
    char linha[100], extra;

    while (1) {
        printf("Quantidade de estudantes (1 a 10): ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return 0;
        }
        if (sscanf(linha, " %d %c", &quantidade, &extra) == 1 &&
            quantidade >= 1 && quantidade <= max_alunos) {
            return quantidade;
        }
        printf("Quantidade invalida. Digite um numero de 1 a 10.\n");
    }
}

//Le nomes (nao vazios e com limite de tamanho) e tres notas validas(1 a 10) para cada (armazena nos vetores fornecidos)
int cadastrarestudantes(int quantidade, char nomes[][tam_nome],
                        float notas[][num_notas]) {
    char linha[100], extra;
    int i, j, valido;
    float nota;

    for (i = 0; i < quantidade; i++) {
        printf("\nEstudante %d\n", i + 1);
        do {
            valido = 0;
            printf("Nome: ");
            if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
            if (strchr(linha, '\n') == NULL && !feof(stdin)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }
                printf("Nome muito longo. Use ate %d caracteres.\n", tam_nome - 1);
                continue;
            }
            linha[strcspn(linha, "\n")] = '\0';
            valido = 0;
            for (j = 0; linha[j] != '\0'; j++) {
                if (!isspace((unsigned char)linha[j])) {
                    valido = 1;
                    break;
                }
            }
            if (!valido) printf("O nome nao pode estar vazio.\n");
            else if (strlen(linha) >= tam_nome) {
                printf("Nome muito longo. Use ate %d caracteres.\n", tam_nome - 1);
                valido = 0;
            }
        } while (!valido);
        strcpy(nomes[i], linha);

        for (j = 0; j < num_notas; j++) {
            while (1) {
                printf("Nota %d (0 a 10): ", j + 1);
                if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
                if (sscanf(linha, " %f %c", &nota, &extra) == 1 &&
                    nota >= 0.0f && nota <= 10.0f) {
                    notas[i][j] = nota;
                    break;
                }
                printf("Nota invalida. Digite um valor de 0 a 10.\n");
            }
        }
    }
    return 1;
}

//calcula e escreve as medias na memoria
void calcularmedias(int quantidade, float notas[][num_notas], float *medias) {
    int i, j;
    for (i = 0; i < quantidade; i++) {
        float soma = 0.0f;
        for (j = 0; j < num_notas; j++) {
            soma += notas[i][j];
        }
        medias[i] = soma / (float)num_notas;
    }
}

// montar a tabela, calcular e mostrar: a media geral e a maior/as maiores media/s
void exibirtabela(int quantidade, char nomes[][tam_nome],
                   float notas[][num_notas], const float *medias) {
    int i;
    float soma = 0.0f, maior = medias[0];

    printf("\n====================== BOLETIM DA TURMA ======================\n");
    printf("%-20s %6s %6s %6s %7s  %s\n",
           "Nome", "N1", "N2", "N3", "Media", "Situacao");
    for (i = 0; i < quantidade; i++) {
        printf("%-20.20s %6.1f %6.1f %6.1f %7.2f  %s\n",
               nomes[i], notas[i][0], notas[i][1], notas[i][2], medias[i],
               medias[i] >= 6.0f ? "Atingiu a meta" : "Abaixo da meta");
        soma += medias[i];
        if (medias[i] > maior) maior = medias[i];
    }

    printf("\nMedia geral da turma: %.2f\n", soma / (float)quantidade);
    printf("Maior media: %.2f\n", maior);
    printf("Estudante(s) com maior media:\n");
    for (i = 0; i < quantidade; i++) {
        if (medias[i] >= maior - 0.0001f && medias[i] <= maior + 0.0001f) {
            printf("- %s\n", nomes[i]);
        }
    }
}

int main(void) {
    char nomes[max_alunos][tam_nome];
    float notas[max_alunos][num_notas];
    float *medias;
    int quantidade;

    printf("SISTEMA DE BOLETIM ESCOLAR\n\n");
    quantidade = lerquantidade();
    if (quantidade == 0) return 1;

    medias = malloc((size_t)quantidade * sizeof(float));
    if (medias == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return 1;
    }

    // Inicializa o vetor 
    for (int i = 0; i < quantidade; i++) medias[i] = 0.0f;

    if (!cadastrarestudantes(quantidade, nomes, notas)) {
        printf("Entrada encerrada antes de concluir o cadastro.\n");
        free(medias);
        return 1;
    }

    calcularmedias(quantidade, notas, medias);
    exibirtabela(quantidade, nomes, notas, medias);

    free(medias);
    medias = NULL;
    return 0;
}
