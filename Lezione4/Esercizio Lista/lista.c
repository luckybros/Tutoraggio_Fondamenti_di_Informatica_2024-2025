#include "lista.h"
#include <stdio.h>

Nodo* creaNodo(int nuovoValore) {
    Nodo *nuovonodo=malloc(sizeof(Nodo));
    if(nuovonodo == NULL) {
        perror("Errore allocazione memoria!\n");
        return NULL;
    }
    nuovonodo->valore=nuovoValore;
    nuovonodo->prossimo=NULL;
    return nuovonodo;
}

bool aggiungiValoreInCoda(Nodo **testa, int nuovoValore)
{
    Nodo *nuovo=creaNodo(nuovoValore);
    if(nuovo == NULL) {
        return false;
    }

    if((*testa)==NULL)
    {
        (*testa)=nuovo;
        return true;
    }
    else
    {
        Nodo *scorrimento=(*testa);

        while(scorrimento->prossimo!=NULL)
        {
            scorrimento=scorrimento->prossimo;
        }
        scorrimento->prossimo=nuovo;
        return true;
    }
}

void visualizzaLista(Nodo* testa)
{
    printf("Lista: ");
    while(testa!=NULL)
    {
        printf(" %d \b", testa->valore);
        testa=testa->prossimo;
    }
    printf("\n");
}

bool cancellaValore(Nodo** testa, int valoreDaCancellare)
{
    Nodo *nodo_precedente=NULL;
    Nodo *scorrimento_lista=(*testa);
    if((*testa)->valore==valoreDaCancellare)
    {
            (*testa)=scorrimento_lista->prossimo;
            libera(scorrimento_lista);
            return true;
    }
    while(scorrimento_lista!=NULL)
    {   
        if(scorrimento_lista->valore==valoreDaCancellare)
        {
            nodo_precedente->prossimo=scorrimento_lista->prossimo;
            libera(scorrimento_lista);
            printf("%p\n", scorrimento_lista);
            return true;
        }
        nodo_precedente=scorrimento_lista;
        scorrimento_lista=scorrimento_lista->prossimo;
    }
    return false;
}

void deallocaLista(Nodo** testa)
{   
    Nodo *temp = NULL;

    while((*testa)!=NULL)
    {
        temp=(*testa);
        (*testa)=(*testa)->prossimo;
        libera(temp);
    }    
}

int calcolaSommaMultipli(Nodo* testa, int M)
{
    int somma_multipli=0;

    while(testa!=NULL)
    {
        if(testa->valore%M==0)
        {
            somma_multipli+=testa->valore;
        }
        testa=testa->prossimo;
    }
    return somma_multipli;
}

void libera(Nodo* punt)
{
    free(punt);
    punt=NULL;
}
