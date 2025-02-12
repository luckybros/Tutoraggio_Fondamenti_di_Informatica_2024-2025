#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTITE 100

typedef struct {
    int id;
    char squadra1[50];
    char squadra2[50];
    int gol1;
    int gol2;
    char data[11];  // "gg/mm/aaaa"
    char luogo[50];
} Partita;

void inserisciPartita(Partita partite[], int* numeroPartite);
void stampaPartitePerData(Partita partite[], int numeroPartite, char data[]);
void calcolaPuntiGiocate(Partita partite[], int numeroPartite, char squadra[], int* punti, int* partiteGiocate);
void rimuoviPartita(Partita partite[], int* numeroPartite);

int main() {
    int max_capacity = MAX_PARTITE;

    Partita* partite = (Partita*)malloc(MAX_PARTITE * sizeof(Partita));  // array dinamico
    int numeroPartite = 0;
    
    int scelta;
    do {
        printf("\nMenu:\n");
        printf("1. Inserisci partita\n");
        printf("2. Stampa partite per data\n");
        printf("3. Calcola punti e partite giocate per squadra\n");
        printf("4. Rimuovi partita\n");
        printf("5. Esci\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                if (numeroPartite >= MAX_PARTITE) {
                    printf("Raggiunta la capacit\u00e0 massima: aumento la memoria disponibile.\n");
                    max_capacity *= 2;
                    partite = realloc(partite, (max_capacity) * sizeof(Partita));
                }
                inserisciPartita(partite, &numeroPartite);
                break;
            case 2: {
                char data[11];
                printf("Inserisci la data (gg/mm/aaaa): ");
                scanf("%s", data);
                stampaPartitePerData(partite, numeroPartite, data);
                break;
            }
            case 3: {
                char squadra[50];
                printf("Inserisci il nome della squadra: ");
                scanf("%s", squadra);
                int punti, partiteGiocate;
                calcolaPuntiGiocate(partite, numeroPartite, squadra, &punti, &partiteGiocate);
                printf("La squadra %s ha totalizzato %d punti e ha giocato %d partite.\n", squadra, punti, partiteGiocate);
                break;
            }
            case 4:
                rimuoviPartita(partite, &numeroPartite);
                break;
            case 5:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
                break;
        }
    } while (scelta != 5);
    
    free(partite);
    return 0;
}

void inserisciPartita(Partita partite[], int* numeroPartite) {
    if (*numeroPartite >= MAX_PARTITE) {
        printf("Numero massimo di partite raggiunto!\n");
        return;
    }

    printf("Inserisci i dati della partita:\n");
    printf("Squadra 1: ");
    scanf("%s", partite[*numeroPartite].squadra1);
    printf("Squadra 2: ");
    scanf("%s", partite[*numeroPartite].squadra2);
    printf("Gol fatti da %s: ", partite[*numeroPartite].squadra1);
    scanf("%d", partite[*numeroPartite].gol1);
    printf("Gol fatti da %s: ", partite[*numeroPartite].squadra2);
    scanf("%d", partite[*numeroPartite].gol2);
    printf("Data (gg/mm/aaaa): ");
    scanf("%s", partite[*numeroPartite].data);
    printf("Luogo: ");
    scanf("%s", partite[*numeroPartite].luogo);
    (*numeroPartite)++;
}

void stampaPartitePerData(Partita partite[], int numeroPartite, char data[]) {
    int trovate = 0;
    for (int i = 0; i < numeroPartite; i++) {
        if (strcmp(partite[i].data, data) == 0) {
            printf("ID: %d | Partita tra %s e %s il %s, Luogo: %s\n", 
                   partite[i].id, partite[i].squadra1, partite[i].squadra2, partite[i].data, partite[i].luogo);
            trovate = 1;
        }
    }

    if (!trovate) {
        printf("Nessuna partita trovata per la data %s.\n", data);
    }
}

void calcolaPuntiGiocate(Partita partite[], int numeroPartite, char squadra[], int* punti, int* partiteGiocate) {
    *punti = 0;
    *partiteGiocate = 0;

    for (int i = 0; i < numeroPartite; i++) {
        if (strcmp(partite[i].squadra1, squadra) == 0 || strcmp(partite[i].squadra2, squadra) == 0) {
            (*partiteGiocate)++;

            if (strcmp(partite[i].squadra1, squadra) == 0) {
                if (partite[i].gol1 > partite[i].gol2) {
                    (*punti) += 3;  // vittoria
                } else if (partite[i].gol1 == partite[i].gol2) {
                    (*punti) += 1;  // pareggio
                }
            }

            if (strcmp(partite[i].squadra2, squadra) == 0) {
                if (partite[i].gol2 > partite[i].gol1) {
                    (*punti) += 3;  
                } else if (partite[i].gol2 == partite[i].gol1) {
                    (*punti) += 1; 
                }
            }
        }
    }
}

void rimuoviPartita(Partita partite[], int* numeroPartite) {
    if (*numeroPartite == 0) {
        printf("Non ci sono partite da rimuovere.\n");
        return;
    }

    int id;
    printf("Inserisci l'ID della partita da rimuovere: ");
    scanf("%d", &id);

    int indiceDaRimuovere = -1;
    for (int i = 0; i < *numeroPartite; i++) {
        if (partite[i].id == id) {
            indiceDaRimuovere = i;
            break;
        }
    }

    if (indiceDaRimuovere == -1) {
        printf("Partita con ID %d non trovata.\n", id);
        return;
    }

    for (int i = indiceDaRimuovere; i < *numeroPartite - 1; i++) {
        partite[i] = partite[i + 1];
    }

    (*numeroPartite)--;

    printf("Partita con ID %d rimossa con successo.\n", id);
}
