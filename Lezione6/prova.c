/*
Rispettando i principi della programmazione strutturata, progettare ed implementare un programma per la gestione di un inventario di prodotti di cancelleria.
 
Il programma prima permette di importare le informazioni per un numero di prodotti da file 
(il numero di prodotti è scelto dall'utente).
Poi permette di inserire le informazioni per un massimo di 10 prodotti da tastiera.
Poi mostra a video la lista dei prodotti costosi in esaurimento 
(ovvero quelli la cui quantità residua è minore di 10 ed il cui prezzo unitario è maggiore di 12 euro).
 
Specifiche implementative.
 
1) Per ciascun prodotto vengono memorizzate le seguenti informazioni in un record (struct) "prodotto": 
- identificativo (nome campo: id, tipo: num intero), 
- prezzo unitario (nome campo: prezzo, tipo: num reale), 
- quantità residua (nome campo: quantita, tipo: numero intero), 
- descrizione (nome campo: descrizione, tipo array di 101 caratteri)
 
2) all'avvio del programma, l'utente specifica (input da tastiera) 
il numero di prodotti le cui informazioni devono essere lette da file (max 50).
 
3) Successivamente il programma alloca lo spazio per ospitare una struttura dati "inventario" 
di tipo array di struct prodotto in area heap.
La struttura dati deve poter ospitare il numero di prodotti che 
l'utente ha scelto di leggere da file maggiorato di 10.
Ovvero se, ad esempio, l'utente ha scelto di leggere le info di 20 prodotti da file, 
la struttura dati deve poter contenere 30 prodotti. 

4) Il programma usa la funzione inizializzaInventario (di cui è fornita l'implementazione completa!) 
per leggere il contenuto del file "inventario2024.txt".
Il file è situato nel file system nella stessa directory dell'eseguibile.
Dopo l'inizializzazione, il programma stampa a video il numero di prodotti in inventario 
effettivamente importati da file.
 
La funzione inizializzaInventario ha la seguente signature:
int inizializzaInventario(Prodotto* prodotti, int numeroProdottiDaLeggere, const char* nomeFile)
prodotti: vettore di struct prodotto (o equivalentemente, puntatore alla testa del vettore) 
nel quale importare le informazioni lette da file;
numeroProdottiDaLeggere: numero prodotti da leggere dal file;
nomeFile: percorso del file da cui importare le informazioni.
La funzione restituisce il numero di prodotti effettivamente letti (e importati nel vettore prodotti).
 
5) Il programma permette di aggiungere prodotti da tastiera attraverso una funzione aggiungiProdotto (da implementare).
La lista di parametri della funzione prevede:
il vettore di record prodotto (o, equivalentemente, il puntatore alla testa del vettore), 
il numero di prodotti effettivamente presenti nel vettore inventario, 
la dimensione massima del vettore inventario.
 
6) stampa prodotti costosi in esaurimento
Il programma stampa a video la lista dei prodotti con quantità minore di 10 e prezzo unitario maggiore di 12 euro
attraverso la funzione 
stampaListaProdottiInEsaurimento (da implementare)
La lista di parametri della funzione prevede:
il vettore di record prodotto (o, equivalentemente, il puntatore alla testa del vettore). 
il numero di prodotti effettivamente presenti nel vettore inventario.
 
La lista di prodotti viene visualizzata a video nel seguente formato:
100 x Penna a sfera - prezzo: 10.50 Euro                                        
200 x Quaderno A4 - prezzo: 5.30 Euro                                           
50 x Calcolatrice scientifica - prezzo: 25.00 Euro
     
*/

#define MAX_DESCRIZIONE 101
#define MAX_PRODOTTI_LETTI 50

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
struct prodotto {
    int id;
    float prezzo;
    int quantita;
    char descrizione[MAX_DESCRIZIONE];
};
typedef struct prodotto Prodotto;
 
 
int inizializzaInventario(Prodotto *prodotti, int numeroProdottiDaLeggere, const char *nomeFile) {
    
    FILE* file = fopen(nomeFile, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        return -1;
    }
    int i = 0;
    // Legge numeroProdottiDaLeggere prodotti (meno se non sono presenti nel file)
    while (i < numeroProdottiDaLeggere && fscanf(file, "%d %f %d %[^\n]",
&prodotti[i].id,
&prodotti[i].prezzo,
&prodotti[i].quantita,
                                               prodotti[i].descrizione) == 4) {
        i++;
    }
    fclose(file);
    return i; // Restituisce il numero di prodotti effettivamente letti
}
 
