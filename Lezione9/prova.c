#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 21
#define MAX_TENTATIVI 3

typedef struct {
    char nome[MAX_NOME];
    int punteggio;
} Risultato;

int generaNumeroCasuale(int min, int max);

int calcolaPunteggio(int tentativi[], int numeroSegreto);

void registraRisultato(int punteggio, char* nome, Risultato* partite, int* dim) ;
    
void gioco(int numeroSegreto, int tentativi[]);

void stampaPartite(Risultato* partite, int dim);

int main() {

}

int calcolaPunteggio(int tentativi[], int numeroSegreto) {
    int distanza = abs(tentativi[0] - numeroSegreto);

    do {

    } while();
}

// [60, 87, ]


void gioco(int numeroSegreto, int tentativi[]) {
    int numeroTentativi = 0;

    do {
        printf("Inserisci il %d tentativo:\n", numeroTentativi + 1);
        scanf("%d", &tentativi[numeroTentativi]);

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

    //int punteggio = calcolaPunteggio(tentativi, numeroSegreto);

    char nome[MAX_NOME];

    printf("Inserisci nome:\n");
    scanf("%[^\n]", nome);


    //registraRisultato();
}



int generaNumeroCasuale(int min, int max) {
    return rand() % (max - min + 1) + min;
}


