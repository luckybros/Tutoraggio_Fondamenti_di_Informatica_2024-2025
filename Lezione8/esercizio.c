/*Il candidato realizzi una funzione:
studente * eliminaRipetuti(studente * v, int dim, int * newDim);
che, ricevuto in ingresso un vettore v di strutture dati di tipo studente e la dimensione
dim di tale vettore, restituisca in un nuovo vettore allocato dinamicamente gli elementi
del vettore iniziale v senza ripetizioni. Ovviamente, siccome riguardo uno stesso
studente vi sono più strutture dati memorizzate, sarà necessario copiare nel vettore
risultato la struttura dati più recente, cioè quella in cui lo studente ha sostenuto più
esami. A tal scopo, si noti che la segreteria aggiunge sempre in fondo al file le nuove
informazioni, e di fatto il file risulta essere parzialmente ordinato: relativamente ad ogni
studente, la riga contenente più esami è sempre quella "più in fondo" nel file (e quindi
più in fondo nel vettore v).*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CARATTERI 65
#define MAX_VOTI 22

typedef struct {
    int matricola;
    char cognome[MAX_CARATTERI];
    char nome[MAX_CARATTERI];
    int numEsami;
    int voti[MAX_VOTI];
} Studente;

int leggiStudente(FILE* fp, Studente* dest);
int uguali(Studente s1, Studente s2);
int contaDiversi(Studente* v, int dim);
Studente* eliminaRipetuti(Studente* v, int dim, int* newDim);
int leggiStudente(FILE* fp, Studente* dest);
Studente* leggiTuttiStudenti(char* fileName, int* dim);

int main() {
    Studente * listaRip;
    Studente * lista;

    int dimListaRip, dimLista;
    int i;

    listaRip = leggiTuttiStudenti("elenco.txt", &dimListaRip);
    lista = eliminaRipetuti(listaRip, dimListaRip, &dimLista);

    for (i=0; i<dimLista; i++) {
        printf("%d %s %s %d\n",
            lista[i].matricola,
            lista[i].cognome,
            lista[i].nome,
            lista[i].numEsami);
    }

    free(listaRip);
    free(lista);

    //system("PAUSE");
    return 0;
}

Studente* leggiTuttiStudenti(char* fileName, int* dim) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        // return -1;
        return NULL;
    }

    *dim = 0;

    Studente pippo;

    while(leggiStudente(file, &pippo) == 0) {
        (*dim)++;
    }

    rewind(file);

    Studente* studenti = (Studente*) calloc((*dim), sizeof(Studente));

    for(int i = 0; i < (*dim); i++) {
        leggiStudente(file, &(studenti[i]));
    }

    fclose(file);

    return studenti;
}

int leggiStudente(FILE* fp, Studente* dest) {
    int result = -1;
    if(fscanf(fp, "%d %s %s %d", &(dest->matricola), dest->nome, dest->cognome, &(dest->numEsami)) == 4) {
        result = 0;
    }

    for(int i = 0; i < dest->numEsami; i++) {
        if(fscanf(fp, "%d", &(dest->voti[i])) != 1) {
            result = -1;
        }
    }

    return result;
}

Studente* eliminaRipetuti(Studente* v, int dim, int* newDim) {

    *newDim = contaDiversi(v, dim);
    Studente* nuovaLista = (Studente*) malloc((*newDim)*sizeof(Studente));
    
    int trovato;
    int riemp = 0;

    for(int i = dim - 1; i >= 0; i--) {
        trovato = 0;
        for(int j = 0; j < riemp && !trovato; j++) {
            if(uguali(v[i], nuovaLista[j]) == 0) {
                trovato = 1;
            }
        }
        if(trovato == 0) {
            nuovaLista[riemp++] = v[i]; 
        }
    }

    return nuovaLista;

}

// [Teresa], [Luca], [Teresa], [Adriana], [Luigi] 
// [], [], [], []


int uguali(Studente s1, Studente s2) {
    if((strcmp(s1.nome, s2.nome) == 0) && (strcmp(s1.cognome, s2.cognome) == 0) && s1.matricola == s2.matricola) {
        return 0;
    }

    return -1;
}

int contaDiversi(Studente* studenti, int dim) {
    int risultato = 0;
    int trovato;

    for(int i = 0; i < dim; i++) {
        trovato = 0;
        for(int j = i + 1; j < dim && !trovato; j++) {
            if(uguali(studenti[i], studenti[j]) == 0) {
                trovato = 1;
            }
        }
        if(trovato == 0) {
            risultato++;
        } 
    }

    return risultato;
}

// [Teresa], [Luca], [Teresa], [Adriana], [Luigi] 


