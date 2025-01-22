/*Esercizio 2 – Generazione del nome del file contente i voti (studenti.h/studenti.c)
Il candidato realizzi una funzione:
char * creaNomeFile(studente s);
che, ricevuto in ingresso una struttura dati studente, generi il nome del file corrispondente che conterrà gli
esami ed i voti di quel certo studente. Si ricorda che per ogni studente, il file corrispondente si chiamerà
“NomeCognome.txt”, dove a Nome ed a Cognome si dovranno sostituire rispettivamente il nome ed il
cognome dello studente.
Contestualmente, il candidato scriva nel main opportune istruzioni per invocare le funzioni definite al fine di
verificarne la corretta implementazione. Una volta verificato il corretto funzionamento delle funzioni, il
candidato non cancelli il codice nel main ma si limiti a commentarlo*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifndef STUDENTI_H
#define STUDENTI_H

#define MAX_NOME 64

typedef struct {
    char nome[MAX_NOME];
    char cognome[MAX_NOME];
    int matricola;
} Studente;

Studente leggiUnoStudente(FILE* file);
Studente* leggiTuttiGliStudenti(char* nomeFile, int* dim);
char* creaNomeFile(Studente studente);

#endif