/*  
*  STATO: CONSEGNA / WIP
*  NOME:
*  COGNOME:
*  MATRICOLA:
*/
 
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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DESCRIZIONE 101

struct prodotto {
   int id;
   float prezzo;
   int quantita;
   char descrizione[MAX_DESCRIZIONE];
};

typedef struct prodotto Prodotto;
 
int inizializzaInventario(Prodotto* prodotti, int numeroProdottiDaLeggere, const char *nomeFile) {
    /*
     * Non modificare l'implementazione di questa funzione.
     * Bisogna de-commentarla ed invocarla nel programma principale per inizializzare la struttura dati.
    */
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
    return i; 
    // Restituisce il numero di prodotti effettivamente letti
    
}
 
/* altre funzioni da implementare:
- aggiungiProdotto
- stampaListaProdottiCostosiInEsaurimento
- ...
*/

void aggiungiProdotto(Prodotto* prodotti, int* numeroProdottiPresenti, int numeroProdottiMassimo) {
    // da implementare
    Prodotto nuovoProdotto;
    printf("Inserisci ID del prodotto:\n");
    scanf("%d", &nuovoProdotto.id);
    printf("Inserisci prezzo del prodotto:\n");
    scanf("%f", &nuovoProdotto.prezzo);
    printf("Inserisci prezzo del prodotto:\n");
    scanf("%d", &nuovoProdotto.quantita);
    printf("Inserisci prezzo del prodotto:\n");
    scanf("%s", nuovoProdotto.descrizione);

    prodotti[*numeroProdottiPresenti] = nuovoProdotto;

    (*numeroProdottiPresenti)++;
}

void stampaListaProdottiCostosiInEsaurimento(Prodotto* prodotti, int numeroProdottiPresenti) {
    // da implementare
}
 
int main(){
    int numeroProdotti;
    printf("Inserisci il numero dei prodotti: \n");
    scanf("%d", &numeroProdotti);

    Prodotto* inventario = malloc((numeroProdotti + 10) * sizeof(Prodotto));
    
    const char* nomeFile = "inventario2024.txt";

    int numeroProdottiTrovati = inizializzaInventario(inventario, numeroProdotti, nomeFile);

    aggiungiProdotto(inventario, &numeroProdottiTrovati, numeroProdotti + 10);

    return 0;
}