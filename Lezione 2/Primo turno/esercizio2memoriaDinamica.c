#include <stdio.h>
#include <math.h>

int calcoloSprecoEnergetico(Casa casa);
Casa casaConMinoreSprecoEnergetico(Casa* caseImmobili, int numeroCase);
void inserimentoCase(Casa* caseImmobili, int numeroCase);

typedef struct {
    char proprietario[100];
    int metriQuadri;
    double costoEnergetico; 
} Casa;

int main() {
    int numeroCase;

    printf("Inserisci il numero delle case nel quartiere:\n");
    scanf("%d", &numeroCase);

    Casa* caseImmobili = (Casa*)malloc(numeroCase * sizeof(Casa));

    inserimentoCase(caseImmobili, numeroCase);

    Casa casaMinoreSpreco = casaConMinoreSprecoEnergetico(caseImmobili, numeroCase);
    
    printf("La casa con il minor spreco energetico è di %s con un spreco di %.2f Joule.\n",
           casaMinoreSpreco.proprietario, calcoloSprecoEnergetico(casaMinoreSpreco));

    free(caseImmobili);

    return 0;
}

int calcoloSprecoEnergetico(Casa casa) {
    return casa.metriQuadri * casa.costoEnergetico;
}

Casa casaConMinoreSprecoEnergetico(Casa* caseImmobili, int numeroCase) {
    Casa casaConMinoreSpreco = caseImmobili[0]; 

    for (int i = 1; i < numeroCase; i++) {
        if (calcoloSprecoEnergetico(caseImmobili[i]) < calcoloSprecoEnergetico(casaConMinoreSpreco)) {
            casaConMinoreSpreco = caseImmobili[i];
        }
    }

    return casaConMinoreSpreco;
}

void inserimentoCase(Casa* caseImmobili, int numeroCase) {
    for (int i = 0; i < numeroCase; i++) {
        printf("Inserisci i dati della casa %d:\n", i + 1);
        printf("Proprietario: ");
        scanf("%s", caseImmobili[i].proprietario); 
        printf("Metri quadri: ");
        scanf("%d", &caseImmobili[i].metriQuadri); 
        printf("Costo energetico (Joule/metro quadro): ");
        scanf("%lf", &caseImmobili[i].costoEnergetico);
    }
}
