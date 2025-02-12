#include <stdio.h>
#include <stdlib.h>

// Struttura per il nodo della lista
typedef struct Nodo {
    int valore;
    struct Nodo* prossimo;
} Nodo;

// typedef Nodo* lista;

// Funzione per creare un nuovo nodo
Nodo* creaNodo(int valore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuovoNodo == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(1);
    }
    nuovoNodo->valore = valore;
    nuovoNodo->prossimo = NULL;
    return nuovoNodo;
}

// Funzione per aggiungere un valore in coda alla lista
void aggiungiInCoda(Nodo** testa, int valore) {
    Nodo* nuovoNodo = creaNodo(valore);
    if (*testa == NULL) {
        *testa = nuovoNodo;
    } else {
        Nodo* temp = *testa;
        while (temp->prossimo != NULL) {
            temp = temp->prossimo;
        }
        temp->prossimo = nuovoNodo;
    }
}

// Funzione per visualizzare la lista
void visualizzaLista(Nodo* testa) {
    if (testa == NULL) {
        printf("La lista è vuota.\n");
        return;
    }
    Nodo* temp = testa;
    printf("Lista: ");
    while (temp != NULL) {
        printf("%d ", temp->valore);
        temp = temp->prossimo;
    }
    printf("\n");
}

// Funzione per cancellare un valore dalla lista
void cancellaValore(Nodo** testa, int valore) {
    if (*testa == NULL) {
        printf("La lista è vuota.\n");
        return;
    }
    Nodo* temp = *testa;
    Nodo* precedente = NULL;

    // Cerca il nodo con il valore specificato
    while (temp != NULL && temp->valore != valore) {
        precedente = temp;
        temp = temp->prossimo;
    }

    if (temp == NULL) {
        printf("Valore %d non trovato nella lista.\n", valore);
        return;
    }

    if (precedente == NULL) {
        *testa = temp->prossimo; // Il valore si trova nel primo nodo
    } else {
        precedente->prossimo = temp->prossimo;
    }

    free(temp);
    printf("Valore %d cancellato.\n", valore);
}

// Funzione per deallocare l'intera lista
void deallocaLista(Nodo** testa) {
    Nodo* temp;
    while (*testa != NULL) {
        temp = *testa;
        *testa = (*testa)->prossimo;
        free(temp);
    }
    printf("Lista deallocata.\n");
}

// Funzione per calcolare la somma dei multipli di M
int sommaMultipli(Nodo* testa, int M) {
    if (testa == NULL) {
        return -1;
    }
    int somma = 0;
    Nodo* temp = testa;
    while (temp != NULL) {
        if (temp->valore % M == 0) {
            somma += temp->valore;
        }
        temp = temp->prossimo;
    }
    return somma;
}

int main() {
    Nodo* lista = NULL;
    int scelta, valore, M;

    do {
        printf("\nMenu:\n");
        printf("1. Aggiungi un valore in coda\n");
        printf("2. Visualizza la lista\n");
        printf("3. Cancella un valore dalla lista\n");
        printf("4. Dealloca la lista\n");
        printf("5. Calcola somma dei multipli di M\n");
        printf("6. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("Inserisci il valore da aggiungere: ");
                scanf("%d", &valore);
                aggiungiInCoda(&lista, valore);
                break;
            case 2:
                visualizzaLista(lista);
                break;
            case 3:
                printf("Inserisci il valore da cancellare: ");
                scanf("%d", &valore);
                cancellaValore(&lista, valore);
                break;
            case 4:
                deallocaLista(&lista);
                break;
            case 5:
                printf("Inserisci il valore di M: ");
                scanf("%d", &M);
                valore = sommaMultipli(lista, M);
                if (valore == -1) {
                    printf("La lista è vuota.\n");
                } else {
                    printf("La somma dei multipli di %d è: %d\n", M, valore);
                }
                break;
            case 6:
                deallocaLista(&lista);
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    } while (scelta != 6);

    return 0;
}
