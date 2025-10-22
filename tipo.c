#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char corExercito[20];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[5]; // Vetor estático de 5 territórios

    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

    // Leitura dos dados de cada território
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o '\n'

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o '\n' deixado pelo scanf

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("=== ESTADO ATUAL DO MAPA ===\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exército: %s\n", mapa[i].corExercito);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
