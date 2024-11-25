/* Vogliamo coprire le tracce di un ricercato: dato un avviso di 
cattura (una stringa) vogliamo andare a sostituire il nome con 
dei trattini bassi (Esempio: fate attenzione a Pippo\0 -> fate 
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
            //inizioParola = i;
            while(avviso[i] != ' ' && avviso[i] != '\0') {
                avviso[i] = '_';
                i++;
            }
            break;
        }
    }

    /*if(inizioParola == -1) {
        printf("Nessun nome da censurare");
        return;
    }*/
}

int main() {
    char avviso[256];

    printf("Inserisci avviso: ");
    scanf("%[^\n]s", avviso);

    copriNome(avviso);

    printf("%s", avviso);

}