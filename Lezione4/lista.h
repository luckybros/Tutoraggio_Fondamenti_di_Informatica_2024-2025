/*Esercizio: funzioni gestione lista 
Creare un programma che preveda l’implementazione di una linked list e le 
relative funzioni per: 
-Creare un nuovo nodo
-Aggiungere un valore in coda alla lista 
-Visualizzare la lista 
-Cancellare un valore della lista 
-Deallocare la lista 
-Si scriva una funzione che riceve come parametro la testa della lista e un 
intero M. Quindi, restituisce la somma dei soli valori della lista che sono 
multipli di M. Se la lista è vuota, la funzione restituisce il valore -1. */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define VUOTA -1

#ifndef LISTA_H
#define LISTA_H

typedef struct nodo {
    int valore;
    struct nodo* prossimo;
} Nodo;

Nodo* creaNodo(int nuovoValore);
void aggiungiValoreInCoda(Nodo** testa, int valoreDaAggiungere);
int visualizzaLista(Nodo* testa);
bool cancellaValore(Nodo** testa, int valoreDaCancellare);
void deallocaLista(Nodo** testa);
int calcolaSommaMultipli(Nodo* testa, int M);

#endif