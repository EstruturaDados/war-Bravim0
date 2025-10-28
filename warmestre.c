#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estrutura de Dados ---
typedef struct {
    char nome[30];
    char corExercito[20];
    int tropas;
} Territorio;

// --- Protótipos ---
Territorio *alocarMapa(int n);
void liberarMemoria(Territorio *mapa);
void limparBufferEntrada(void);
void inicializarMapa(Territorio *mapa, const int n);
void exibirMapa(const Territorio *mapa, const int n);
void batalhar(Territorio *mapa, int atacante, int defensor);
void mostrarMissao(int missao, const char *corJogador);
int verificarMissao(const Territorio *mapa, int n, int missao, const char *corJogador);
int escolherMissao(void);
int contarTerritorios(const Territorio *mapa, int n, const char *cor);

// --- Função Principal ---
int main() {
    const int n = 5;
    srand(time(NULL));

    Territorio *mapa = alocarMapa(n);
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    char corJogador[20] = "Vermelho";
    int missao = escolherMissao();

    inicializarMapa(mapa, n);

    printf("\n🎯 Sua missão secreta:\n");
    mostrarMissao(missao, corJogador);

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: {
                exibirMapa(mapa, n);
                int atacante, defensor;
                printf("\nEscolha o território atacante (1-%d): ", n);
                scanf("%d", &atacante);
                printf("Escolha o território defensor (1-%d): ", n);
                scanf("%d", &defensor);
                limparBufferEntrada();

                if (atacante < 1 || atacante > n || defensor < 1 || defensor > n) {
                    printf("Opção inválida!\n");
                    break;
                }
                if (atacante == defensor) {
                    printf("Não pode atacar a si mesmo!\n");
                    break;
                }
                if (strcmp(mapa[atacante - 1].corExercito, corJogador) != 0) {
                    printf("Você só pode atacar com territórios da sua cor (%s)!\n", corJogador);
                    break;
                }

                batalhar(mapa, atacante - 1, defensor - 1);

                if (verificarMissao(mapa, n, missao, corJogador)) {
                    printf("\n🏆 MISSÃO CUMPRIDA! VOCÊ VENCEU O JOGO! 🏆\n");
                    opcao = 0;
                }
                break;
            }
            case 2:
                mostrarMissao(missao, corJogador);
                verificarMissao(mapa, n, missao, corJogador);
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

// --- Funções de Setup ---
Territorio *alocarMapa(int n) {
    Territorio *mapa = calloc(n, sizeof(Territorio));
    return mapa;
}

void liberarMemoria(Territorio *mapa) {
    if (mapa != NULL)
        free(mapa);
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void inicializarMapa(Territorio *mapa, const int n) {
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "México"};
    const char *cores[] = {"Azul", "Verde", "Amarelo", "Vermelho", "Roxo"};
    for (int i = 0; i < n; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].tropas = (rand() % 5) + 2;
    }
}

// --- Funções de Interface ---
void exibirMapa(const Territorio *mapa, const int n) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %-10s | Cor: %-8s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
}

void mostrarMissao(int missao, const char *corJogador) {
    printf("---------------------------\n");
    switch (missao) {
        case 1:
            printf("Missão: Destruir o exército Verde!\n");
            break;
        case 2:
            printf("Missão: Conquistar 3 territórios!\n");
            break;
    }
    printf("Sua cor: %s\n", corJogador);
    printf("---------------------------\n");
}

// --- Lógica do Jogo ---
void batalhar(Territorio *mapa, int atacante, int defensor) {
    if (mapa[atacante].tropas <= 1) {
        printf("O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n🎯 BATALHA ENTRE %s (Atacante) e %s (Defensor)\n",
           mapa[atacante].nome, mapa[defensor].nome);
    printf("Dado Ataque: %d | Dado Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        mapa[defensor].tropas--;
        printf("✅ Ataque bem-sucedido! %s perdeu 1 tropa.\n", mapa[defensor].nome);

        if (mapa[defensor].tropas <= 0) {
            printf("🏴 %s foi conquistado por %s!\n",
                   mapa[defensor].nome, mapa[atacante].nome);
            strcpy(mapa[defensor].corExercito, mapa[atacante].corExercito);
            mapa[defensor].tropas = 1;
            mapa[atacante].tropas--;
        }
    } else {
        mapa[atacante].tropas--;
        printf("🛡️ Defesa de %s resistiu! %s perdeu 1 tropa.\n",
               mapa[defensor].nome, mapa[atacante].nome);
    }
}

// --- Funções de Missão ---
int escolherMissao(void) {
    return (rand() % 2) + 1;
}

int contarTerritorios(const Territorio *mapa, int n, const char *cor) {
    int cont = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].corExercito, cor) == 0)
            cont++;
    }
    return cont;
}

int verificarMissao(const Territorio *mapa, int n, int missao, const char *corJogador) {
    if (missao == 1) {
        int existeVerde = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0)
                existeVerde = 1;
        }
        if (!existeVerde) {
            printf("✅ Você destruiu o exército Verde!\n");
            return 1;
        }
    } else if (missao == 2) {
        int conquistados = contarTerritorios(mapa, n, corJogador);
        printf("Você controla %d territórios.\n", conquistados);
        if (conquistados >= 3) {
            printf("✅ Você conquistou 3 territórios!\n");
            return 1;
        }
    }
    return 0;
}
