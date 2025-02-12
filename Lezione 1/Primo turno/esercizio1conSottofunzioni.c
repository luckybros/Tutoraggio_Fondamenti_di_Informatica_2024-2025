const int MAXDIM = 100;

#include <stdio.h>

// Firma delle funzioni
void popolaArray(int array[], int dimensione);
void inserisciPosizioni(int* primaPosizione, int* secondaPosizione, int dimensione);
int verificaSomma(int array[], int dimensione, int somma);

int main() {
    int array[MAXDIM];

    int dimensione;

    printf("Inserisci dimensione dell'array: \n");
    scanf("%d", &dimensione);

    popolaArray(array, dimensione);

    int primaPosizione, secondaPosizione;

    inserisciPosizioni(&primaPosizione, &secondaPosizione, dimensione);

    int somma = array[primaPosizione] + array[secondaPosizione];

    int risultato = verificaSomma(array, dimensione, somma);

    if (risultato == -1) {
        printf("La somma non è presente all'interno dell'array!\n");
    } else {
        printf("La somma è presente in posizione %d!\n", risultato);
    }

    return 0;
}

// Definizioni delle funzioni

void popolaArray(int array[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        printf("Inserisci l'%d - elemento: ", i + 1);
        scanf("%d", &array[i]);
    }
}

void inserisciPosizioni(int* primaPosizione, int* secondaPosizione, int dimensione) {
    while (*primaPosizione < 0 || *primaPosizione >= dimensione || *secondaPosizione < 0 || *secondaPosizione >= dimensione) {
        printf("Inserisci la prima posizione: ");
        scanf("%d", primaPosizione);
        printf("Inserisci la seconda posizione: ");
        scanf("%d", secondaPosizione);

        if (*primaPosizione < 0 || *primaPosizione >= dimensione || *secondaPosizione < 0 || *secondaPosizione >= dimensione) {
            printf("Errore nell'inserimento delle posizioni: riprova!\n");
        }
    }
}

int verificaSomma(int array[], int dimensione, int somma) {
    for (int i = 0; i < dimensione; i++) {
        if (array[i] == somma) {
            return i;  
        }
    }
    return -1;  
}
