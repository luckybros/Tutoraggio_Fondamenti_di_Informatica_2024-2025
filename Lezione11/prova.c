/*Traccia: Sanremo
 
Rispettando i principi della programmazione strutturata, progettare ed implementare un programma che permetta ad un giurato l’assegnazione dei voti ai concorrenti al Festival di Sanremo.
 
1.All’avvio il Programma importa la lista dei concorrenti (massimo 29) da un file in maniera automatica.
 
2. Per ciascun concorrente non valutato (all’inizio tutti i concorrenti sono sprovvisti di voto), il programma permette di scegliere se assegnare una voto (un numero da 1 a 10 - se il voto inserito non è valido, il programma ne richiede una nuova immissione) oppure posticiparne l’inserimento.
 
3. Vengono stampate tutte le esibizioni, con "[N.D.]" in corrispondenza dei voti non disponibili.
 
4. Viene stampato il riepilogo,  nella seguente forma:
Numero di esibizioni totali: 5
Numero di voti inseriti: 3
Valutazione media: 4.2
 
5. Vengono aggiunte alla lista delle esibizioni le due seguenti esibizioni (nota bene: NON viene richiesto all'utente, ma vanno direttamente inseriti i dati, scritti esplicitamente nel codice):
 
concorrente: Massimo Ranieri, valutato: false, voto: 999
 
concorrente: Elodie, valutato: false, voto: 999
 
6. viene fornita al giurato la possibilità di completare la valutazione (per i concorrenti non valutati in precedenza e per le nuove  esibizioni, come nel punto 2)
 
7. vengono stampate tutte le esibizioni (come nel punto 3)
 
8. viene stampato il riepilogo (come nel punto 4)
 
Quindi il programma termina.
 
BONUS: nel riepilogo, riportare anche l'esibizione con il voto più alto, nella forma
Valutazione più alta: Joan Thiele, 8
 
Nota: NON è richiesto un comportamento iterativo, ma per comodità di test è possibile ad esempio implementare un ciclo do-while infinito che ripeta le operazioni da testare (il ciclo va rimosso o commentato prima della consegna).
 
Dettagli implementativi
 
Il programma definisce un record (struct) esibizione con i seguenti campi:
 
    concorrente (stringa di lunghezza massima 120 caratteri)
 
    valutato (bool, true se il giurato ha fornito un voto per il concorrente, false altrimenti)
 
    voto (intero compreso tra 1 e 10, inclusi)
 
Le informazioni relative ai concorrenti ed alle valutazioni sono conservate in una struttura dati di tipo “array di record esibizione” con nome “esibizioni2025”.
 
La struttura dati esibizioni 2025 è memorizzata in area HEAP è può ospitare al massimo 29 record Esibizione.
 
I record per Massimo Ranieri ed Elodie non vengono inseriti a mano dall’utente, ma sono definiti direttamente nel codice come variabili automatiche.
 
 
Funzioni da implementare:
voto_is_valido()
    : controlla se il voto è compreso tra 1 e 10 e restituisce true se è così
    input: numero (intero)
 
mostra_riepilogo(): stampa a video riepilogo
    input: array di record Esibizione e relativo riempimento
 
indice_prossimo_concorrente_non_valutato(): restituisce indice del prossimo concorrente non valutato a partire da un indice di partenza specificato
    input: array di record Esibizione, relativo riempimento, e indice di partenza
    output: indice del primo concorrente non valutato (a partire dall’indice di partenza). Viene restituito -1 se tutti i concorrenti hanno un voto.
 
aggiungi_esibizione(): dato un record esibizione, lo accoda alla lista di valutazioni, restituisce false se non è possibile perché è stato superato il numero massimo di esibizioni
    input: record Esibizione nuovaEsibizione
    input,output: array di record Esibizione e relativo riempimento
    output (valore di ritorno): false se è stato già raggiunta la dimensione massima della lista esibizioni, true se è stato effettuato l'inserimento
 
completa_valutazioni() permette al giurato di inserire (da tastiera) i voti per i concorrenti non ancora valutati.
    Richiama la funzione voto_is_valido() per validare il voto fornito dal giurato e la funzione indice_prossimo_concorrente_non_valutato() per individuare per quali concorrenti chiedere il voto.
    input: array di record Esibizione e relativo riempimento
 
 
Per l'implementazione si richiede di seguire le buone pratiche di programmazione strutturata, tra cui
 
    strutturare il programma secondo l'approccio top-down (nel main() deve essere leggibile la struttura generale del programma, lasciando solo il minimo dei dettagli implementativi)
 
    evitare variabili globali;
 
    utilizzare identificativi con nomi autoesplicativi;
 
    non usare valori letterali, preferendo costanti, enumerativi, e macro di preprocessore;
 
    dichiarare ed inizializzare variabili nello scope più restrittivo;
 
    evitare ripetizioni del codice (copia-e-incolla) */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_CONCORRENTI 29
#define MAX_CARATTERI 121
#define ERRORE_FILE -1

typedef struct {
    bool valutato;
    int voto;
    char nome[MAX_CARATTERI];
} Esibizione;

int importaConcorrenti(Esibizione* valutazioni, int numeroConcorrentiDaImportare, const char* nomeFile);
bool voto_is_valido(int voto);
void mostra_riepilogo(Esibizione* esibizioni2025, int riemp);
int indice_prossimo_concorrente_non_valutato(Esibizione* esibizioni2025, int riemp, int indice_di_partenza);
bool aggiungi_esibizione(Esibizione nuova_esibizione, Esibizione* esibizioni2025, int* riemp);
void completa_valutazioni(Esibizione* esibizioni2025, int riemp);
void stampa_concorrenti(Esibizione* esibizioni2025, int riemp);

