#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DESCRIZIONE 101

struct prodotto {
    int id;
    float prezzo;
    int quantita;
    char descrizione[MAX_DESCRIZIONE];
};
typedef struct prodotto Prodotto;

int inizializzaInventario(Prodotto *prodotti, int numeroProdottiDaLeggere, const char *nomeFile) {
    FILE* file = fopen(nomeFile, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        return -1;
    }
    int i = 0;
    while (i < numeroProdottiDaLeggere && fscanf(file, "%d %f %d %[^
]", &prodotti[i].id, &prodotti[i].prezzo, &prodotti[i].quantita, prodotti[i].descrizione) == 4) {
        i++;
    }
    fclose(file);
    return i;
}

void aggiungiProdotto(Prodotto *prodotti, int *numeroProdotti, int dimensioneMassima) {
    if (*numeroProdotti >= dimensioneMassima) {
        printf("Inventario pieno. Impossibile aggiungere altri prodotti.\n");
        return;
    }

    Prodotto nuovoProdotto;
    printf("Inserisci l'identificativo del prodotto: ");
    scanf("%d", &nuovoProdotto.id);
    printf("Inserisci il prezzo unitario del prodotto: ");
    scanf("%f", &nuovoProdotto.prezzo);
    printf("Inserisci la quantita' residua del prodotto: ");
    scanf("%d", &nuovoProdotto.quantita);
    printf("Inserisci la descrizione del prodotto: ");
    getchar(); // Per consumare il newline rimasto nel buffer
    fgets(nuovoProdotto.descrizione, MAX_DESCRIZIONE, stdin);
    nuovoProdotto.descrizione[strcspn(nuovoProdotto.descrizione, "\n")] = '\0'; // Rimuove il newline

    prodotti[*numeroProdotti] = nuovoProdotto;
    (*numeroProdotti)++;
    printf("Prodotto aggiunto con successo.\n");
}

void stampaListaProdottiInEsaurimento(Prodotto *prodotti, int numeroProdotti) {
    printf("Prodotti costosi in esaurimento:\n");
    for (int i = 0; i < numeroProdotti; i++) {
        if (prodotti[i].quantita < 10 && prodotti[i].prezzo > 12.0) {
            printf("%d x %s - prezzo: %.2f Euro\n", prodotti[i].quantita, prodotti[i].descrizione, prodotti[i].prezzo);
        }
    }
}

int main() {
    int numeroProdottiDaLeggere;
    printf("Inserisci il numero di prodotti da leggere da file (max 50): ");
    scanf("%d", &numeroProdottiDaLeggere);
    if (numeroProdottiDaLeggere > 50) {
        printf("Numero di prodotti da leggere non valido.\n");
        return 1;
    }

    int dimensioneMassima = numeroProdottiDaLeggere + 10;
    Prodotto *inventario = (Prodotto *)malloc(dimensioneMassima * sizeof(Prodotto));
    if (!inventario) {
        perror("Errore nell'allocazione della memoria");
        return 1;
    }

    int prodottiLetti = inizializzaInventario(inventario, numeroProdottiDaLeggere, "inventario2024.txt");
    if (prodottiLetti == -1) {
        free(inventario);
        return 1;
    }

    printf("Numero di prodotti importati da file: %d\n", prodottiLetti);

    int numeroProdotti = prodottiLetti;
    for (int i = 0; i < 10; i++) {
        printf("Vuoi aggiungere un prodotto? (1 per si, 0 per no): ");
        int scelta;
        scanf("%d", &scelta);
        if (scelta == 1) {
            aggiungiProdotto(inventario, &numeroProdotti, dimensioneMassima);
        } else {
            break;
        }
    }

    stampaListaProdottiInEsaurimento(inventario, numeroProdotti);

    free(inventario);
    return 0;
}
