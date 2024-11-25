/* Vogliamo coprire le tracce di un ricercato: dato un avviso di 
cattura (una stringa) vogliamo andare a sostituire il nome con 
dei trattini bassi (Esempio: Fate attenzione a Pippo -> fate 
attenzione a _____). Assumiamo che il nome del ricercato sia 
l'unica parola che comincia con una maiuscola.
*/

// fate attenzione a Pippo
// 0123456789

#include <stdio.h>
#include <string.h>

void copriNome(char avviso[]) {
    int lunghezza = strlen(avviso);

    int inizioParola = -1;

    for(int i = 0; i < lunghezza; i++) {
        if((avviso[i] >= 'A' && avviso[i] <= 'Z') && (i == 0 || avviso[i - 1] == ' ')) {

        }
    }
}



int main() {
    char avviso[256];

    printf("Inserisci avviso: ");
    scanf("%[^\n]s", avviso);



}