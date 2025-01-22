#include "studenti.h"

Studente leggiUnoStudente(FILE* file) {
    Studente studente;

    fscanf(file, "%s %s %d", studente.nome, studente.cognome, &studente.matricola);

    return studente;
}

Studente* leggiTuttiGliStudenti(char* nomeFile, int* dim) {

    FILE* file = fopen(nomeFile, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        return -1;
    }

    int numRighe = 0;

    Studente pippo;

    while(fscanf(file, "%s %s %d\n", pippo.nome, pippo.cognome, &pippo.matricola) == 3) {
        numRighe++;
    }

    rewind(file);

    Studente* studenti = (Studente*) calloc(numRighe, sizeof(Studente));

    for(int i = 0; i < numRighe; i++) {
        studenti[i] = leggiUnoStudente(file);
    }

    *dim = numRighe;

    fclose(file);

    return studenti;
}

void creaNomeFile(Studente studente) {
    char* nomeFile = malloc(strlen("fileStudenti/") + strlen(studente.nome) + strlen(studente.cognome) + 5);

    strcat(nomeFile, "fileStudenti/");
    strcat(nomeFile, studente.nome);
    strcat(nomeFile, studente.cognome);
    strcat(nomeFile, ".txt");

    FILE* file = fopen(nomeFile, "w");
    if (!file) {
        perror("Errore nell'apertura del file");
        // return -1;
    }

    char codice[MAX_NOME];
    int voto;
    int scelta;

    printf("Inserisci codice e voto dello studente %s %s\n", studente.nome, studente.cognome);
    
    do {
        printf("Inserisci codice:\n");
        scanf("%s", codice);

        printf("Inserisci voto:\n");
        scanf("%d", &voto);

        fprintf(file, "%s %d\n", codice, voto);

        printf("Vuoi continuare? Scegli 0 per terminare:\n");
        scanf("%d", &scelta);
    }while(scelta != 0);

    fclose(file);

    free(nomeFile);

}

int trovaPos(RiepilogoEsame* esami, int dim, char* codice) {
    for(int i = 0; i < dim; i++) {
        if(strcmp(esami[i].codice, codice) == 0) {
            return i;
        }
    }

    return -1;
}

void aggiornaEsamiSostenuti(char* nomeFile, RiepilogoEsame* esami, int* dim) {
    FILE* file = fopen(nomeFile, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        // return -1;
    }

    char codice[MAX_NOME];
    int voto;
    int pos;

    while(fscanf(file, "%s %d\n", codice, &voto) == 2) {
        if(voto >= 18) {
            pos = trovaPos(esami, *dim, codice);

            // TROVO ESAME NELLA LISTA
            if(pos != -1) {
                esami[pos].numStudenti++;
                esami[pos].somma += voto;
            }

            // NON TROVO L'ESAME
            else {
                strcpy(esami[*dim].codice, codice);
                esami[*dim].numStudenti = 1;
                esami[*dim].somma = voto;
                (*dim)++; 
            }
        }
    }

    fclose(file);
}


