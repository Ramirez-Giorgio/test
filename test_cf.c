#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Funzione per verificare se un anno è bisestile
int ControlloAnno(int anno) {
    if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0)) {
        return 1; // Anno bisestile
    }
    return 0; // Non è bisestile
}

// Funzione per verificare se una data è valida
int ControlloData(int giorno, int mese, int anno) {
    if (mese < 1 || mese > 12 || giorno < 1 || giorno > 31)
    {
        return 0; // ridà 0 per la data non valida   
    }

    if ((mese == 4 || mese == 6 || mese == 9 || mese == 11) && giorno > 30) // per i mesi che hanno 30 giorni  
    {
        return 0;
    }
    if (mese == 2) {
        if (ControlloAnno(anno)) {
            if (giorno > 29)// Febbraio in anno bisestile
            {
                return 0;
            }; 
        } 
        else {
            if (giorno > 28)// Febbraio in anno non bisestile 
            {
                return 0;
            };
        }
    }
        return 1; // Data valida
}

// Funzione per estrarre le consonanti del cognome
void estraiCons(const char *input, char *consonanti, int maxConsonanti) {
    int consonantiTrovate = 0;//lo inizializzo a 0
    for (int i = 0; input[i] != '\0' && consonantiTrovate < maxConsonanti; i++) { //for per fargli prendere le consonanti
        char c = toupper(input[i]);//mette tutto in maiscolo dentro il char c 
        if ((c >= 'A' && c <= 'Z') && !(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
            consonanti[consonantiTrovate++] = c;
        }
    }
    while (consonantiTrovate < maxConsonanti) {
        consonanti[consonantiTrovate++] = 'X'; // Riempie con 'X' se non ci sono abbastanza consonanti
    }
    consonanti[consonantiTrovate] = '\0'; // Termina la stringa
}

// Funzione per calcolare le consonanti del nome
int calcolaNome(char nome[], char codice_fiscale[]) {
    char cons[25] = {0}, vocal[25] = {0};//dichiaro l'array con dentro nulla
    int cont_cons = 0, cont_vocal = 0;//i contatori che poi userò in 2 if

    for (int i = 0; nome[i] != '\0'; i++) {
        char c = toupper(nome[i]);//come nel congnome metto tutto in mauscolo
        if ((c >= 'A' && c <= 'Z')) { //if per le lettere dalla A alla Z
            if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                vocal[cont_vocal++] = c;//se vocale A,E,I,O,U e il contatore aumenta
            } else {
                cons[cont_cons++] = c;//stessa cosa ma per le consonanti
            }
        }
    }

    if (cont_cons >= 4) {// per i casi di 4 o più consonanti
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = cons[2];
        codice_fiscale[5] = cons[3];
    } 
    else if (cont_cons == 3) {//invece per 3
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = cons[1];
        codice_fiscale[5] = cons[2];
    } 
    else if (cont_cons == 2) {//per 2
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = cons[1];
        codice_fiscale[5] = vocal[0];
    } 
    else if (cont_cons == 1 && cont_vocal >= 2) {//qua se è 1 e allora prende anche 2 vocali
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = vocal[0];
        codice_fiscale[5] = vocal[1];
    } 
    else if (cont_cons == 1 && cont_vocal == 1) {//stesso ma se c'è anche 1 sola vocale
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = vocal[0];
        codice_fiscale[5] = 'X';//per riempire il buco di 1 mette una x
    } 
    else if (cont_cons == 0 && cont_vocal >= 2) {//qua invece se sono direttamente solo 2 vocali
        codice_fiscale[3] = vocal[0];
        codice_fiscale[4] = vocal[1];
        codice_fiscale[5] = 'X';//quindi metterà pure qui una x
    } else {
        printf("Nome non valido.\n");//se non soddisfa nulla
        return 0;
    }
    return 1;// se ci sono errori e non prende nulla allora ritornerà 1 nel main e terminerà tutto
}

// Funzione per calcolare la parte del codice fiscale relativa alla data
void calcolaData(int giorno, int mese, int anno, char *cod_anno, char *cod_mese, int *cod_giorno) {
    *cod_anno = (anno % 100) / 10 + '0'; // per far si che prende le Ultime due cifre dell'anno
    *(cod_anno + 1) = (anno % 10) + '0';
    *(cod_anno + 2) = '\0';//cosi non prende le prime 2 come nel caso 2008 non prende 20 ma prende 08

    switch (mese) {//in base ad ogni caso il puntatore prende una lettera per il mese
        case 1: 
            *cod_mese = 'A'; 
            break;
        case 2:
            *cod_mese = 'B'; 
            break;
        case 3:
            *cod_mese = 'C'; 
            break;
        case 4: 
            *cod_mese = 'D'; 
            break;
        case 5: 
            *cod_mese = 'E'; 
            break;
        case 6: 
            *cod_mese = 'H'; 
            break;
        case 7: 
            *cod_mese = 'L'; 
            break;
        case 8: 
            *cod_mese = 'M'; 
            break;
        case 9: 
            *cod_mese = 'P'; 
            break;
        case 10: 
            *cod_mese = 'R'; 
            break;
        case 11: 
            *cod_mese = 'S'; 
            break;
        case 12: 
            *cod_mese = 'T'; 
            break;
        default: 
            *cod_mese = 'X'; 
            break;
    }

    *cod_giorno = giorno;// per il giorno il puntatore è uguale 
}

