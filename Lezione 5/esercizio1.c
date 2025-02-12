#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 4
#define COLS 4

void fillMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void printMatrix(int matrix[ROWS][COLS]) {
    printf("Matrice generata:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int searchInMatrix(int matrix[ROWS][COLS], int number) {
    int found = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == number) {
                printf("Il numero %d si trova nella posizione [%d][%d].\n", number, i, j);
                found = 1;
            }
        }
    }
    return found;
}

int main() {
    int matrix[ROWS][COLS];
    int searchNumber;

    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));

    // Riempimento e stampa della matrice
    fillMatrix(matrix);
    printMatrix(matrix);

    // Chiedere all'utente il numero da cercare
    printf("\nInserisci un numero da cercare nella matrice (0-9): ");
    scanf("%d", &searchNumber);

    // Ricerca del numero nella matrice
    if (!searchInMatrix(matrix, searchNumber)) {
        printf("Il numero %d non si trova nella matrice.\n", searchNumber);
    }

    return 0;
}
