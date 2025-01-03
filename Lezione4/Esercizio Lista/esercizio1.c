/*Esercizio: funzioni gestione lista 
Creare un programma che preveda l’implementazione di una linked list e le 
relative funzioni per: 
Aggiungere un valore in coda alla lista 
Visualizzare la lista 
Cancellare un valore della lista 
Deallocare la lista */

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>

Funzioni inserimento_scelta()
{
    Funzioni scelta_utente;
    printf("0.Esci 1.Aggiungi valore \n 2.Visualizza Lista 3.Cancella valore \n 4.Somma multipli \n");
    scanf("%d", &scelta_utente);
    return scelta_utente;
}

int inserimento_valori(const char cosa_inserire[])
{
    int valore_utente=0;
    printf("Inserisci il %s \n",cosa_inserire);
    scanf("%d",&valore_utente);
    return valore_utente;
}

void menu(Nodo **lista)
{
    bool ripeti=true;

    while (ripeti)
    {
        switch(inserimento_scelta())
        {
            case esci:
                ripeti=false;
                break;
            case aggiungi_valore_in_coda:
                aggiungiValoreInCoda(lista,inserimento_valori("valore"));  
                break;
            case visualizza_lista:
                visualizzaLista((*lista));
                break;
            case cancella_valore:
                if(cancellaValore(lista,inserimento_valori("valore da eliminare"))==true)
                {
                    printf("Il valore e' stato eliminato \n");
                }
                else
                {
                    printf("Valore non presente \n");
                }
                break;  
            case somma_multipli:
            {
                int somma_multipli=0;
                int Multiplo=inserimento_valori("multiplo");
                somma_multipli=calcolaSommaMultipli((*lista),Multiplo);   
                printf("La somma dei multipli di %d e' %d \n", Multiplo, somma_multipli); 
            }
            break;

            default:
                printf("Riprova \n");
                
        }
    }
    
}


int main()
{
    Nodo *lista=NULL;
    menu(&lista);
    deallocaLista(&lista);
    return 0;
}
