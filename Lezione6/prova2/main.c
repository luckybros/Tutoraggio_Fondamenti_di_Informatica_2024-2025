#include "prova.h"

int main() {
    int numLibriDaLeggere;

    printf("Inserisci numero di libri da leggere:\n");

    do {
        scanf("%d", &numLibriDaLeggere);

        if(numLibriDaLeggere <= 0) {
            printf("Errore: il numero deve essere almeno 1!\n");
        }
    }while(numLibriDaLeggere <= 0);
    
    Libro* libri = (Libro*) calloc(numLibriDaLeggere, sizeof(Libro));
    if(libri == NULL) {
        perror("Errore: non c'è memoria disponibile!\n");
        return -1;
    }

    letturaLibri(libri, numLibriDaLeggere);

    int scelta;

    do{
        printf("===========================================\n");
        printf("| Benvenut* nel tuo menù per la gestione libreria!  |\n");
        printf("===========================================\n");
        printf("Scegli un'operazione tra le seguenti:\n");
        printf(" [1] Stampa libri\n");
        printf(" [2] Elimina libri con prezzo maggiore di quello indicato\n");
        printf(" [0] Uscire dal programma\n");
        printf("=========================================\n");
        printf("Inserisci la tua scelta: ");

        scanf("%d", &scelta);

        switch(scelta) {
            case 1: 
                stampaLibri(libri, numLibriDaLeggere);
                break;
            case 2: {
                int prezzo;
                printf("Inserisci il prezzo dei libri da eliminare:\n");
                scanf("%d", &prezzo);
                int eliminati = eliminazionePrezzo(libri, &numLibriDaLeggere, prezzo);
                printf("Sono stati eliminati %d libri!\n", eliminati);
                break;
            }
            case 0:
                printf("Uscita dal programma...\n");
                break;

            default:
                printf("Errore: scelta non corretta!\n");
                break;
        }
    }while(scelta != 0);

    free(libri);
}