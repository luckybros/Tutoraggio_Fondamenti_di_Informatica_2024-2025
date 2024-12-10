/*Definire una struttura di nome punto con i campi x e y di tipo double. 
Scrivere una funzione distanza che dati due parametri di tipo punto restituisce 
la distanza Euclidea tra i due punti. Scrivere poi una funzione lunghezzaComplessiva
che riceve come parametro un array di punti che rappresentano una poligonale e calcola 
la lunghezza complessiva della poligonale.
Scrivere un programma che fa inserire all’utente una sequenza di punti (la lunghezza 
della sequenza è scelta dall’utente) e stampi la lunghezza complessiva della poligonale 
rappresentata dai punti inseriti.*/
#define MAX_PUNTI 10

#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Punto;

double calcoloDistanza(Punto A, Punto B);
double calcoloLunghezza(Punto punti[], int n);
void inserimento(Punto punti[], int n);

int main() {

    int numeroPunti;
    Punto punti[MAX_PUNTI];

    do {
        printf("Inserisci numero punti: ");
        scanf("%d", &numeroPunti);

        if(numeroPunti < 3 || numeroPunti > MAX_PUNTI) {
            printf("Errore! Il punto deve essere compreso tra 2 e %d\n", MAX_PUNTI);
        }
    } while(numeroPunti < 3 || numeroPunti > MAX_PUNTI);

    inserimento(punti, numeroPunti);

    double lunghezza = calcoloLunghezza(punti, numeroPunti);

    printf("La lunghezza del poligono è %.2lf", lunghezza);

}

double calcoloDistanza(Punto A, Punto B) {
    double distanza = sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2));
    return distanza;
}

double calcoloLunghezza(Punto punti[], int n) {
    double lunghezza = 0;

    for(int i = 0; i < n - 1; i++) {
        lunghezza += calcoloDistanza(punti[i], punti[i+1]); 
    }

    lunghezza += calcoloDistanza(punti[0], punti[n-1]);

    return lunghezza;
}

void inserimento(Punto punti[], int n) {
    for(int i = 0; i < n; i++) {
        printf("Inserisci coordinate del %d - esimo punto (x, y)\n", i+1);
        scanf("%lf %lf", &punti[i].x, &punti[i].y);
    }
}