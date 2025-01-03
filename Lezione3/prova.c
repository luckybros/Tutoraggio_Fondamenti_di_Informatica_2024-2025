/*Si realizzi un programma che memorizza le informazioni per un numero variabile di partite di un campionato di calcio.
Per ciascuna partita, si memorizzino le seguenti informazioni:
- ID partita
- Nome Squadra 1 (50 caratteri)
- Nome Squadra 2 (50 caratteri)
- Gol fatti da Squadra 1 (intero)
- Gol fatti da Squadra 2 (intero)
- Data (stringa di massimo 10 caratteri, formato "gg/mm/aaaa")
- Luogo (50 caratteri)

Si realizzino le seguenti funzioni: 
- Una funzione che permetta di inserire una nuova partita; 
- Una funziona che permetta di cancellare una partita;
- Una funzione che, data una data, stampi le informazioni relative alle partite che si disputano in quella data;
- Una funzione che, dato il nome di una squadra, restituisca il numero di punti fatti e il numero di partite giocate (seguendo la regola dei 3 punti per vittoria, 1 punto per pareggio, 0 punti per sconfitta);

NOTA: si utilizzi la memoria Heap

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NOME 101
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

void aggiungiPartita(Partita* partite, int* numeroPartite);
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
            case 1: {
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

                printf("\n \n \n");
                break;
            }
            case 2: {
                int idDaRimuovere;
                printf("Inserisci ID partita da rimuovere: \n");
                scanf("%d", &idDaRimuovere);

                if(!cancellaPartita(partite, &numeroPartite, idDaRimuovere)) {
                    printf("Errore: partita non trovata!\n");
                }
                else {
                    printf("Partita rimossa correttamente!\n");
                }
                printf("\n \n \n");
                break;
            }
            case 3: {
                char dataDaCercare[MAX_DATA];
                printf("Inserisci la data da cercare (gg/mm/yyyy):\n");
                scanf("%11s", dataDaCercare);

                getPartitaPerData(partite, numeroPartite, dataDaCercare);
                // printf("ID Partita: %d, %s VS %s", partitaTrovata.id, partitaTrovata.squadra1, partitaTrovata.squadra2);
                printf("\n \n \n");
                break;
            }
            case 4: {
                char squadraDaCercare[MAX_NOME];
                printf("Inserisci nome della squadra:\n");
                scanf("%s", squadraDaCercare);

                int punti, partiteGiocate;

                calcolaPuntiPartite(partite, numeroPartite, squadraDaCercare, &punti, &partiteGiocate);

                printf("La squadra %s ha giocato %d partite ottenendo %d punti\n", squadraDaCercare, partiteGiocate, punti);
                printf("\n \n \n");
                break;
            }
            case 0: 
                printf("Uscita dal programma...\n");
                break;
            default: 
                printf("Scelta errata: riprova!\n");
                printf("\n \n \n");
                break;
        }

    } while(scelta != 0);

    free(partite);
}

void aggiungiPartita(Partita* partite, int* numeroPartite) {
    printf("Inserisci ID della partita: \n");
    scanf("%d", &partite[*numeroPartite].id);

    printf("Inserisci squadra 1: \n");
    scanf("%s", partite[*numeroPartite].squadra1);

    printf("Inserisci squadra 2: \n");
    scanf("%s", partite[*numeroPartite].squadra2);
    
    printf("Inserisci numero gol squadra 1: \n");
    scanf("%d", &partite[*numeroPartite].gol1);

    printf("Inserisci numero gol squadra 2: \n");
    scanf("%d", &partite[*numeroPartite].gol2);

    printf("Inserisci data (gg/mm/yyyy): \n");
    scanf("%11s", partite[*numeroPartite].data);

    printf("Inserisci luogo: \n");
    scanf("%s", partite[*numeroPartite].luogo);

    (*numeroPartite)++;
}

bool cancellaPartita(Partita partite[], int* numeroPartite, int id) {
    if(*numeroPartite == 0) {
        printf("Errore: la lista è vuota!\n");
        return false;
    }

    int indice = -1;

    for(int i = 0; i < *numeroPartite; i++) {
        // Ho trovato la partita da cancellare
        if(partite[i].id == id) {
            indice = i;
            break;
        }
    }

    if(indice == -1) {
        printf("L'ID non è stato trovato!\n");
        return false;
    }

    for(int i = indice; i < *numeroPartite - 1; i++) {
        partite[i] = partite[i + 1];
    }

    (*numeroPartite)--;

    return true;
}

void getPartitaPerData(Partita partite[], int numeroPartite, char data[]) {
    int trovato = -1;

    for(int i = 0; i < numeroPartite; i++) {
        if(strcmp(partite[i].data, data) == 0) {
            printf("ID: %d | %s VS %s | %d - %d | Luogo: %s\n", partite[i].id, partite[i].squadra1, partite[i].squadra2, partite[i].gol1, partite[i].gol2, partite[i].luogo);
            trovato = 0;
        }
    }

    if(trovato == -1) {
        printf("Nessuna partita trovata per la data specificata %s\n", data);
    }
}

void calcolaPuntiPartite(Partita partite[], int numeroPartite, char squadra[], int* punti, int* partiteGiocate) {

    *punti = 0;
    *partiteGiocate = 0;

    for(int i = 0; i < numeroPartite; i++) {
        if(strcmp(partite[i].squadra1, squadra) == 0 || strcmp(partite[i].squadra2, squadra) == 0) {
            (*partiteGiocate)++;

            // La squadra si trova sullo slot sinistro
            if(strcmp(partite[i].squadra1, squadra) == 0) {
                if(partite[i].gol1 > partite[i].gol2) {
                    (*punti) += 3;
                }

                else if(partite[i].gol1 == partite[i].gol2) {
                    (*punti) += 1;
                }
            }

            if(strcmp(partite[i].squadra2, squadra) == 0) {
                if(partite[i].gol1 < partite[i].gol2) {
                    (*punti) += 3;
                }

                else if(partite[i].gol1 == partite[i].gol2) {
                    (*punti) += 1;
                }
            }
        }
    }
}