int main() { 
    
    Esibizione* esibizioni2025 = calloc(MAX_CONCORRENTI, sizeof(Esibizione));
    int numero_concorrenti_da_importare = 15;

    int numero_concorrenti_importati = importaConcorrenti(esibizioni2025, numero_concorrenti_da_importare, "sanremo.txt");

    completa_valutazioni(esibizioni2025, numero_concorrenti_importati);

    stampa_concorrenti(esibizioni2025, numero_concorrenti_importati);

    mostra_riepilogo(esibizioni2025, numero_concorrenti_importati);

    Esibizione nuova_esibizione_1 = { false, 999, "Elodie" };
    Esibizione nuova_esibizione_2 = { false, 999, "Massimo Ranieri" };

    aggiungi_esibizione(nuova_esibizione_1, esibizioni2025, &numero_concorrenti_importati);
    aggiungi_esibizione(nuova_esibizione_2, esibizioni2025, &numero_concorrenti_importati);
    
    printf("\n\n");

    completa_valutazioni(esibizioni2025, numero_concorrenti_importati);

    stampa_concorrenti(esibizioni2025, numero_concorrenti_importati);

    mostra_riepilogo(esibizioni2025, numero_concorrenti_importati);
}

void stampa_concorrenti(Esibizione* esibizioni2025, int riemp) {
    printf("\n\nESIBIZIONI\n");
    
    for(int i = 0; i < riemp; i++) {
        printf("Concorrente: %s\n", esibizioni2025[i].nome);
        printf("Voto: ");
        
        if(esibizioni2025[i].valutato) {
            printf("%d\n", esibizioni2025[i].voto);
        }
        else {
            printf("[N./D.]\n");
        }
    }
}

int importaConcorrenti(Esibizione* valutazioni, int numeroConcorrentiDaImportare, const char* nomeFile) {
   FILE* file = fopen(nomeFile, "r");
   if (!file) {
       perror("Errore nell'apertura del file");
       return ERRORE_FILE;
   }
   int i = 0;
   // Legge numeroConcorrentiDaImportare concorrenti (meno se non sono presenti nel file)
   while (i < numeroConcorrentiDaImportare && fscanf(file, " %[^\n]",
                                              valutazioni[i].nome) != EOF) {
       valutazioni[i].valutato = false;
       valutazioni[i].voto = 999;
       i++;
   }
   fclose(file);
   return i; // Restituisce il numero di recensioni effettivamente importate
}

bool voto_is_valido(int voto) {
    /*if(voto >= 1 && voto <= 10) {
        return true;
    }
    return false;*/

    return (voto <= 10 && voto >= 1);
}

void mostra_riepilogo(Esibizione* esibizioni2025, int riemp) {
    //4. Viene stampato il riepilogo,  nella seguente forma:
    //Numero di esibizioni totali: 5
    //Numero di voti inseriti: 3
    //Valutazione media: 4.2
    // Votazione più alta: Lucio corsi, 10

    int voti_inseriti = 0;
    float media = 0;
    float somma_voti = 0;
    Esibizione esibizione_migliore;
    esibizione_migliore.voto = -1;

    for(int i = 0; i < riemp; i++) {
        if(esibizioni2025[i].valutato) {
            somma_voti += esibizioni2025[i].voto;
            voti_inseriti++;

            if(esibizioni2025[i].voto > esibizione_migliore.voto) {
                esibizione_migliore = esibizioni2025[i];
            }
        }        
    }

    media = somma_voti / voti_inseriti;

    printf("\n\nRIEPILOGO\n");
    printf("Numero di esibizioni totali: %d\n", riemp);
    printf("Numero di voti inseriti: %d\n", voti_inseriti);
    printf("Valutazione media: %.2f\n", media);
    printf("Votazione più alta: %s, %d\n", esibizione_migliore.nome, esibizione_migliore.voto);
}

int indice_prossimo_concorrente_non_valutato(Esibizione* esibizioni2025, int riemp, int indice_di_partenza) {
    for(int i = indice_di_partenza; i < riemp; i++) {
        if(!esibizioni2025[i].valutato) {
            return i;
        } 
    }
    return -1;
}

bool aggiungi_esibizione(Esibizione nuova_esibizione, Esibizione* esibizioni2025, int* riemp) {
    if(*riemp == MAX_CONCORRENTI) {
        return false;
    }

    esibizioni2025[*riemp] = nuova_esibizione;

    (*riemp)++;

    return true;
}

void completa_valutazioni(Esibizione* esibizioni2025, int riemp) {
    int indice = 0;

    do {
        indice = indice_prossimo_concorrente_non_valutato(esibizioni2025, riemp, indice);

        if(indice != -1) {
            int scelta;
            printf("Vuoi inserire il voto per %s? (0 - no, 1 - si)\n", esibizioni2025[indice].nome);
            scanf("%d", &scelta);

            if(scelta == 1) {
                do {
                    printf("Inserisci voto tra 1 e 10\n");
                    scanf("%d", &esibizioni2025[indice].voto);
            
                    if(!voto_is_valido(esibizioni2025[indice].voto)) {
                        printf("ERRORE! Inserisci un voto tra 1 e 10\n");
                    }
                } while(!voto_is_valido(esibizioni2025[indice].voto));
            
                esibizioni2025[indice].valutato = true;
            } 
            
            else {
                indice = indice + 1;
            }
        }
        
    } while(indice != -1);
}