// Funzione per cercare il codice catastale del comune
void controllocomune(char *com, char *comune) {
    FILE *fd = fopen("comuni_test.txt", "r");//apre il file comuni
    if (fd == NULL) {
        printf("Errore nell'apertura del file\n");
        return;
    }

    char record[100];//per immagazzinare temporaneamente i dati del comune di nscità
    while (fscanf(fd, "%s", record) != EOF) {
        if (strcmp(comune, record) == 0) {
            fscanf(fd, "%s", record);//per comparare il nome del comine che viene inserito tutto in mucsolo
            strncpy(com, record, 4);//nel caso vero prende il codice catastale di 4 cfre
            com[4] = '\0';
            break;
        }
    }
    fclose(fd);//chiude il file quando finisce di prendere il codce catastale
}

// Funzione per calcolare il codice di controllo
char calcolaCodiceControllo(char codice_fiscale[]) {
    int valori_dispari[26] = {1, 0, 5, 7, 9, 13, 15, 17, 19, 21, 2, 4, 18, 20, 11, 3, 6, 8, 12, 14, 16, 10, 22, 25, 24, 23};
    int valori_pari[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

    int somma = 0;//lo inizializzo a 0
    for (int i = 0; i < 15; i++) {
        char c = toupper(codice_fiscale[i]);
        if (i % 2 == 0) { // Posizione dispari
            if (c >= '0' && c <= '9') somma += valori_dispari[c - '0'];
            else somma += valori_dispari[c - 'A'];
        } else { // Posizione pari
            if (c >= '0' && c <= '9') somma += valori_pari[c - '0'];
            else somma += valori_pari[c - 'A'];
        }
    }
    return 'A' + (somma % 26); // Codice di controllo
}

// Funzione main
int main() {
    char cognomi[100], nomi[100], comune[100];//gli array di char usati
    char codice_fiscale[16] = {0}, consonantiCognome[4] = {0};//inizializzati a 0 all'interno
    char cod_anno[3], cod_mese;//array per anno e mese che in base all'int inserito verrà messa una lettera
    int giorno, mese, anno, cod_giorno;//per prendere la data in intero quando viene inserita

    printf("Inserisci i cognomi (separati da spazi): ");//inserisce il cognome
    fgets(cognomi, sizeof(cognomi), stdin);
    cognomi[strcspn(cognomi, "\n")] = '\0';

    printf("Inserisci i nomi (separati da spazi): ");//inserisce il noem
    fgets(nomi, sizeof(nomi), stdin);
    nomi[strcspn(nomi, "\n")] = '\0';

    printf("Inserisci la data di nascita (gg/mm/aaaa): ");//inserisce la data 
    char data_input[20];
    fgets(data_input, sizeof(data_input), stdin);
    if (sscanf(data_input, "%d/%d/%d", &giorno, &mese, &anno) != 3) {
        printf("Formato data non valido.\n");
        return 1;
    }

    printf("Inserisci il sesso (M/F): ");//inserisce il genere
    char sesso_input[10];
    fgets(sesso_input, sizeof(sesso_input), stdin);
    char sesso = toupper(sesso_input[0]); // Prende il primo carattere e lo converte in maiuscolo
    if (sesso != 'M' && sesso != 'F') {
        printf("Sesso non valido.\n");
        return 1;
    }

    printf("Inserisci il nome del comune di nascita' (tutto maiuscolo): ");//inserisci il comune di nascità
    fgets(comune, sizeof(comune), stdin);
    comune[strcspn(comune, "\n")] = '\0';

    // Calcolo del codice fiscale
    estraiCons(cognomi, consonantiCognome, 3);//richiamo della funzione per le cononanti nel cognome
    if (!calcolaNome(nomi, codice_fiscale))
    {
        return 1;
    }
    calcolaData(giorno, mese, anno, cod_anno, &cod_mese, &cod_giorno);//richiamo della funzione per la data
    if (sesso == 'F' || sesso == 'f') //per il genere
    {
        cod_giorno += 40;
    }

    controllocomune(codice_fiscale + 11, comune);//richiamo della funzione per il comune 

    // Costruzione del codice fiscale
    strncpy(codice_fiscale, consonantiCognome, 3); // Copia le prime 3 consonanti del cognome
    codice_fiscale[6] = cod_anno[0]; // Inserisci la prima cifra dell'anno
    codice_fiscale[7] = cod_anno[1]; // Inserisci la seconda cifra dell'anno
    codice_fiscale[8] = cod_mese; // Inserisci il codice del mese
    codice_fiscale[9] = (cod_giorno / 10) + '0'; // Inserisci la prima cifra del giorno
    codice_fiscale[10] = (cod_giorno % 10) + '0'; // Inserisci la seconda cifra del giorno
    codice_fiscale[15] = calcolaCodiceControllo(codice_fiscale); // Calcola e inserisci il codice di controllo
    codice_fiscale[16] = '\0'; // Termina la stringa

    // Stampa il codice fiscale
    printf("Codice Fiscale: %s\n", codice_fiscale);

    return 0;
}