/*Esercizio 5 – Main (main.c)
Il candidato realizzi un programma main.c che provveda a leggere i nomi degli studenti nel file
“listaStud.txt” e a memorizzarli tramite la funzione di cui al punto 1. Quindi il programma allochi spazio
sufficiente per memorizzare un array di strutture dati riepilogoEsame (inizialmente vuoto), e tramite la
funzione di cui al punto 4 legga, per ogni studente memorizzato nel file “listaStud.txt”, gli esami ed i voti
ricevuti, ed aggiorni l’array di riepilogo. Infine il main stampi a video l’elenco degli esami con codice
dell’esame, numero di studenti che l’hanno sostenuto e medie.
Il candidato abbia cura di deallocare (al termine del programma) tutte le strutture allocate dinamicamente.*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifndef STUDENTI_H
#define STUDENTI_H

#define MAX_NOME 64
#define NUMERO_ESAMI 29

typedef struct {
    char nome[MAX_NOME];
    char cognome[MAX_NOME];
    int matricola;
} Studente;

typedef struct {
    char codice[MAX_NOME];
    int numStudenti;
    int somma;
} RiepilogoEsame;

Studente leggiUnoStudente(FILE* file);
Studente* leggiTuttiGliStudenti(char* nomeFile, int* dim);
void creaNomeFile(Studente studente);
int trovaPos(RiepilogoEsame* esami, int dim, char* codice);
void aggiornaEsamiSostenuti(char* nomeFile, RiepilogoEsame* esami, int* dim);

#endif