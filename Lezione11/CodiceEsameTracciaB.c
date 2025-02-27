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

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LETTURE 99
#define ERRORE_LETTURA_FILE -1
#define NESSUN_ERRORE 0
#define MAX_LUNGHEZZA_LOCALITA 120
#define MAX_UMIDITA 100
#define MAX_TEMPERATURA 50
#define MIN_UMIDITA 0
#define MIN_TEMPERATURA -50
#define NUMERO_NUOVE_LETTURE 4
#define TEMPERATURA_MASSIMA_ASSENTE -1
#define SECONDA_TEMPERATURA_MASSIMA_ASSENTE -1

#define TEMPERATURA_ROMA 23.2
#define UMIDITA_ROMA 87
#define TEMPERATURA_MILANO 28.3
#define UMIDITA_MILANO 999
#define TEMPERATURA_ACI_TREZZA 999.9
#define UMIDITA_ACI_TREZZA 999
#define TEMPERATURA_AOSTA 999.9
#define UMIDITA_AOSTA 55

typedef enum eStato{
    NESSUNA=0, SOLO_TEMPERATURA, SOLO_UMIDITA, ENTRAMBE
} Stato;

typedef struct sLettura{
    char localita[MAX_LUNGHEZZA_LOCALITA];
    Stato stato;
    float temperatura;
    int umidita;
} Lettura;

/* 
    NON RICHIESTA DALLA TRACCIA
    Legge il numero di righe presenti in un file e restituisce tale
    numero come parametro di output
    -PARAMETRI DI INPUT/OUTPUT: puntatore a FILE infoMeteo
    -OUTPUT (valore di ritorno): il numero di righe lette dal file
    
    -SIDE EFFECTS: Interagisce con file
    
    Dato che scorre tra i caratteri del file attraverso la 
    funzione fgetc() fino alla fine del file, se dobbiamo usare lo stesso 
    puntatore a file in altre funzioni dobbiamo ricordarci di riportare il
    puntatore/indicatore posizione (contenuto all'interno della struct FILE) 
    ad inizio file tramite rewind() o fseek() altrimenti non leggerà nulla
    
    Se si vuole importare un numero di letture superiore a MAX_LETTURE (99) allora
    il contatore delle letture si fermerà alle prime 99 (e stampa a video dei messaggi
    di errore) e le successive letture presenti nel file non verranno salvate nel vettore
    
    Usa macro MAX_LETTURE
*/
int conta_letture_file(FILE* infoMeteo){
    int numero_letture_nel_file = 1; // inizializzato a 1 in quanto partiamo dalla prima riga del file
    char carattere_temporaneo;
    bool limite_letture_raggiunto = false;
    do 
    {
        if( numero_letture_nel_file == MAX_LETTURE ){
            printf("Impossibile aggiungere tutte le letture presenti nel file!\n");
            printf("Verranno aggiunte solo le prime %d letture\n",numero_letture_nel_file);
            limite_letture_raggiunto = true;
        }
        else{
            /* 
               Legge un carattere dal file e sposta l'indicatore di 
               posizione alla posizione del carattere successivo
               
               fgetc() restituisce il valore ASCII associato al carattere letto
               dal file
            */
            carattere_temporaneo=fgetc(infoMeteo);

            /* 
               Se legge un carattere newline allora incrementiamo il numero
               di letture (cioè il numero di righe) presenti nel file
            */
            if( carattere_temporaneo=='\n' ){
                numero_letture_nel_file++;
            }
        }
    /* 
       Continuiamo finché fgetc() non legge il carattere di fine file EOF oppure
       se viene letto un numero maggiore di letture rispetto a MAX_LETTURE (99)
    */
    } while( carattere_temporaneo!=EOF && !limite_letture_raggiunto );
    
    return numero_letture_nel_file;
}

/* 
    NON RICHIESTA DALLA TRACCIA
    Imposta l'indicatore di posizione della struttura FILE per il flusso a cui 
    punta infoMeteo all'inizio del file
    
    Se immaginiamo il flusso di byte associato al file di testo come un nastro 
    continuo, la funzione rewind() riavvolge il nastro riportandolo al primo byte
    
    -PARAMETRI DI INPUT/OUTPUT: puntatore a FILE infoMeteo
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: modifica l'indicatore di posizione del FILE per il flusso
    a cui punta infoMeteo 
*/
void ritorna_ad_inizio_file(FILE* infoMeteo){
    rewind(infoMeteo); 
    /* 
       Potremmo usare fseek() (preferibile per debugging in quanto, a differenza
       della rewind(), fseek() restituisce 0 se l'operazione ha avuto successo) ma 
       rewind() ha una sintassi più leggibile
    */
}

