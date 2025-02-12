/*Si realizzi un programma per la gestione di un piccolo parcheggio per auto. Il parcheggio ha 10 posti in totale. Per
ogni posto auto, fino alla chiusura della giornata lavorativa, il sistema deve consentire all’operatore di registrare gli
ingressi e le uscite delle auto e i relativi incassi. Si assuma che il parcheggio è vuoto all’esecuzione del programma.
Il programma presenta all’operatore il seguente menu:
---------------------------------------
Seleziona un’operazione da effettuare:
1-registra un nuovo ingresso
2-registra un’uscita
3-chiudi registro e visualizza report finale
-----------------------------------------------
Se si seleziona l’opzione 1, il programma verifica la disponibilità di posti auto e, se ci sono posti disponibili,
restituisce il numero della postazione in cui parcheggiare (intero compreso fra 1 e 10). Se il parcheggio è pieno, il
programma stampa un messaggio per l’operatore. NOTA: il programma assegna i posti in sequenza, dal primo
all’ultimo fino al riempimento del parcheggio ed assegna sempre il primo posto libero trovato.
Se si seleziona l’opzione 2, il programma verifica che ci siano effettivamente auto nel parcheggio (l’opzione
potrebbe essere stata selezionata erroneamente) e, in caso affermativo, richiede il numero di postazione (che era
stato rilasciato all’ingresso) e il numero di ore di sosta. Se la postazione e le ore di sosta sono stati inseriti
correttamente (la posizione è un intero compreso fra 1 e 10 e le ore di sosta sono espresse come un intero
positivo), il programma marca la postazione come libera e calcola l’incasso, stampandolo a video. L’incasso viene
calcolato come prodotto del numero di ore per la tariffa oraria di 1,50 euro. L’incasso viene poi aggiunto al totale
della giornata.
Se si seleziona l’opzione 3, il programma mostra la situazione dei posti auto (postazioni occupate e libere) e stampa
l’incasso totale della giornata.
Il menu viene riproposto finché l’opzione scelta è diversa dalla 3 (se viene scelta un’opzione non valida il
programma deve stampare un messaggio di errore e riproporre il menu).
Lo studente è libero di definire l’output del programma, purché rispetti i vincoli della specifica.*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_POSTI_AUTO 10
#define TARIFFA_ORARIA 1.50

typedef struct {
    bool libero;
    int ora_ingresso;
    int ora_uscita;
} Auto;

int registra_ingresso(Auto* lista_auto);
bool registra_uscita(Auto* lista_auto, int posizione, int ora_uscita, float* incasso);
void stampa(Auto* lista_auto, float incasso);

int main() {
    
}

int registra_ingresso(Auto* lista_auto) {
    int i = 0;

    for(i = 0; i < MAX_POSTI_AUTO; i++) {
        if(lista_auto[i].libero == true) {
            printf("Il %d posto è libero\n", i + 1);
            printf("Inserisci ora di ingresso:\n");
            scanf("%d\n", &lista_auto[i].ora_ingresso);
            lista_auto[i].libero = false;
            break;
        }
    }

    return i;
}

bool registra_uscita(Auto* lista_auto, int posizione, int ora_uscita, float* incasso) {
    if(lista_auto[posizione].libero == true) {
        return false;
    }

    // La posizione è occupata
    lista_auto[posizione].libero = true;

    *incasso += (ora_uscita - lista_auto[posizione].ora_ingresso)*(TARIFFA_ORARIA);

    return true;
}

void stampa(Auto* lista_auto, float incasso) {
    for(int i = 0; i < MAX_POSTI_AUTO; i++) {
        if(lista_auto[i].libero == false) {
            printf("La %d posizione è occupata\n", i+1);
        }
        else {
            printf("La %d posizione è libera\n", i+1);
        }
    }

    printf("L'incasso totale è %f euro\n", incasso);
}
