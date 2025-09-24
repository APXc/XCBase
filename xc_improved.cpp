/*
Copyright
Project: XCBase
Author: Alessio Pellizzaro <alessio.pellizzaro@apserial.it>
Github User: APXc
Year: 2016
Version: 0.6 (Updated 2025)
Nation: Italy

commercial use not authorized
*/

#include "pch_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream> 
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>

// Cross-platform sleep function
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#endif

#define Max_word 122 // massimo di lettura 

using namespace std;

// Function prototypes
char *xcIn(char*);
char *xcOt(char*);
char *xcInSecure(char*, int key);
char *xcOtSecure(char*, int key);
char *lett(char file[]);
int Scritura(const char *testo);
void logAp(const char*);
int generateKey();
void showProgressBar(const char* operation);
bool secureScanf(char* buffer, size_t bufferSize);

int main(int argc, char *argv[]) {
    // Suppress unused parameter warnings
    (void)argc;
    (void)argv;
    
    int menu;
    char Maxparola[Max_word];
    printf("%s", ITTitolo);
    char *string;
    int scr = 3;
    cout << "Selezionare Menu" << endl;
    SLEEP_MS(100);
    cout << "Criptaggio Semplice(1), DeCriptaggio Semplice(2), Gestione da File(3), Criptaggio Sicuro(4)" << endl;
    logAp("avvio Programma Corretto");
    
    if (scanf("%d", &menu) != 1) {
        printf("Errore di input\n");
        return -1;
    }
    
    switch (menu) {
        case 1:
        {
            logAp("selezionato menu 1 per criptaggio\n");
            cout << "inserisci la parola\n" << endl;
            if (!secureScanf(Maxparola, sizeof(Maxparola))) {
                printf("Errore di input\n");
                return -1;
            }
            string = xcIn(Maxparola);
            showProgressBar("Criptaggio");
            printf("\n%s\n\n", string);
            scr = Scritura(string);
            if (scr != 0) {
                printf("Impossibile salvare in report\n");
                logAp("Impossibile salvare in report\n");
            } else {
                printf("Scrittura file riuscita\n");
                logAp("Scrittura file riuscita\n");
            }
            break;
        }
            
        case 2:
        {
            logAp("Selezionato Menu per Decriptaggio\n");
            cout << "inserisci la parola" << endl;
            if (!secureScanf(Maxparola, sizeof(Maxparola))) {
                printf("Errore di input\n");
                return -1;
            }
            string = xcOt(Maxparola);
            showProgressBar("Decriptaggio");
            printf("\n%s\n\n", string);
            scr = Scritura(string);
            if (scr != 0) {
                printf("Impossibile salvare in report\n");
                logAp("Impossibile salvare in report\n");
            } else {
                printf("Scrittura file riuscita\n");
                logAp("Scrittura file riuscita\n");
            }
            break;
        }
            
        case 3:
        {
            cout << "Menu Lettura file\n" << endl;
            char percorso[Max_word];
            logAp("Selezionato Menu Lettura file\n");
            if (!secureScanf(percorso, sizeof(percorso))) {
                printf("Errore di input\n");
                return -1;
            }
            logAp(percorso);
            char *risul = lett(percorso);
            if (risul == NULL) {
                return 57;
            }
            printf("\n%s\n", risul);
            int sel = 0;
            char *texte;
            printf("Criptare Testo(1) o Decriptare Testo(2)?\n");
            if (scanf("%d", &sel) != 1) {
                printf("Errore di input\n");
                return -1;
            }
            if (sel == 1) {
                texte = xcIn(risul);
                showProgressBar("Criptaggio");
                printf("\n%s\n\n", texte);
                scr = Scritura(texte);
                if (scr != 0) {
                    printf("Impossibile salvare in report\n");
                    logAp("Impossibile salvare in report\n");
                } else {
                    printf("Scrittura file riuscita\n");
                    logAp("Scrittura file riuscita\n");
                }
            } else if (sel == 2) {
                texte = xcOt(risul);
                showProgressBar("Decriptaggio");
                printf("\n%s\n\n", texte);
                scr = Scritura(texte);
                if (scr != 0) {
                    printf("Impossibile salvare in report\n");
                    logAp("Impossibile salvare in report\n");
                } else {
                    printf("Scrittura file riuscita\n");
                    logAp("Scrittura file riuscita\n");
                }
            } else {
                return -1;
            }
            break;
        }
        
        case 4:
        {
            logAp("Selezionato Menu Criptaggio Sicuro\n");
            cout << "Criptaggio sicuro con chiave casuale" << endl;
            cout << "inserisci la parola" << endl;
            if (!secureScanf(Maxparola, sizeof(Maxparola))) {
                printf("Errore di input\n");
                return -1;
            }
            int key = generateKey();
            cout << "Chiave generata: " << key << " (salvala per il decriptaggio!)" << endl;
            string = xcInSecure(Maxparola, key);
            showProgressBar("Criptaggio Sicuro");
            printf("\nTesto criptato: %s\n", string);
            printf("Chiave: %d\n\n", key);
            
            // Save both encrypted text and key
            ofstream keyFile("key.txt");
            keyFile << key;
            keyFile.close();
            
            scr = Scritura(string);
            if (scr != 0) {
                printf("Impossibile salvare in report\n");
                logAp("Impossibile salvare in report\n");
            } else {
                printf("Scrittura file riuscita. Chiave salvata in key.txt\n");
                logAp("Scrittura file riuscita con chiave\n");
            }
            break;
        }
            
        default:
            printf("Opzione non valida\n");
            return -1;
    }

    return 0;
}

