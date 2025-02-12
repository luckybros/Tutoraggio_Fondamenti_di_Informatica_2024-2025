// Un array contiene una lista di 0, ma tra di loro c'è un intruso. 
// Si scriva una funzione che permetta di ottenere la posizione dell'
// intruso e un'altra che, presa la posizione dell'intruso, vi ci inserisca
// nuovamente uno 0.
// ATTENZIONE: si risolva l'esercizio non restituendo un parametro dalla prima
// sottofunzione. Che parametri in input devo dare a quest'ultima?

const int MAXDIM = 100;

#include <stdio.h>

void popolaArray(int array[], int dimensione);
void trovaPosizione(int array[], int dimensione, int *intruso);

int main() {
    int array[MAXDIM];

    int dimensione;

    printf("Inserisci dimensione dell'array: \n");
    scanf("%d", &dimensione);

    popolaArray(array, dimensione);

    int intruso = -1;

    trovaPosizione(array, dimensione, &intruso);

    if(intruso != -1) {
        array[intruso] = 0;
    }
}

void popolaArray(int array[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        printf("Inserisci l'%d - elemento: ", i + 1);
        scanf("%d", &array[i]);
    }
}

void trovaPosizione(int array[], int dimensione, int* intruso) {
    for (int i = 0; i < dimensione; i++) {
        if (array[i] != 0) {
            *intruso = i;  
            return;  
        }
    }
}