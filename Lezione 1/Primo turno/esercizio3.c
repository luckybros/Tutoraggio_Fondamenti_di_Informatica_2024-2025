// Vogliamo coprire le tracce di un ricercato: dato un avviso
// di cattura (una stringa) vogliamo andare a sostituire il nome 
// con dei trattini bassi (Esempio: )
// Assumiamo che il nome del ricercato sia l'unica parola
// che comincia con una maiuscola
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Per la funzione isupper()

int main() {
    char avviso[100];

    printf("Inserisci avviso di cattura: ");
    scanf("%[^\n]s", avviso);

    censura(avviso);

    printf("Avviso modificato: %s\n", avviso);
}

void censura(char avviso[]) {

    int lunghezza = strlen(avviso);

    for(int i = 0; i < lunghezza; i++) {
        if(avviso[i] >= 'A' && avviso[i] <= 'Z') {
            int j = i;
            // Ha trovato l'iniziale del nome: continuare finché
            // non si trova uno spazio nuovo o finche non finisce
            while(j < lunghezza && avviso[j] != ' ') {
                avviso[j++] = '_';
            }
            break;

        }
    }

}