#include "registroVoti.h"

void aggiungiStudente(Cella matrice[][MAX_COLONNE], int* numStudenti, int numMaterie, char nomeStudente[]) {

    for(int i = 0; i < numMaterie; i++) {
        strcpy(matrice[*numStudenti][i].nome, nomeStudente);

        if(*numStudenti == 0) {
            printf("Inserisci nome della %d - esima materia:\n", i + 1);
            scanf("%s", matrice[*numStudenti][i].materia);
        }
        else {
            strcpy(matrice[*numStudenti][i].materia, matrice[0][i].materia);
        }

        matrice[*numStudenti][i].voto = (rand() % 13) + 18;
    }

    (*numStudenti)++;
}