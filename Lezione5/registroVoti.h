/*
Definire una matrice dove in ogni cella è salvato il nome dello studente, della materia, e del voto preso in quella materia.
Realizzare le seguenti funzioni:
Una funzione che permetta di aggiungere un nuovo studente, e aggiorni i suoi voti
Una funzione che permetta di aggiungere una nuova materia, e aggiornare i voti degli studenti già presenti.
Un metodo che, per ogni materia, restituisca il nome dello studente migliore con il voto più alto.*/

#ifndef LISTA_H
#define LISTA_H

#include <string.h>

#define MAX_NOME 51
#define MAX_RIGHE 10
#define MAX_COLONNE 10

typedef struct {
    char nome[MAX_NOME];
    char materia[MAX_NOME];
    int voto;
} Cella;

void aggiungiStudente(Cella matrice[][MAX_COLONNE], int* numStudenti, int numMaterie, char nomeStudente[]);
void aggiungiMateria(Cella matrice[][MAX_COLONNE], int numStudenti, int* numMaterie);
Cella studenteVotoPiuAlto(Cella matrice[][MAX_COLONNE], int numStudenti, int indiceMateria);

#endif