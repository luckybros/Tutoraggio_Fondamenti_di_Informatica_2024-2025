// Date due stringhe, verifica che una sia sottostringa di un'altra
#include <stdio.h>
#include <string.h>

int sottostringa(char stringa1[], char stringa2[]);

int main() {
    char stringa1[100], stringa2[100];

    // Poiché scanf legge solo fino al primo spazio, 
    // la direttiva ^/n indica di prendere l'input
    // fino a che non si incontra il carattere
    // di newline (che va a capo)
    printf("Inserisci prima stringa: ");
    scanf("%[^\n]s", stringa1);

    printf("Inserisci seconda stringa: ");
    scanf("%[^\n]s", stringa2);

    if(sottostringa(stringa1, stringa2) == 1) {
        printf("La seconda stringa è sottostringa della prima!");
    }
    else {
        printf("La seconda stringa non è sottostringa della prima...");
    }
}

int sottostringa(char stringa1[], char stringa2[]) {
    
    int lunghezza1 = strlen(stringa1);
    int lunghezza2 = strlen(stringa2);

    if (lunghezza2 > lunghezza1) {
        return 0;
    }

    for(int i = 0; i <= lunghezza1 - lunghezza2; i++) {
        int j = 0;
        
        if(stringa1[i] == stringa2[j]) {
            // Il primo carattere è trovato: continuiamo a scorrere
            // per verificare che sia una sottostringa
            j++;

            while(stringa2[j] == stringa1[i+j]) {
                j++;
            }

            if(j == lunghezza2) {
                return 1;
            }
        }
    }

    return 0;
}