bool secureScanf(char* buffer, size_t bufferSize) {
    // Skip the newline from previous input
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    if (fgets(buffer, bufferSize, stdin) != NULL) {
        // Remove newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        return true;
    }
    return false;
}

void showProgressBar(const char* operation) {
    cout << operation << " in corso" << endl;
    for (int i = 0; i < 50; i++) {
        printf("#");
        SLEEP_MS(20);
    }
    cout << endl;
}

int generateKey() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 255);
    return dis(gen);
}

char *xcIn(char* word) {
    int val = 0;
    int carateri = strlen(word);
    int temp;
    logAp("Criptaggio semplice in corso....");
    
    while (val < carateri) {
        temp = word[val];
        if (temp == 32) { // se il carattere è spazio diventa €
            temp = 128;
        }
        temp = temp + 1;
        if (temp == 127 || temp > 127) { // se il carattere è ~ porta a !
            temp = 33;
        } else if (temp == 32 || temp < 32) { // se il carattere è spazio porta a ù 
            temp = 249;
        }
        word[val] = temp;
        val++;
    }

    return word;
}

char *xcOt(char* word) {
    int val = 0;
    int carateri = strlen(word);
    int temp;
    logAp("Decriptaggio semplice in corso....");
    
    while (val < carateri) {
        temp = word[val];
        if (temp == 128) { // se il carattere è € diventa spazio
            temp = 32;
        }
        temp = temp - 1;
        if (temp == 32 || temp < 32) { // se il carattere e ! porta a ~
            temp = 126;
        } else if (temp == 248 || temp > 248) { // se il carattere è ù porta a spazio 
            temp = 32;
        }
        
        word[val] = temp;
        val++;
    }
    return word;
}

char *xcInSecure(char* word, int key) {
    int val = 0;
    int carateri = strlen(word);
    int temp;
    logAp("Criptaggio sicuro in corso....");
    
    while (val < carateri) {
        temp = word[val];
        // XOR encryption with key
        temp = temp ^ key;
        // Additional scrambling
        temp = (temp + key) % 256;
        word[val] = temp;
        val++;
    }

    return word;
}

char *xcOtSecure(char* word, int key) {
    int val = 0;
    int carateri = strlen(word);
    int temp;
    logAp("Decriptaggio sicuro in corso....");
    
    while (val < carateri) {
        temp = word[val];
        // Reverse the scrambling
        temp = (temp - key + 256) % 256;
        // XOR decryption with key
        temp = temp ^ key;
        word[val] = temp;
        val++;
    }

    return word;
}

char *lett(char file[]) {
    static char let[MAXWORD];
    ifstream fileLet;
    cout << "lettura file in corso" << endl;
    logAp("lettura file in corso");
    fileLet.open(file, ifstream::in);
    if (!fileLet) {
        printf("Errore di Lettura di file impossibile continuare\n");
        logAp("Errore di Lettura");
        return NULL;
    }
    
    int i = 0;
    while (!fileLet.eof() && i < MAXWORD - 1) {
        fileLet.get(let[i]);
        if (!fileLet.eof()) {
            cout << let[i];
            i++;
        }
    }
    let[i] = '\0';
    fileLet.close();
    return let;
}

int Scritura(const char *testo) {
    time_t data;
    struct tm *datainfo;
    data = time(NULL);
    datainfo = localtime(&data);
    printf("\nScritura su File\n");
    logAp("Scrittura su File");
    cout << (datainfo->tm_year + 1900) << "\\" << (datainfo->tm_mon + 1) << "\\" 
         << (datainfo->tm_mday) << "\\ " << (datainfo->tm_hour) << ":" 
         << (datainfo->tm_min) << endl;
    
    ofstream Salvafile("report.txt");
    if (!Salvafile) {
        logAp("Errore di Scrittura su File");
        return 1;
    }
    
    Salvafile << testo;
    Salvafile.close();
    logAp("Scrittura riuscita");
    return 0;
}

void logAp(const char *testo) {
    time_t data;
    struct tm *datainfo;
    data = time(NULL);
    datainfo = localtime(&data);
    
    ofstream Salvafile("log.txt", ios::app);
    if (Salvafile) {
        Salvafile << "[" << (datainfo->tm_year + 1900) << "\\" 
                  << (datainfo->tm_mon + 1) << "\\" << (datainfo->tm_mday) 
                  << "\\ " << (datainfo->tm_hour) << ":" << (datainfo->tm_min) 
                  << "] " << testo << "\n" << endl;
        Salvafile.close();
    }
    return;
}