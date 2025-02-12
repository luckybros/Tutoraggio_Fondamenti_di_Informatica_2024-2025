/* Definire una struttura di nome punto con i campi x e y di tipo double. 
Scrivere una funzione distanza che dati due parametri di tipo punto restituisce la distanza Euclidea 
tra i due punti. Scrivere poi una funzione che riceve come parametro un array di punti (max 10)
che rappresentano un poligono e calcola la lunghezza complessiva della poligono.
Scrivere un programma che fa inserire all’utente una sequenza di punti (la lunghezza della sequenza è scelta dall’utente) e stampa la 
lunghezza complessiva della poligonale rappresentata dai punti inseriti.*/
#include <stdio.h>
#include <math.h>

#define MAX_PUNTI 10

typedef struct {
    double x;
    double y;
} Punto;

double calcoloDistanza(Punto primoPunto, Punto secondoPunto);
double calcoloLunghezzaComplessiva(Punto listaPunti[], int numeroPunti);
void inserimentoPunti(Punto listaPunti[], int numeroPunti);

int main() {
    Punto listaPunti[MAX_PUNTI];
    int numeroPunti;

    do {
        printf("Inserisci il numero di punti (max %d): \n", MAX_PUNTI);
        scanf("%d", &numeroPunti);

        if(numeroPunti < 2) {
            printf("Errore: devi inserire almeno due punti!\n");
        }
        else if(numeroPunti > MAX_PUNTI) {
            printf("Errore: non puoi inserire più di %d punti!\n", MAX_PUNTI);
        }

    } while(numeroPunti > MAX_PUNTI || numeroPunti < 2);

    inserimentoPunti(listaPunti, numeroPunti);

    printf("La lunghezza complessiva della poligonale è %.2lf\n", calcoloLunghezzaComplessiva(listaPunti, numeroPunti));

}

double calcoloDistanza(Punto primoPunto, Punto secondoPunto) {
    double distanzaSuX = primoPunto.x - secondoPunto.x;
    double distanzaSuY = primoPunto.y - secondoPunto.y;

    double distanza = sqrt(pow(distanzaSuX, 2) + pow(distanzaSuY, 2));

    return distanza;
}

double calcoloLunghezzaComplessiva(Punto listaPunti[], int numeroPunti) {
    double lunghezzaComplessiva = 0;

    for(int i = 0; i < numeroPunti; i++) {
        // Nel primo caso si trova all'ultimo punto e deve calcolare la distanza con il primo
        if(i == numeroPunti - 1) {
            lunghezzaComplessiva += calcoloDistanza(listaPunti[i], listaPunti[0]);
        }
        else { 
            lunghezzaComplessiva += calcoloDistanza(listaPunti[i], listaPunti[i+1]);
        }
    }

    return lunghezzaComplessiva;
}

void inserimentoPunti(Punto listaPunti[], int numeroPunti) {
    for (int i = 0; i < numeroPunti; i++) {
        printf("Inserisci le coordinate del punto %d (x y): ", i + 1);
        scanf("%lf %lf", &listaPunti[i].x, &listaPunti[i].y);
    }
}