/*Creare un array, far scegliere all'utente due posizioni e verificare 
se la somma tra i numeri è presente all'interno dell'array. 
Se è presente, il programma stampa la posizione in cui la somma è 
collocata; altrimenti stampa -1. 
NOTA: gestire il caso in cui le posizioni non sono nell’array.*/
#define MAX_DIM 100

#include <stdio.h>

int main() {
    int array[MAX_DIM];

    int riempimento = 0;

    // Viene chiesta la dimensione dell'array all'utente
    int dimensione = -1;
    while(dimensione > 100 || dimensione <= 0) {
        printf("Inserisci dimensione dell'array");
        scanf("%d", &dimensione);

        if(dimensione > 100 || dimensione <= 0) {
            printf("Errore nel valore: ripeti\n");
        }
    }

    // Popoliamo l'array
    int i;
    for(i = 0; i < dimensione; i++){
        printf("Inserisci l' %d - elemento ", i + 1);
        scanf("%d", &array[i]);
        riempimento++;
    }

    // Scegliamo le posizioni
    int posizione1, posizione2;

    do {
        printf("Inserisci due posizioni da 0 a %d\n", dimensione - 1);
        printf("Posizione 1: ");
        scanf("%d", &posizione1);
        printf("Posizione 2: ");
        scanf("%d", &posizione2);

        if(posizione1 < 0 || posizione1 >= dimensione) {
            printf("Errore: la prima posizione non è valida!\n");
        }
        if(posizione2 < 0 || posizione2 >= dimensione){
            printf("Errore: la seconda posizione non è valida!\n");
        }

    } while(posizione1 < 0 || posizione1 >= dimensione || posizione2 < 0 || posizione2 >= dimensione);
    
    int somma = array[posizione1] + array[posizione2];
    int trovato = -1;

    for(int i = 0; i < dimensione && trovato != 1; i++) {
        if(array[i] == somma) {
            printf("La somma si trova all'indice %d", i);
            trovato = 1;
            //i = dimensione;
        }
    }

    if(trovato != 1) {
        printf("La somma non è trovata: %d", trovato);
    }
}