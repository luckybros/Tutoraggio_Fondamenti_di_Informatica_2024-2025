#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NOME 51
#define MAX_DATA 11
#define MAX_PARTITE 10

typedef struct {
    int id;
    char squadra1[MAX_NOME];
    char squadra2[MAX_NOME];
    int gol1;
    int gol2;
    char data[MAX_DATA];
    char luogo[MAX_NOME];
} Partita;

void aggiungiPartita(Partita partite[], int* numeroPartite);
bool cancellaPartita(Partita partite[], int* numeroPartite, int id);
void getPartitaPerData(Partita partite[], int numeroPartite, char data[]);
void calcolaPuntiPartite(Partita partite[], int numeroPartite, char squadra[], int* punti, int* partiteGiocate);

int main() {
    int dimensioneMassima = MAX_PARTITE;

    Partita* partite = (Partita*)malloc(sizeof(Partita)*MAX_PARTITE);
    int numeroPartite = 0;

    int scelta;
    do {
        printf("===========================================\n");
        printf("| Benvenut* nel tuo menù per le  partite  |\n");
        printf("===========================================\n");
        printf("Scegli un'operazione tra le seguenti:\n");
        printf(" [1] Aggiungi una nuova partita\n");
        printf(" [2] Elimina una partita esistente\n");
        printf(" [3] Stampa le partite in una determinata data\n");
        printf(" [4] Stampa il punteggio di una squadra\n");
        printf(" [0] Uscire dal programma\n");
        printf("=========================================\n");
        printf("Inserisci la tua scelta: ");
        scanf("%d", &scelta);
        switch(scelta) {
            case 1: 
                if(numeroPartite >= dimensioneMassima) {
                    dimensioneMassima *= 2;
                    Partita* vecchioValore = partite;
                    partite = realloc(partite, dimensioneMassima*sizeof(Partita));
                    if(!partite) {
                        perror("Errore allocazione memoria\n");
                        free(vecchioValore);
                        return -1;
                    }
                }
                aggiungiPartita(partite, &numeroPartite);
                break;
            case 2: 
                int idDaRimuovere;
                printf("Inserisci ID partita da rimuovere: \n");
                scanf("%d", &idDaRimuovere);

                if(!cancellaPartita(partite, &numeroPartite, idDaRimuovere)) {
                    printf("Errore: partita non trovata!\n");
                }
                else {
                    printf("Partita rimossa correttamente!\n");
                }
                break;
            case 3: 
                char dataDaCercare[MAX_DATA];
                printf("Inserisci la data da cercare (gg/mm/yyyy):\n");
                scanf("%11s", dataDaCercare);

                getPartitaPerData(partite, numeroPartite, dataDaCercare);
                // printf("ID Partita: %d, %s VS %s", partitaTrovata.id, partitaTrovata.squadra1, partitaTrovata.squadra2);
                break;

            case 4:
                char squadraDaCercare[MAX_NOME];
                printf("Inserisci nome della squadra:\n");
                scanf("%[^\n]", squadraDaCercare);

                int punti, partiteGiocate;

                calcolaPuntiPartite(partite, numeroPartite, squadraDaCercare, &punti, &partiteGiocate);

                printf("La squadra %s ha giocato %d partite ottenendo %d punti\n", squadraDaCercare, partiteGiocate, punti);
                break;
            case 0: 
                
                break;
            default: 
                
                break;
        }

    } while(scelta != 0);

    free(partite);
}