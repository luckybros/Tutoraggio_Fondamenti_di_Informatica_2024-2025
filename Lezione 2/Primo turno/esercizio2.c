#include <stdio.h>
#include <math.h>

#define MAX_CASE 10

int calcoloSprecoEnergetico(Casa casa);
Casa casaConMinoreSprecoEnergetico(Quartiere quartiere);
void inserimentoCase(Quartiere quartiere);

typedef struct {
    char proprietario[100];
    int metriQuadri;
    double costoEnergetico; 
} Casa;

typedef struct {
    Casa caseImmobili[MAX_CASE];  
    int numeroCase;
} Quartiere;

int main() {
    Quartiere quartiere;
    quartiere.numeroCase = 0;

    do {
        printf("Inserisci il numero delle case nel quartiere:\n");
        scanf("%d", &quartiere.numeroCase);

        if(quartiere.numeroCase > MAX_CASE) {
            printf("Errore: non puoi inserire più di %d case!\n", MAX_CASE);
        }

    } while(quartiere.numeroCase > MAX_CASE);

    inserimentoCase(quartiere);

    Casa casaMinoreSpreco = casaConMinoreSprecoEnergetico(quartiere);
    
    printf("La casa con il minor spreco energetico è di %s con un spreco di %d Joule.\n",
           casaMinoreSpreco.proprietario, calcoloSprecoEnergetico(casaMinoreSpreco));
}

int calcoloSprecoEnergetico(Casa casa) {
    return casa.metriQuadri * casa.costoEnergetico;
}

Casa casaConMinoreSprecoEnergetico(Quartiere quartiere) {
    Casa casaConMinoreSpreco = quartiere.caseImmobili[0]; 

    for (int i = 1; i < quartiere.numeroCase; i++) {
        if (calcoloSprecoEnergetico(quartiere.caseImmobili[i]) < calcoloSprecoEnergetico(casaConMinoreSpreco)) {
            casaConMinoreSpreco = quartiere.caseImmobili[i];
        }
    }

    return casaConMinoreSpreco;
}

void inserimentoCase(Quartiere quartiere) {
    for (int i = 0; i < quartiere.numeroCase; i++) {
        printf("Inserisci i dati della casa %d:\n", i + 1);
        printf("Proprietario: ");
        scanf("%s", quartiere.caseImmobili[i].proprietario);
        printf("Metri quadri: ");
        scanf("%d", &quartiere.caseImmobili[i].metriQuadri);
        printf("Costo energetico (Joule/metro quadro): ");
        scanf("%lf", &quartiere.caseImmobili[i].costoEnergetico);
    }
}
