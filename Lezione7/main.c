#include "studenti.h"

int main() {
    int dim = 0;
    Studente* studenti = leggiTuttiGliStudenti("listaStud.txt", &dim);

    for(int i = 0; i < dim; i++) {
        printf("%s %s %d\n", studenti[i].nome, studenti[i].cognome, studenti[i].matricola);
    }

    creaNomeFile(studenti[0]);
    
    free(studenti);
}