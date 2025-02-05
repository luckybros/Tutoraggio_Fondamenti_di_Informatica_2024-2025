#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 21
#define MAX_TENTATIVI 3
#define MAX_PARTITE 100

typedef struct {
    char nome[MAX_NOME];
    int punteggio;
}Risultato;

int generaNumeroCasuale(int min, int max);
int calcolaPunteggio(int tentativi[], int numeroSegreto);
void registraRisultato(int punteggio, char* nome, Risultato* partite, int* dim);
void gioco(int numeroSegreto, int tentativi[], Risultato* partite, int* dim);
void stampaPartite(Risultato* partite, int dim);

int main() {
    int numeroSegreto = generaNumeroCasuale(0, 100);
    int* tentativi = calloc(MAX_TENTATIVI, sizeof(int));
    Risultato* partite = calloc(MAX_PARTITE, sizeof(Risultato));
    int dim = 0;

    gioco(numeroSegreto, tentativi, partite, &dim);
}

int generaNumeroCasuale(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int calcolaPunteggio(int tentativi[], int numeroSegreto) {
    int distanzaMinima = abs(tentativi[0] - numeroSegreto);

    int i = 1;
    do {
        if(abs(tentativi[i] - numeroSegreto) < distanzaMinima) {
            distanzaMinima = abs(tentativi[i] - numeroSegreto);
        }      
    } while(i < MAX_TENTATIVI && tentativi[i] != numeroSegreto);

    return 100 - distanzaMinima;
}

void registraRisultato(int punteggio, char* nome, Risultato* partite, int* dim) {
    Risultato nuovoRisultato;
    nuovoRisultato.punteggio = punteggio;
    strcpy(nuovoRisultato.nome, nome);

    partite[*dim] = nuovoRisultato;
    
    (*dim)++;
}

void gioco(int numeroSegreto, int tentativi[], Risultato* partite, int* dim) {
    int numeroTentativi = 0;

    do {
        printf("Inserisci il %d tentativo:\n", numeroTentativi + 1);
        scanf("%d", &tentativi[numeroTentativi]);
        printf("Hai inserito %d\n", tentativi[numeroTentativi]);

        if(tentativi[numeroTentativi] == numeroSegreto) {
            printf("Complimenti! Hai indovinato! Hai utilizzato %d tentativi\n", numeroTentativi + 1);
        }

        else if(tentativi[numeroTentativi] > numeroSegreto) {
            printf("Hai sbagliato! Il numero segreto è più piccolo di quello inserito\n");
        }

        else if(tentativi[numeroTentativi] < numeroSegreto) {
            printf("Hai sbagliato! Il numero segreto è più grande di quello inserito\n");
        }

        numeroTentativi++;
    } while(numeroTentativi < MAX_TENTATIVI && tentativi[numeroTentativi] != numeroSegreto);

    printf("ciao");
    int punteggio = calcolaPunteggio(tentativi, numeroSegreto);

    char nome[MAX_NOME];

    printf("Inserisci nome:\n");
    scanf("%[^\n]", nome);

    registraRisultato(punteggio, nome, partite, dim);
}

void stampaPartite(Risultato* partite, int dim) {
    printf("----------PUNTEGGI----------");
    for(int i = 0; i < dim; i++) {
        printf("%s %d\n", partite[i].nome, partite[i].punteggio);
    }
    printf("----------------------------");
}