/* 
    Importa delle letture da un file e le salva in un vettore 
    -PARAMETRI DI INPUT: una stringa nomeFile associata al nome del file
    -PARAMETRI DI INPUT/OUTPUT: il vettore dove salvare le letture meteo importate
    -OUTPUT (valore di ritorno): il numero di letture correttamente importate dal file
    
    -SIDE EFFECTS: interagisce con file presente sul disco (e l'apertura di tale
    file tramite funzione fopen() può fallire, in tal caso stampa su stderr)
    
    Se si vuole importare un numero di letture superiore a MAX_LETTURE (99) allora
    verranno salvate nel vettore solo le prime 99 letture
    
    Usa macro ERRORE_LETTURA_FILE
*/
int importaLetture(Lettura* lettureMeteo, const char *nomeFile) {
    FILE* infoMeteo = fopen(nomeFile,"r");
    if(!infoMeteo) //controlla se l'apertura del file è avvenuta correttamente
    {
        perror("Errore nell'apertura del file");
        return ERRORE_LETTURA_FILE;
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
    return i; //ritorna il numero di letture meteo correttamente lette dal file "info_meteo.txt"
}

/* 
    NON RICHIESTA DALLA TRACCIA
    Funzione di testing/debugging per stampare il numero di letture importate
    -PARAMETRI DI INPUT: il numero di letture correttamente importate dal file
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: stampa a video 
*/
void stampa_numero_letture_importate(int numeroLettureMeteo){
    printf("Sono state importate %d letture meteo con successo!\n\n",numeroLettureMeteo);
}

/* 
    Funzione che controlla il campo stato di una lettura per verificare se ha
    una temperatura valida
    -PARAMETRI DI INPUT: la lettura meteo che si vuole verificare
    -OUTPUT (valore di ritorno): valore booleano (vero se la lettura ha una temperatura 
    valida, in caso contrario restituisce falso)
    
    -SIDE EFFECTS: nessuno
*/
bool ha_temperatura(Lettura letturaDaVerificare){
    if( letturaDaVerificare.stato == SOLO_TEMPERATURA || letturaDaVerificare.stato == ENTRAMBE ){
        return true;
    }
    else{
        return false;
    }
}

/* 
    Funzione che controlla il campo stato di una lettura per verificare se ha
    un'umidità valida
    -PARAMETRI DI INPUT: la lettura meteo che si vuole verificare
    -OUTPUT (valore di ritorno): valore booleano (vero se la lettura ha un'umidità 
    valida, in caso contrario restituisce falso)
    
    -SIDE EFFECTS: nessuno
*/
bool ha_umidita(Lettura letturaDaVerificare){
    if( letturaDaVerificare.stato == SOLO_UMIDITA || letturaDaVerificare.stato == ENTRAMBE ){
        return true;
    }
    else{
        return false;
    }
}

/* 
    Funzione che aggiunge una nuova lettura meteo in coda al vettore
    -PARAMETRI DI INPUT: la lettura meteo che si vuole aggiungere al vettore
    -PARAMETRI DI INPUT/OUTPUT: il vettore che contiene le letture meteo e il 
    relativo riempimento
    -OUTPUT (valore di ritorno): valore booleano (vero se la lettura è stata aggiunta
    con successo, in caso contrario restituisce falso)
    
    -SIDE EFFECTS: modifica il vettore che contiene le letture meteo 
    
    L'aggiunta può fallire se il riempimento (numeroLettureMeteo)
    relativo al vettore ha già raggiunto il numero massimo di letture MAX_LETTURE
    (in questo caso la funzione restituisce falso)
    
    Usa macro MAX_LETTURE
*/
bool aggiungi_lettura(Lettura nuovaLettura, Lettura* lettureMeteo, int* numeroLettureMeteo){
    if( *numeroLettureMeteo == MAX_LETTURE ){
        return false;
    }
    else{
        lettureMeteo[*numeroLettureMeteo]=nuovaLettura;
        (*numeroLettureMeteo)++;
        return true;
    }
}

/* 
    NON RICHIESTA DALLA TRACCIA
    Funzione che aggiunge un numero variabile di letture (contenute in un vettore)
    al vettore che contiene le letture meteo importate da file
    -PARAMETRI DI INPUT: il vettore che contiene le nuove letture meteo da inserire
    -PARAMETRI DI INPUT/OUTPUT: il vettore che contiene le letture meteo e il 
    relativo riempimento
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: modifica il vettore che contiene le letture meteo 
    
    L'aggiunta può fallire se il riempimento relativo al vettore 
    che contiene le letture meteo ha già raggiunto il numero massimo di letture 
    MAX_LETTURE (in questo caso la funzione stampa a video un messaggio di errore)
    
    Nel caso in cui la lettura è stata aggiunta correttamente stampa a video
    un messaggio di conferma
    
    Usa macro NUMERO_NUOVE_LETTURE
*/
void aggiungi_nuove_letture(const Lettura* nuoveLetture, Lettura* lettureMeteo, int* numeroLettureMeteo ){
    bool lettura_aggiunta_con_successo = true;
    for(int i=0; i<NUMERO_NUOVE_LETTURE && lettura_aggiunta_con_successo; i++){
        lettura_aggiunta_con_successo = aggiungi_lettura(nuoveLetture[i], lettureMeteo, numeroLettureMeteo);
        if( lettura_aggiunta_con_successo ){
            printf("La lettura relativa alla località %s è stata aggiunta con successo!\n\n", nuoveLetture[i].localita);
        }
        else{
            printf("Impossibile aggiungere nuove letture meteo\n");
            lettura_aggiunta_con_successo = false;
        }
    }
}

/* 
    Funzione che stampa a video le informazioni relative alla lettura meteo di
    una località
    -PARAMETRI DI INPUT: una lettura meteo da stampare a video
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: stampa a video 
    
    (la funzione copre anche i casi in cui si voglia stampare una località che ha 
    solo il campo della temperatura valido o solo il campo dell'umidità valido, questo 
    dipende dalle specifiche del programma e quest'implementazione che copre tutti i casi 
    NON è richiesta dalla traccia)
    
    Nel caso in cui il campo della lettura relativo allo stato sia uguale a NESSUNA
    stampa un messaggio di errore per notificare l'utente che non sono presenti
    campi validi da stampare a video
*/
void stampa_localita(Lettura letturaDaStampare){
    switch(letturaDaStampare.stato){
        case ENTRAMBE:
            printf("\nLocalità:%s - Temperatura: %.1f °C - Umidità: %d \n", letturaDaStampare.localita, letturaDaStampare.temperatura, letturaDaStampare.umidita );
            break;
        case SOLO_TEMPERATURA:
            printf("\nLocalità:%s - Temperatura: %.1f °C \n", letturaDaStampare.localita, letturaDaStampare.temperatura );
            break;
        case SOLO_UMIDITA:
            printf("\nLocalità:%s - Umidità: %d \n", letturaDaStampare.localita, letturaDaStampare.umidita );
            break;
        default:
            printf("Errore: non ci sono campi validi da stampare per la lettura meteo relativa alla localita %s", letturaDaStampare.localita);
            break;
    }
}

/* 
    Funzione che stampa a video le informazioni relative a tutte le letture
    meteo presenti nel vettore che hanno una temperatura valida (il campo stato 
    della struttura deve essere dunque SOLO_TEMPERATURA o ENTRAMBE)
    -PARAMETRI DI INPUT: il vettore che contiene le letture meteo e il relativo riempimento
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: stampa a video le informazioni relative alle letture meteo
    che hanno temperatura valida (negli altri casi non stampa nulla)
*/
void stampa_localita_con_temperatura_valida(const Lettura* lettureMeteo, int numeroLettureMeteo){
    for(int i=0; i<numeroLettureMeteo; i++){
        if( ha_temperatura(lettureMeteo[i]) ){
            stampa_localita(lettureMeteo[i]);
        }
    }
}

/* 
    Funzione che stampa a video le informazioni relative alle 2 località (presenti 
    nel vettore) con la temperatura maggiore
    -PARAMETRI DI INPUT: il vettore che contiene le letture meteo e il relativo riempimento
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: stampa a video 
    
    Stampa dei messaggi di errore nel caso non ci siano località con una temperatura
    valida oppure non ci sia una seconda località con temperatura valida
    
    Usa le seguenti macro: MIN_TEMPERATURA, TEMPERATURA_MASSIMA_ASSENTE e 
    SECONDA_TEMPERATURA_MASSIMA_ASSENTE
*/
void temperature_maggiori(const Lettura* lettureMeteo, int numeroLettureMeteo){
    float temperatura_massima=MIN_TEMPERATURA-1; 
    float seconda_temperatura_massima=MIN_TEMPERATURA-1;
    /* 
       Nessuna temperatura valida avrà temperatura MIN_TEMPERATURA-1 quindi ciò lo rende
       un valore ideale per inizializzare le due variabili delle temperature massime per dei
       confronti
    */
    int indiceTempMassima=TEMPERATURA_MASSIMA_ASSENTE; 
    int indiceSecondaTempMassima=SECONDA_TEMPERATURA_MASSIMA_ASSENTE;
    /*
       Discorso analogo vale anche per i due indici, inizializziamo a -1 le due variabili
       che memorizzano gli indici delle letture con le due temperature maggiori, gli indici
       sono positivi quindi sicuramente non potranno assumere valore negativo -1 
       
       ( Potremmo anche non inizializzarli, ma per la logica del programma serve che
       abbiano un valore iniziale, se tale valore iniziale non viene modificato dalla funzione durante
       i controlli, allora possiamo concludere che non c'è una temperatura massima (o una seconda temperatura
       massima) )
    */

    for (int i = 0; i < numeroLettureMeteo; i++) {
        if ( ha_temperatura(lettureMeteo[i]) ) {
            
            // Se troviamo una temperatura maggiore di temperatura_massima 
            if ( lettureMeteo[i].temperatura > temperatura_massima ) {
                seconda_temperatura_massima = temperatura_massima;  // La precedente temperatura massima diventa la seconda temperatura massima
                indiceSecondaTempMassima = indiceTempMassima; // L'indice della precedente temperatura massima diventa l'indice della seconda temperatura massima
                
                /* 
                    Dopo aver memorizzato i valori della vecchia temperatura 
                    massima, possiamo aggiornare temperatura_massima e il relativo 
                    indice per memorizzarne la posizione all'interno del vettore
                */
                temperatura_massima = lettureMeteo[i].temperatura; 
                indiceTempMassima = i; 
            }
            
            /* 
               Se invece la temperatura è più alta della seconda temperatura massima 
               ma più bassa della prima temperatura massima allora essa diventa la 
               nuova seconda temperatura massima e aggiorniamo l'indice in modo da 
               memorizzare la posizione all'interno del vettore
            */
            if (lettureMeteo[i].temperatura > seconda_temperatura_massima && lettureMeteo[i].temperatura < temperatura_massima) {
                seconda_temperatura_massima = lettureMeteo[i].temperatura;
                indiceSecondaTempMassima = i;
            }
        }
    }

    /*
       Se la variabile indiceTempMassima non è stata modificata allora non c'è 
       una temperatura massima, in caso contrario stampa la lettura presente nel 
       vettore associata all'indice indiceTempMassima
    */
    if (indiceTempMassima == TEMPERATURA_MASSIMA_ASSENTE) {  
        printf("\nNon ci sono località con una temperatura valida\n");
    } else {
        printf("\nLocalità con la temperatura massima:\n");
        stampa_localita(lettureMeteo[indiceTempMassima]);
    }

    /*
       Se la variabile indiceSecondaTempMassima non è stata modificata allora non 
       c'è una seconda temperatura  massima, in caso contrario stampa la lettura 
       presente nel vettore associata all'indice indiceTempMassima
    */
    if (indiceSecondaTempMassima == SECONDA_TEMPERATURA_MASSIMA_ASSENTE) {
        printf("\nNon c'è una seconda località con una temperatura valida\n");
    } else {
        printf("\nLocalità con la seconda temperatura massima:\n");
        stampa_localita(lettureMeteo[indiceSecondaTempMassima]);
    }
}

/* 
    La funzione scorre tutto il vettore e se trova delle letture meteo che hanno
    dei valori non validi per la temperatura e/o per l'umidità li chiede all'utente
    e li modifica nel vettore
    -PARAMETRI DI INPUT: il riempimento del vettore che contiene le letture meteo
    -PARAMETRI DI INPUT/OUTPUT: il vettore che contiene le letture meteo
    -OUTPUT: nessuno
    
    -SIDE EFFECTS: modifica il vettore che contiene le letture meteo e interagisce
    con l'utente (quindi vengono stampati a video dei messaggi di errore nel caso 
    in cui gli inserimenti dell'utente non siano validi)
    
    Usa le seguenti macro: MIN_TEMPERATURA, MAX_TEMPERATURA, MIN_UMIDITA e
    MAX_UMIDITA
*/
void sostituisci_valori_non_validi(Lettura* lettureMeteo, int numeroLettureMeteo){
    for(int i=0; i<numeroLettureMeteo; i++){
        
        // Se una lettura non ha una temperatura valida, la chiediamo all'utente
        if( !ha_temperatura(lettureMeteo[i]) ){
            printf("\nLa località %s presenta una temperatura non valida\n", lettureMeteo[i].localita);
            /* 
               Chiediamo all'utente di inserire un valore valido per la temperatura
               e validiamo l'input
            */
            do{
                printf("Inserisci una nuova temperatura valida:");
                scanf("%f",&lettureMeteo[i].temperatura);
                if( lettureMeteo[i].temperatura<MIN_TEMPERATURA || lettureMeteo[i].temperatura>MAX_TEMPERATURA ){
                    printf("Inserimento non valido, si prega di riprovare!\n");
                }
            } while( lettureMeteo[i].temperatura<MIN_TEMPERATURA || lettureMeteo[i].temperatura>MAX_TEMPERATURA );
        }
        
        // Se una lettura non ha un'umidità valida, la chiediamo all'utente
        if( !ha_umidita(lettureMeteo[i]) ){
            printf("\nLa località %s presenta un'umidità non valida\n", lettureMeteo[i].localita);
            /* 
               Chiediamo all'utente di inserire un valore valido per l'umidità
               e validiamo l'input
            */
            do{
                printf("Inserisci una nuova umidità valida:");
                scanf("%d",&lettureMeteo[i].umidita);
                if( lettureMeteo[i].umidita<MIN_UMIDITA || lettureMeteo[i].umidita>MAX_UMIDITA ){
                    printf("Inserimento non valido, si prega di riprovare!\n");
                }
            } while( lettureMeteo[i].umidita<MIN_UMIDITA || lettureMeteo[i].umidita>MAX_UMIDITA );
        }
        
        /*
           Dopo aver assegnato dei valori validi alla temperatura e all'umidità
           modifichiamo lo stato relativo alla lettura 
        */
        lettureMeteo[i].stato=ENTRAMBE;
    }
}

int main()
{
    Lettura* LettureMeteo2025 = calloc(MAX_LETTURE, sizeof(Lettura));
    int numeroLettureMeteo = importaLetture(LettureMeteo2025, "info_meteo.txt");
    
    stampa_numero_letture_importate(numeroLettureMeteo); //per testing/debugging
    if( numeroLettureMeteo == ERRORE_LETTURA_FILE){
        return ERRORE_LETTURA_FILE;
    }
    
    // Prima richiesta
    stampa_localita_con_temperatura_valida(LettureMeteo2025, numeroLettureMeteo);
    
    // Seconda richiesta
    Lettura nuoveLetture[NUMERO_NUOVE_LETTURE] = {
        {"Roma", ENTRAMBE, TEMPERATURA_ROMA, UMIDITA_ROMA},
        {"Milano", SOLO_TEMPERATURA, TEMPERATURA_MILANO, UMIDITA_MILANO},
        {"Aci Trezza", NESSUNA, TEMPERATURA_ACI_TREZZA, UMIDITA_ACI_TREZZA},
        {"Aosta", SOLO_UMIDITA, TEMPERATURA_AOSTA, UMIDITA_AOSTA}
    };
    aggiungi_nuove_letture(nuoveLetture, LettureMeteo2025, &numeroLettureMeteo);
    
    // Terza richiesta
    temperature_maggiori(LettureMeteo2025, numeroLettureMeteo);
    
    // Richiesta bonus
    sostituisci_valori_non_validi(LettureMeteo2025, numeroLettureMeteo);
    stampa_localita_con_temperatura_valida(LettureMeteo2025, numeroLettureMeteo);
    temperature_maggiori(LettureMeteo2025, numeroLettureMeteo);
    return NESSUN_ERRORE;
}