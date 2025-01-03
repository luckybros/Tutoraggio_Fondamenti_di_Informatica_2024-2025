#include "lista.h"

Nodo* creaNodo(int nuovoValore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));

    if(nuovoNodo == NULL) {
        perror("Errore allocazione memoria!\n");
        return NULL;
    }

    nuovoNodo->valore = nuovoValore;
    nuovoNodo->prossimo = NULL;

    return nuovoNodo;
}

void aggiungiValoreInCoda(Nodo** testa, int valoreDaAggiungere) {
    Nodo* nuovoNodo = creaNodo(valoreDaAggiungere);
    // Se la lista è vuota
    if(*testa == NULL) {
        *testa = nuovoNodo;
    }
    else {
        // Scorriamo la lista
        Nodo* corrente = *testa;

        while(corrente->prossimo !=NULL) {
            corrente = corrente->prossimo;
        }

        corrente->prossimo = nuovoNodo;
    }
}

int visualizzaLista(Nodo* testa) {
    if(testa == NULL) {
        return VUOTA;
    }
    
    printf("Lista: ");
    while(testa != NULL) {
        printf("%d ->", testa->valore);
        testa = testa->prossimo;
    }

    printf("\n");
}

bool cancellaValore(Nodo** testa, int valoreDaCancellare) {
    if(*testa == NULL) {
        return false;
    }

    Nodo* corrente = *testa;
    Nodo* precedente = NULL;

    while(corrente != NULL) {
        if(corrente->valore == valoreDaCancellare) {
            // Il valore da cancellare è alla testa
            if(precedente == NULL) {
                *testa = corrente->prossimo;
                free(corrente);
                return true;
            }
            else {
                precedente->prossimo = corrente->prossimo;
                free(corrente);
                return true;
            }
        }
        precedente = corrente;
        corrente = corrente->prossimo;
    }

    return false;
}