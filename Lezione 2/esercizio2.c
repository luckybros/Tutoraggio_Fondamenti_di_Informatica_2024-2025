/*Definire una struct casa per memorizzare i dati delle case da parte di un’agenzia 
immobiliare, ogni casa è caratterizzata da un proprietario, un numero intero 
di metri quadri e da un costo energetico (per esempio 100 Joule/metro quadro).
Definire poi una variabile struct quartiere che memorizzi le case e la loro quantità.
Scrivere una funzione che, dato il quartiere, restituisca una variabile di 
tipo casa e stampi il nome del proprietario della casa a minor costo complessivo.
Provate a svolgere l’esercizio allocando la struttura in memoria heap.
Per semplicità potete omettere la gestione della struttura quartiere e gestire 
semplicemente una lista di case
*/
#define MAX_NOME 51

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char proprietario[MAX_NOME];
    int superficie;
    float costoEnergetico;
} Casa;

Casa calcoloCasaMinorCosto(Casa Case[], int numeroCase);
float calcoloCostoComplessivo(Casa casa);
void inserimentoCase(Casa Case[], int numeroCase)

int main() {
    int numeroCase;

    scanf("%d", &numeroCase);

    Casa* Case = (Casa*)malloc(numeroCase*sizeof(Casa));

    inserimentoCase(Case, numeroCase);

    Casa casaMinima = calcoloCasaMinorCosto(Case, numeroCase);

    printf("Il proprietario con casa a costo complessivo minore è :%s", casaMinima.proprietario);
}