#include "prova.h"

void letturaLibri(Libro* libri, int numLibriDaInserire) {
    for(int i = 0; i < numLibriDaInserire; i++) {
        printf("--------------------------------\n");
        printf("Inserire anno di pubblicazione:\n");
        scanf("%d", &libri[i].annoPubblicazione);
        getchar();
        printf("Inserire titolo:\n");
        fgets(libri[i].titolo, MAX_TITOLO, stdin);
        libri[i].titolo[strcspn(libri[i].titolo, "\n")] = '\0';
        printf("Inserire numero pagine:\n");
        scanf("%d", &libri[i].numPagine);
        printf("Inserire prezzo:\n");
        scanf("%d", &libri[i].prezzo);
    }
}

void stampaLibri(Libro* libri, int numLibri) {
    printf("Anno\tTitolo\t\tNumero di pagine\tPrezzo\n");

    for(int i = 0; i < numLibri; i++) {
        printf("%d\t%s\t%d\t%d\n", libri[i].annoPubblicazione, libri[i].titolo, 
            libri[i].numPagine, libri[i].prezzo);
    }
}

int eliminazionePrezzo(Libro* libri, int* numLibri, int prezzo) {
    int conteggio = 0;

    for(int i = 0; i < *numLibri; i++) {
        if(libri[i].prezzo > prezzo) {
            (*numLibri)--;
            conteggio++;
            for(int j = i; j < *numLibri; j++) {
                libri[j] = libri[j + 1];
            }
        }
    }

    return conteggio;
}

// numLibri = 1
// [15], [15], [15]
