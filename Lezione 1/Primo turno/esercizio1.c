// Creare un array, far scegliere all'utente due posizioni
// e verificare se la somma tra i numeri è presente all'interno
// dell'array. Se è presente, il programma stampa la posizione
// in cui la somma è collocata; altrimenti stampa -1.
// NOTA: gestire il caso in cui le posizioni non sono nell'array
const int MAXDIM = 100;

#include <stdio.h>

int main() {
    int array[MAXDIM];

    int dimensione;
    
    printf("Inserisci dimensione dell'array: \n");
    scanf("%d", &dimensione);

    // Inserimento degli elementi nell'array
    for(int i = 0; i < dimensione; i++) {
        printf("Inserisci l'%d - elemento: ", i+1);
        scanf("%d", &array[i]);
    }

    // Inserimento posizioni
    int primaPosizione, secondaPosizione;

    while(primaPosizione < 0 || primaPosizione >= dimensione || secondaPosizione < 0 || secondaPosizione >= dimensione) {
        printf("Inserisci la prima posizione: ");
        scanf("%d", &primaPosizione);
        printf("Inserisci la seconda posizione: ");
        scanf("%d", &secondaPosizione);

        if(primaPosizione < 0 || primaPosizione >= dimensione || secondaPosizione < 0 || secondaPosizione >= dimensione) {
            printf("Errore nell'inserimento delle posizioni: riprova!");
        }
    }

    int somma = array[primaPosizione] + array[secondaPosizione];
    int risultato = -1;

    for(int i = 0; i < dimensione; i++) {
        if(array[i] == somma) {
            risultato = i;
        }
    }

    if(risultato == -1) {
        printf("La somma non è presente all'interno dell'array!");
    }
    else {
        printf("La somma è presente in posizione %d!", risultato);
    }
}