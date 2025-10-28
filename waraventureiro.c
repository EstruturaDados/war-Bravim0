#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[50];
    char corExercito[20];
    int tropas;
} Territorio;

// Funções auxiliares
void cadastrarTerritorios(Territorio *mapa, int n);
void exibirMapa(Territorio *mapa, int n);
void batalhar(Territorio *mapa, int atacante, int defensor);

int main() {
    int n = 5;
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    srand(time(NULL)); // inicializa gerador de números aleatórios

    printf("=== CADASTRO DE TERRITÓRIOS ===\n");
    cadastrarTerritorios(mapa, n);

    int opcao;
    do {
        printf("\n=== MAPA ATUAL ===\n");
        exibirMapa(mapa, n);

        int atacante, defensor;

        printf("\nEscolha o território atacante (1 a %d): ", n);
        scanf("%d", &atacante);
        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &defensor);

        if (atacante < 1 || atacante > n || defensor < 1 || defensor > n) {
            printf("Índice inválido! Tente novamente.\n");
            continue;
        }
        if (atacante == defensor) {
            printf("Um território não pode atacar a si mesmo!\n");
            continue;
        }

        batalhar(mapa, atacante - 1, defensor - 1);

        printf("\nAperte ENTER para continuar ou 0 para sair ");
        getchar();

    } while (opcao != 0);

    free(mapa);
    printf("\nJogo encerrado. Memória liberada!\n");
    return 0;
}

/* ---------- FUNÇÕES ---------- */

void cadastrarTerritorios(Territorio *mapa, int n) {
    getchar(); // limpa o \n deixado no buffer
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o buffer
    }
}

void exibirMapa(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d] %-15s | Exército: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
}

void batalhar(Territorio *mapa, int atacante, int defensor) {
    if (mapa[atacante].tropas <= 1) {
        printf("O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtaque = (rand() % 6) + 1;   // 1 a 6
    int dadoDefesa = (rand() % 6) + 1;

    printf("\nBatalha: %s (Atacante) vs %s (Defensor)\n",
           mapa[atacante].nome, mapa[defensor].nome);
    printf("Dado de Ataque: %d | Dado de Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        // atacante vence (empate favorece atacante)
        mapa[defensor].tropas--;
        printf("✅ %s venceu a rodada!\n", mapa[atacante].nome);

        if (mapa[defensor].tropas <= 0) {
            printf("🏴 %s foi conquistado por %s!\n",
                   mapa[defensor].nome, mapa[atacante].nome);
            strcpy(mapa[defensor].corExercito, mapa[atacante].corExercito);
            mapa[defensor].tropas = 1;
            mapa[atacante].tropas--;
        }
    } else {
        printf("🛡️ Defesa de %s resistiu!\n", mapa[defensor].nome);
        mapa[atacante].tropas--; // atacante perde tropa
    }
}