bool aggiungiProdotto(Prodotto *prodotti, int *numProdottiPresenti, int dimensioneMassima) {
    if(*numProdottiPresenti == dimensioneMassima) {
        return false;
    }

    int scelta;

    do {
        printf("Inserisci l'ID del prodotto:\n");
        scanf("%d", &prodotti[*numProdottiPresenti].id);
        printf("Inserisci il prezzo del prodotto:\n");
        scanf("%f", &prodotti[*numProdottiPresenti].prezzo);
        printf("Inserisci la quantità del prodotto:\n");
        scanf("%d", &prodotti[*numProdottiPresenti].quantita);
        printf("Inserisci la descrizione del prodotto:\n");
        scanf("%s", prodotti[*numProdottiPresenti].descrizione);

        (*numProdottiPresenti)++;

        if(*numProdottiPresenti == dimensioneMassima) {
            printf("Dimensione massima raggiunta!\n");
            break;
        }

        printf("Vuoi inserire un altro prodotto? (0 - termina, 1 - continua)\n");

        do {
            scanf("%d", &scelta);

            if(scelta != 0 && scelta != 1) {
                printf("Errore: scegliere 0 o 1\n");
            }

        } while(scelta != 0 && scelta != 1);
        
    } while(scelta == 1 && *numProdottiPresenti != dimensioneMassima);

    return true;
}

void stampaListaProdottiCostosiInEsaurimento(Prodotto *prodotti, int numProdottiPresenti) {
    for(int i = 0; i < numProdottiPresenti; i++) {
        if(prodotti[i].quantita < 10 && prodotti[i].prezzo > 12) {
            printf("%d x %s - prezzo: %.2f Euro\n", prodotti[i].quantita, prodotti[i].descrizione, prodotti[i].prezzo);
        }
    }
}
 
int main(){
    int numProdottiDaLeggere;

    do {
        printf("Inserire prodotti da leggere da file:\n");
        scanf("%d", &numProdottiDaLeggere);

        if(numProdottiDaLeggere > MAX_PRODOTTI_LETTI) {
            printf("Errore: il numero di prodotti deve essere minore o uguale a 50! \n");
        }

        else if(numProdottiDaLeggere <= 0) {
            printf("Errore: il numero di prodotti da leggere deve essere almeno 1!\n");
        }
    }while(numProdottiDaLeggere > MAX_PRODOTTI_LETTI || numProdottiDaLeggere <= 0);
    
    int dimensioneMassima = numProdottiDaLeggere + 10;

    Prodotto* prodotti = (Prodotto*) malloc((dimensioneMassima) * sizeof(Prodotto));

    if(prodotti == NULL) {
        perror("Errore allocazione memoria!\n");
        return -1;
    }

    int numProdottiLetti = inizializzaInventario(prodotti, numProdottiDaLeggere, "prodotti.txt");

    if(numProdottiLetti == -1) {
        return -1;
    }

    printf("Sono stati importati dal file %d prodotti!\n", numProdottiLetti);

    int scelta;

    do {    
        printf("===========================================\n");
        printf("| Benvenut* nel tuo menù per la gestione inventario!  |\n");
        printf("===========================================\n");
        printf("Scegli un'operazione tra le seguenti:\n");
        printf(" [1] Aggiungi un nuovo prodotto\n");
        printf(" [2] Stampa prodotti costosi in esaurimento\n");
        printf(" [0] Uscire dal programma\n");
        printf("=========================================\n");
        printf("Inserisci la tua scelta: ");

        scanf("%d", &scelta);
        switch(scelta) {
            case 1: 
                if(aggiungiProdotto(prodotti, &numProdottiLetti, dimensioneMassima)) {
                    printf("Inserimento avvenuto con successo!\n");
                }
                else {
                    printf("Errore: capacità massima raggiunta!\n");
                }
                break;

            case 2:
                stampaListaProdottiCostosiInEsaurimento(prodotti, numProdottiLetti);
                break;

            case 0:
                printf("Uscita in corso...\n");
                break;

            default:
                printf("Scelta non corretta!\n");
                break;
        }
    } while(scelta != 0);
    
    free(prodotti);

    return 0;
}