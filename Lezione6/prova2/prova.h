/*Si vuole implementare un software per la gestione di una libreria.
Ogni libro è caratterizzato dall’anno di pubblicazione (valore intero), dal titolo (stringa al più di 30
caratteri che può contenere anche degli spazi), dal numero di pagine (valore intero) e dal prezzo in
euro del libro (valore intero).
Requisiti obbligatori di progettazione del software.
• Il programma deve essere strutturato utilizzando i prototipi di funzione.
• Lo studente DEVE utilizzare l’allocazione dinamica per allocare l’array di libri.
• Lo studente può scegliere il tipo di accesso agli elementi degli array. Utilizzo esplicito dei
puntatori oppure utilizzo dell'operatore [].
N.B. L'uso esplicito di puntatori è considerato come valore aggiuntivo all'atto della
correzione del compito.
correzione del compito.
Il programma deve eseguire preliminarmente in sequenza le operazioni indicate al punto 1.
I successivi due punti (punti 2 e 3) sono indipendenti e possono essere eseguiti senza alcun ordine
temporale prestabilito.
1. Lettura dei libri.
tramite tastiera.
Il programma deve caricare in un array le informazioni relative ai libri inserite dall’utente
2. Stampa a video dei libri.
Il programma mostra a video le informazioni relative ai libri presenti nell’array.
Il programma deve stampare le informazioni in maniera tabellare come nell’esempio di
seguito riportato.
3. Elimina libri in base al prezzo.
Il programma deve permette all’utente di eliminare tutti i libri il cui prezzo è superiore ad un
certo valore soglia. Pertanto, il programma chiede all’utente il prezzo soglia, ed elimina dal
vettore tutti i libri il cui prezzo sia superiore a tale valore.
Esempio: Supponendo che l’utente inserisca 25 come valore soglia sul prezzo, il vettore
risultante sarà il seguente*/

#ifndef PROVA_H
#define PROVA_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TITOLO 31

struct libro {
    int annoPubblicazione;
    char titolo[MAX_TITOLO];
    int numPagine;
    int prezzo;
};

typedef struct libro Libro;

void letturaLibri(Libro* libri, int numLibriDaInserire);
void stampaLibri(Libro* libri, int numLibri);
int eliminazionePrezzo(Libro* libri, int* numLibri, int prezzo);

#endif