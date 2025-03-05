/*
Rispettando i principi della programmazione strutturata, implementare un
programma che gestisca le letture da una stazione meteorologica.

Dichiarare una struttura lettura con i seguenti campi:
-Località (max 120 caratteri)

-Stato (enumerativo che può assumere solo i seguenti valori in base all'assenza
o presenza dei campi di temperatura ed umidità: NESSUNA, ENTRAMBE, 
SOLO_TEMPERATURA, SOLO_UMIDITA)

-Temperatura (reale compreso tra -50 e 50 (inclusi) )

-Umidità (intero compreso tra 0 e 100 (inclusi) )

Le prime letture vengono importate da un file "info_meteo.txt" e inserite
in un vettore "LettureMeteo2025" allocato in area HEAP che contiene 
al massimo 99 letture

In seguito il programma:
1) Stampa tutte le località con temperatura valida 
(se non hanno temperatura valida nel file sarà presente 999.9, un valore "placeholder")

2) Il programma aggiunge in coda al vettore "LettureMeteo2025" 4 nuove letture 
per le città di Roma, Milano, Aci Trezza e Aosta, che presentano i seguenti dati:

-Località: Roma - Temperatura: 23.2 - Umidità: 87 - Stato: ENTRAMBE
-Località: Milano - Temperatura: 28.3 - Umidità: 999 - Stato: SOLO_TEMPERATURA
-Località: Aci Trezza - Temperatura: 999.9 - Umidità: 999 - Stato: NESSUNA
-Località: Aosta - Temperatura: 999.9 - Umidità: 55 - Stato: SOLO_UMIDITA

3) Stampa le 2 città con le temperature più alte

BONUS: Se i valori di temperatura e umidità non sono validi, fa in modo che
debba inserirli l'utente (e poi ripete i punti 1 e 3)

ULTERIORI DETTAGLI IMPLEMENTATIVI:
Implementare le seguenti funzioni:
1) temperature_maggiori() stampa le due città con le temperature più alte
Parametri di INPUT: il vettore che contiene le letture meteo e relativo riempimento

2) ha_temperatura() verifica tramite controllo sui campi "stato" se la lettura
ha una temperatura valida. Se la temperatura è valida ritorna true, altrimenti false
Parametri di INPUT: una lettura meteo di cui si vuole verificare la temperatura

3) aggiungi_lettura() inserisce una nuova lettura in coda al vettore delle 
letture meteo. Se è possibile inserire il valore ed esso viene inserito con
successo ritorna true, in caso contrario ritorna false.
Parametri di INPUT: una nuova lettura meteo da aggiungere
Parametri di INPUT/OUTPUT: il vettore che contiene le letture meteo e relativo 
riempimento

*/
#define MAX_CARATTERI 121
#define MIN_TEMPERATURA -50
#define MAX_TEMPERATURA 50
#define MAX_LETTURE 99

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {NESSUNA, SOLO_TEMPERATURA, 
    SOLO_UMIDITA, ENTRAMBE} Stato;

typedef struct {
    char localita[MAX_CARATTERI];
    Stato stato;
    float temperatura;
    int umidita;
} Lettura;

int importaLetture(Lettura* lettureMeteo, const char *nomeFile) {
    FILE* infoMeteo = fopen(nomeFile,"r");
    if(!infoMeteo) //controlla se l'apertura del file è avvenuta correttamente
    {
        perror("Errore nell'apertura del file");
        return -1;
    }
    int numeroLettureDaLeggere=conta_letture_file(infoMeteo);
    ritorna_ad_inizio_file(infoMeteo);
    int i=0;
    while( i<numeroLettureDaLeggere && fscanf(infoMeteo, "%u %f %d %[^\n]", &lettureMeteo[i].stato,
                                                                            &lettureMeteo[i].temperatura,
                                                                            &lettureMeteo[i].umidita,
                                                                            lettureMeteo[i].localita) == 4)
    {
        i++;
    }
    fclose(infoMeteo);
    return i;
}

void stampaLettureValide(Lettura* lettureMeteo, int riemp);
bool aggiungiLettura(Lettura nuovaLettura, Lettura* lettureMeteo, int* riemp);
bool haTemperatura(Lettura lettura);
void temperatureMaggiori(Lettura* lettureMeteo, int riemp);

int main() {
    
}

void stampaLettureValide(Lettura* lettureMeteo, int riemp) {
    for(int i = 0; i < riemp; i++) {
        if(haTemperatura(lettureMeteo[i])) {
            printf("%d %f %d %s\n", lettureMeteo[i].stato, lettureMeteo[i].temperatura, 
                lettureMeteo[i].umidita, lettureMeteo[i].localita);
        }
    }
}

bool haTemperatura(Lettura lettura) {
    if(lettura.stato == SOLO_TEMPERATURA || lettura.stato == ENTRAMBE) {
        if(lettura.temperatura >= MIN_TEMPERATURA && lettura.temperatura <= MAX_TEMPERATURA) {
            return true;
        }
    }

    return false;
}

bool aggiungiLettura(Lettura nuovaLettura, Lettura* lettureMeteo, int* riemp) {
    if(*riemp == MAX_LETTURE) {
        return false;
    }

    lettureMeteo[*riemp] = nuovaLettura;
    (*riemp)++;
    return true;
}

void temperatureMaggiori(Lettura* lettureMeteo, int riemp) {
    int max_1 = -50;
    int max_2 = -50;

    int posizione_max_1 = 0;

    for(int i = 0; i < riemp; i++) {
        if(lettureMeteo[i].temperatura > max_1) {
            max_1 = lettureMeteo[i].temperatura;
            posizione_max_1 = i;
        }
    }

    printf("1 - %s: %f\n", lettureMeteo[posizione_max_1].localita, max_1);


}

// [20, 10, 40, 30]
// 