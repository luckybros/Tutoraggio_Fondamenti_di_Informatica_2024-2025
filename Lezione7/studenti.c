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

char* creaNomeFile(Studente studente) {
    char* nomeFile = malloc(strlen("fileStudenti/") + strlen(studente.nome) + strlen(studente.cognome) + 5);

    strcat(nomeFile, "fileStudenti/");
    strcat(nomeFile, studente.nome);
    strcat(nomeFile, studente.cognome);
    strcat(nomeFile, ".txt");

    FILE* file = fopen(nomeFile, "w");
    if (!file) {
        perror("Errore nell'apertura del file");
        return -1;
    }

    fclose(file);

    return nomeFile;
}