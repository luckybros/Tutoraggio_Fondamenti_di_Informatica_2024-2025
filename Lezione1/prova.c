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

#include <stdbool.h>

#define MAX_NOME 51
#define MAX_PLAYER 100
#define MAX_CLASS 21

int restituisciLivello(Giocatore giocatori[], int numGiocatori, char nome[]);
bool stampaInfo(Giocatore giocatori[], int numGiocatori, char nome[]);
void inserisciGiocatore(Giocatore giocatori[], int *numGiocatori);
float calcolaMedia(Giocatore giocatori[], int numGiocatori);
void stampaGiocatoriForti(Giocatore giocatori[], int numGiocatori);
void stampaModa(Giocatore giocatori[], int numGiocatori, char classePiuNumerosa[], int* occorrenze);
bool verificaClasse(char classe[]);
void stampaMenu();

typedef struct{
    char nome[MAX_NOME];
    int livello;
    int exp;
    char classe[MAX_CLASS];
} Giocatore;

int main() {

    Giocatore giocatori[MAX_PLAYER];
    int numGiocatori = 0;

    int scelta;
    do {
        scanf("%d", &scelta);

        switch(scelta) {
            case 1: 
                //  checkare che il nome sia minore della dimensione
                printf("%s\n", "Inserisci nome giocatore:");
                char nome[MAX_NOME];
                scanf("%s", nome);
                int livello = restituisciLivello(giocatori, numGiocatori, nome);
                if(livello != -1) {
                    printf("Il livello del giocatore è: %d\n", livello);
                }
                else {
                    printf("%s\n", "Errore: giocatore non trovato!");
                }
                break;
            case 2: 
                stampaInfo();
                break;
            case 3: 
                inserisciGiocatore();
                break;
            case 4: 
                calcolaMedia();
                break;
            case 5: 
                stampaGiocatoriForti();
                break;
            case 6: 
                stampaModa();
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