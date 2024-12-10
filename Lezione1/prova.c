/* Si realizzi un programma che memorizza le informazioni per un numero variabile di giocatori (max 100) per un 
videogioco online.
Per ciascun giocatore, si memorizzino le seguenti informazioni:
Nome (50 caratteri)
Livello (intero)
Punti esperienza (intero)
Classe (20 caratteri: "Cavaliere", "Mago" o "Samurai")

Si realizzino le seguenti funzioni:
 una funzione che restituisca il livello di un giocatore, dato il suo nome (se presente);
 una funzione che stampi a video le informazioni di un giocatore dato il suo nome;
 una funzione che permetta di inserire le informazioni di un nuovo giocatore;
 una funzione che calcoli la media dei punti esperienza di tutti i giocatori;
 una funzione che stampi a video le informazioni di tutti i giocatori con livello maggiore di 10;
 una funzione che restituisca la classe più scelta tra i giocatori.*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NOME 51
#define MAX_PLAYER 100
#define MAX_CLASS 21

typedef struct{
    char nome[MAX_NOME];
    int livello;
    int exp;
    char classe[MAX_CLASS];
} Giocatore;

int restituisciLivello(Giocatore giocatori[], int numGiocatori, char nome[]);
bool stampaInfo(Giocatore giocatori[], int numGiocatori, char nome[]);
void inserisciGiocatore(Giocatore giocatori[], int numGiocatori);
float calcolaMedia(Giocatore giocatori[], int numGiocatori);
void stampaGiocatoriForti(Giocatore giocatori[], int numGiocatori);
void stampaModa(Giocatore giocatori[], int numGiocatori, char classePiuNumerosa[], int* occorrenze);
bool verificaClasse(char classe[]);

int main() {

    Giocatore giocatori[MAX_PLAYER];
    int numGiocatori = 0;

    int scelta;
    do {
        printf("Selezionare la funzione desiderata: \n");
        printf("1)Dimmi il livello di un giocatore a mia scelta\n");
        printf("2)Dimmi le informazioni di un giocatore a mia scelta\n");
        printf("3)Voglio aggiungere le informazioni di un nuovo giocatore\n");
        printf("4)Voglio calcolare la media\n");
        printf("5)Dimmi i giocatori che vanno oltre il livello 10\n");
        printf("6)Dimmi la classe più scelta\n");
        printf("0)Esci dal programma\n");
        scanf("%d", &scelta);
        switch(scelta) {
            case 1: 
                //  checkare che il nome sia minore della dimensione
                printf("%s\n", "Inserisci nome giocatore:");
                char nome1[MAX_NOME];
                scanf("%s", nome1);
                int livello = restituisciLivello(giocatori, numGiocatori, nome1);
                if(livello != -1) {
                    printf("Il livello del giocatore è: %d\n", livello);
                }
                else {
                    printf("%s\n", "Errore: giocatore non trovato!\n");
                }
                break;
            case 2: 
                printf("%s\n", "Inserisci nome giocatore:\n");
                char nome2[MAX_NOME];
                scanf("%s", nome2);

                bool esito = stampaInfo(giocatori, numGiocatori, nome2);

                if(!esito) {
                    printf("Errore: il nome non è stato trovato!\n");
                }
                break;
            case 3: 
                if(numGiocatori < MAX_PLAYER) {
                    inserisciGiocatore(giocatori, numGiocatori);
                    printf("Inserimento avvenuto con successo!\n");
                    numGiocatori++;
                }
                else {
                    printf("Errore! Numero massimo giocatori raggiunto!\n");
                }
                break;
            case 4: 
                float media = calcolaMedia(giocatori, numGiocatori);
                printf("La media dei giocatori è pari a %.2f", media); 
                break;
            case 5: 
                stampaGiocatoriForti(giocatori, numGiocatori);
                break;
            case 6: 
                char classe[MAX_CLASS];
                int occorrenze = 0;
                stampaModa(giocatori, numGiocatori, classe, &occorrenze);
                printf("La classe più scelta dagli utenti è %s con %d occorrenze!\n", classe, occorrenze);
                break;
            case 0: 
                printf("Uscita dal programma...");
                break;
            default: 
                printf("%s", "Scelta non valida: riprova!\n");
                break;
        }

    } while(scelta != 0);
        
}

int restituisciLivello(Giocatore giocatori[], int numGiocatori, char nome[]) {
    for(int i = 0; i < numGiocatori; i++) {
        if(strcmp(nome, giocatori[i].nome) == 0) {
            return giocatori[i].livello;
        }
    }

    return -1;
}

bool stampaInfo(Giocatore giocatori[], int numGiocatori, char nome[]) {
    for(int i = 0; i < numGiocatori; i++) {
        if(strcmp(nome, giocatori[i].nome) == 0) {
            printf("Il livello del giocatore è %d\n", giocatori[i].livello);
            printf("I punti esperienza del giocatore sono %d\n", giocatori[i].exp);
            printf("La classe del giocatore è %s\n", giocatori[i].classe);
            return true;
        }
    }

    return false;
}

void inserisciGiocatore(Giocatore giocatori[], int numGiocatori) {
    printf("Inserisci nome giocatore: ");
    scanf("%s", giocatori[numGiocatori].nome);

    printf("Inserisci livello giocatore: ");
    scanf("%d", &giocatori[numGiocatori].livello);

    printf("Inserisci esperienza giocatore: ");
    scanf("%d", &giocatori[numGiocatori].exp);

    bool valido = false;

    while(!valido) {
        printf("Inserisci classe giocatore (Cavaliere, Mago o Samurai): \n");
        scanf("%s", giocatori[numGiocatori].classe);

        valido = verificaClasse(giocatori[numGiocatori].classe);

        if(!valido) {
            printf("Errore: classe non valida!\n");
        }
    }        
}

float calcolaMedia(Giocatore giocatori[], int numGiocatori) {
    float somma = 0;

    for(int i = 0; i < numGiocatori; i++) {
        somma += giocatori[i].exp;
    }

    float media = somma/numGiocatori;

    return media;
}

void stampaGiocatoriForti(Giocatore giocatori[], int numGiocatori) {
    for(int i = 0; i < numGiocatori; i++) {
        if(giocatori[i].livello > 10) {
            printf("Il nome del giocatore è %s\n", giocatori[i].nome);
            printf("Il livello del giocatore è %d\n", giocatori[i].livello);
            printf("I punti esperienza del giocatore sono %d\n", giocatori[i].exp);
            printf("La classe del giocatore è %s\n", giocatori[i].classe);
        }        
    }
}

void stampaModa(Giocatore giocatori[], int numGiocatori, char classePiuNumerosa[], int* occorrenze) {

    int conteggioCavaliere = 0, conteggioMago = 0, conteggioSamurai = 0;

    for(int i = 0; i < numGiocatori; i++) {
        if(strcmp(giocatori[i].classe, "Cavaliere") == 0) {
            conteggioCavaliere++;
        }
        else if(strcmp(giocatori[i].classe, "Mago") == 0) {
            conteggioMago++;
        }
        else if(strcmp(giocatori[i].classe, "Samurai") == 0) {
            conteggioSamurai++;
        }
    }

    if(conteggioCavaliere >= conteggioMago && conteggioCavaliere >= conteggioSamurai) {
        *occorrenze = conteggioCavaliere;
        strcpy(classePiuNumerosa, "Cavaliere");
    }
    else if(conteggioMago >= conteggioCavaliere && conteggioMago >= conteggioSamurai) {
        *occorrenze = conteggioMago;
        strcpy(classePiuNumerosa, "Mago");
    }
    else if(conteggioSamurai >= conteggioMago && conteggioSamurai >= conteggioCavaliere) {
        *occorrenze = conteggioSamurai;
        strcpy(classePiuNumerosa, "Samurai");
    }
    //*occorrenze = massimo(massimo(conteggioCavaliere, conteggioMago), conteggioSamurai);
}

bool verificaClasse(char classe[]) {
    if(strcmp(classe, "Cavaliere") == 0 || strcmp(classe, "Mago") == 0 || strcmp(classe, "Samurai") == 0){
        return true;
    }
    return false;
}