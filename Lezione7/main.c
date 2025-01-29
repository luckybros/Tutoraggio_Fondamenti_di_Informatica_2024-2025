#include "studenti.h"

int main() {
    int dim = 0;
    Studente* studenti = leggiTuttiGliStudenti("listaStud.txt", &dim);

    for(int i = 0; i < dim; i++) {
        printf("%s %s %d\n", studenti[i].nome, studenti[i].cognome, studenti[i].matricola);
        creaNomeFile(studenti[i]);
    }

    int numeroEsami = 0;
    RiepilogoEsame esami[NUMERO_ESAMI];

    for(int i = 0; i < dim; i++) {
        char* nomeFile = malloc(strlen("fileStudenti/") + strlen(studenti[i].nome) + strlen(studenti[i].cognome) + 5);
        strcat(nomeFile, "fileStudenti/");
        strcat(nomeFile, studenti[i].nome);
        strcat(nomeFile, studenti[i].cognome);
        strcat(nomeFile, ".txt");

        aggiornaEsamiSostenuti(nomeFile, esami, &numeroEsami);

        free(nomeFile);
    }

    printf("\n\n");
    for(int i = 0; i < numeroEsami; i++) {
        printf("Codice:%s Numero studenti:%d Media voto:%.2d\n", esami[i].codice, esami[i].numStudenti, (esami[i].somma/esami[i].numStudenti));
    }

    free(studenti);
}
