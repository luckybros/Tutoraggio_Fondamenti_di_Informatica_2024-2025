#include <stdio.h>
#include <string.h>

#define MAX_GIOCATORI 100
#define MAX_NOME 50
#define MAX_CLASSE 20

typedef struct {
    char nome[MAX_NOME];
    int livello;
    int punti_esperienza;
    char classe[MAX_CLASSE];  // Classe del giocatore: "Cavaliere", "Mago" o "Samurai"
} Giocatore;

void inserisciGiocatore(Giocatore giocatori[], int *numGiocatori);
int ottieniLivello(Giocatore giocatori[], int numGiocatori, char nome[]);
void stampaInformazioniGiocatore(Giocatore giocatori[], int numGiocatori, char nome[]);
float mediaPuntiEsperienza(Giocatore giocatori[], int numGiocatori);
void stampaGiocatoriLivelloMaggioreDi10(Giocatore giocatori[], int numGiocatori);
void classePiuScelta(Giocatore giocatori[], int numGiocatori);

int main() {
    Giocatore giocatori[MAX_GIOCATORI];
    int numGiocatori = 0;
    int scelta;

    do {
        printf("\n\n-----Menu Gioco Online-----\n");
        printf("[1] Inserire Nuovo Giocatore\n");
        printf("[2] Ricerca Giocatore\n");
        printf("[3] Media Punti Esperienza dei Giocatori Attivi\n");
        printf("[4] Giocatori con Livello Maggiore di 10\n");
        printf("[5] Classe Più Scelta\n");
        printf("[0] Esci\n\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);

        switch(scelta) {
            case 1:
                inserisciGiocatore(giocatori, &numGiocatori);
                break;
            case 2: {
                char nomeRicerca[MAX_NOME];
                printf("Inserisci nome del giocatore per visualizzarne le informazioni: ");
                scanf("%s", nomeRicerca);
                stampaInformazioniGiocatore(giocatori, numGiocatori, nomeRicerca);
                break;
            }
            case 3: {
                float media = mediaPuntiEsperienza(giocatori, numGiocatori);
                printf("La media dei punti esperienza di tutti i giocatori attivi è: %f\n", media);
                break;
            }
            case 4:
                printf("Giocatori con livello maggiore di 10:\n");
                stampaGiocatoriLivelloMaggioreDi10(giocatori, numGiocatori);
                break;
            case 5:
                classePiuScelta(giocatori, numGiocatori);
                break;
            case 0:
                printf("Uscita in corso...");
                break;
            default:
                printf("Scelta non valida, riprova!\n");
                break;
        }
    } while (scelta != 0);  
    
    return 0;
}

void inserisciGiocatore(Giocatore giocatori[], int *numGiocatori) {
    if (*numGiocatori >= MAX_GIOCATORI) {
        printf("Numero massimo di giocatori raggiunto!\n");
        return;
    }
    
    printf("Inserisci il nome del giocatore: ");
    scanf("%s", giocatori[*numGiocatori].nome);
    
    printf("Inserisci il livello del giocatore: ");
    scanf("%d", &giocatori[*numGiocatori].livello);
    
    printf("Inserisci i punti esperienza del giocatore: ");
    scanf("%d", &giocatori[*numGiocatori].punti_esperienza);
    
    char classeScelta[MAX_CLASSE];
    int classeValida = 0;
    
    while (!classeValida) {
        printf("Scegli la classe del giocatore (Cavaliere, Mago, Samurai): ");
        scanf("%s", classeScelta);
        
        if (strcmp(classeScelta, "Cavaliere") == 0 || strcmp(classeScelta, "Mago") == 0 || strcmp(classeScelta, "Samurai") == 0) {
            classeValida = 1;
            strcpy(giocatori[*numGiocatori].classe, classeScelta);
        } else {
            printf("Classe non valida. Scegli tra Cavaliere, Mago o Samurai.\n");
        }
    }
    
    (*numGiocatori)++;
}

int ottieniLivello(Giocatore giocatori[], int numGiocatori, char nome[]) {
    for (int i = 0; i < numGiocatori; i++) {
        if (strcmp(giocatori[i].nome, nome) == 0) {
            return giocatori[i].livello;
        }
    }
    return -1; // Non trovato
}

void stampaInformazioniGiocatore(Giocatore giocatori[], int numGiocatori, char nome[]) {
    for (int i = 0; i < numGiocatori; i++) {
        if (strcmp(giocatori[i].nome, nome) == 0) {
            printf("Nome: %s\n", giocatori[i].nome);
            printf("Livello: %d\n", giocatori[i].livello);
            printf("Punti esperienza: %d\n", giocatori[i].punti_esperienza);
            printf("Classe: %s\n", giocatori[i].classe);
            return;
        }
    }
    printf("Giocatore non trovato!\n");
}

float mediaPuntiEsperienza(Giocatore giocatori[], int numGiocatori) {
    int totalePunti = 0;
    for (int i = 0; i < numGiocatori; i++) {
        totalePunti += giocatori[i].punti_esperienza;
    }
    return (float)totalePunti / numGiocatori;
}

void stampaGiocatoriLivelloMaggioreDi10(Giocatore giocatori[], int numGiocatori) {
    for (int i = 0; i < numGiocatori; i++) {
        if (giocatori[i].livello > 10) {
            printf("Nome: %s, Livello: %d, Punti Esperienza: %d, Classe: %s\n", 
                   giocatori[i].nome, giocatori[i].livello, giocatori[i].punti_esperienza, giocatori[i].classe);
        }
    }
}

void classePiuScelta(Giocatore giocatori[], int numGiocatori) {
    int conteggioCavaliere = 0, conteggioMago = 0, conteggioSamurai = 0;

    for (int i = 0; i < numGiocatori; i++) {
        if (strcmp(giocatori[i].classe, "Cavaliere") == 0) {
            conteggioCavaliere++;
        } else if (strcmp(giocatori[i].classe, "Mago") == 0) {
            conteggioMago++;
        } else if (strcmp(giocatori[i].classe, "Samurai") == 0) {
            conteggioSamurai++;
        }
    }

    if (conteggioCavaliere >= conteggioMago && conteggioCavaliere >= conteggioSamurai) {
        printf("La classe più scelta è: Cavaliere\n");
    } else if (conteggioMago >= conteggioCavaliere && conteggioMago >= conteggioSamurai) {
        printf("La classe più scelta è: Mago\n");
    } else if (conteggioSamurai >= conteggioCavaliere && conteggioSamurai >= conteggioMago) {
        printf("La classe più scelta è: Samurai\n");
    }
}
