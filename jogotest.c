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


