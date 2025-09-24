/*
Copyright
Project: XCBase
Author: Alessio Pellizzaro <alessio.pellizzaro@apserial.it>
Github User: APXc
Year: 2016
Version: 0.5
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

// Cross-platform sleep function
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#endif

#define Max_word 122 // massimo di lettura 
#pragma warning(disable : 4996)

using namespace std;

// Function prototypes
char *xcIn(char*);
char *xcOt(char*);
char *lett(char file[], char*);
int Scritura(char *testo);
void logAp(const char*);

int main(int argc, char *argv[]) {
    int aggiunta;
    int menu;
    char Maxparola[Max_word];
    printf("%s", ITTitolo);
    char *string;
    int scr = 3;
    char *dat;
    cout << "Selezionare Menu" << endl;
    SLEEP_MS(5);
    cout << "Criptaggio(1), DeCriptaggio(2), Gestione da File(3)" << endl;
    logAp("avvio Programma Corretto");
    cin >> menu;
    
    switch (menu) {
        case 1:
            logAp("selezionato menu 1 per criptaggio\n");
            cout << "inserisci la parola\n" << endl;
#ifdef _WIN32
            scanf_s("%s", &Maxparola, sizeof(Maxparola));
#else
            scanf("%121s", Maxparola); // Prevent buffer overflow
#endif
            string = xcIn(Maxparola);
            for (aggiunta = 0; aggiunta < 50; aggiunta++) {
                printf("#");
                SLEEP_MS(20);
            }
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
            
        case 2:
            logAp("Selezionato Menu per Decriptaggio\n");
            cout << "inserisci la parola" << endl;
#ifdef _WIN32
            scanf_s("%s", &Maxparola, sizeof(Maxparola));
#else
            scanf("%121s", Maxparola);
#endif
            string = xcOt(Maxparola);
            for (aggiunta = 0; aggiunta < 50; aggiunta++) {
                printf("#");
                SLEEP_MS(20);
            }
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
            
        case 3:
        {
            cout << "Menu Lettura file\n" << endl;
            char percorso[Max_word];
            logAp("Selezionato Menu Lettura file\n");
            cin >> percorso;
            dat = percorso;
            logAp(percorso);
            char *risul = lett(percorso, dat);
            if (risul == NULL) {
                return 57;
            }
            printf("\n%s\n", risul);
            int sel = 0;
            char *texte;
            printf("Criptare Testo(1) o Decriptare Testo(2)?\n");
            cin >> sel;
            if (sel == 1) {
                texte = xcIn(risul);
                for (int aggiunta = 0; aggiunta < 50; aggiunta++) {
                    printf("#");
                    SLEEP_MS(20);
                }
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
                for (int aggiunta = 0; aggiunta < 50; aggiunta++) {
                    printf("#");
                    SLEEP_MS(20);
                }
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
            
        default:
            printf("Opzione non valida\n");
            return -1;
    }

    return 0;
}

char *xcIn(char* word) {
    int val = 0;
    int carateri = strlen(word);
    int temp;
    cout << "Criptaggio in corso" << endl;
    logAp("Criptaggio in corso....");
    
    while (val < carateri) {  // Fixed condition to prevent buffer overrun
        temp = word[val];
        if (temp == 32) { // se il carattere è spazio diventa €
            temp = 128;
        }
        temp = temp + 1;  // Fixed the temp++ issue
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
    cout << "Decriptaggio in corso" << endl;
    logAp("Decriptaggio in corso....");
    
    while (val < carateri) {  // Fixed condition to prevent buffer overrun
        temp = word[val];
        if (temp == 128) { // se il carattere è € diventa spazio
            temp = 32;
        }
        temp = temp - 1;  // Fixed the temp-- issue
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

char *lett(char file[], char *var) {
    static char let[MAXWORD];  // Made static to prevent returning local variable
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
    while (!fileLet.eof() && i < MAXWORD - 1) {  // Prevent buffer overflow
        fileLet.get(let[i]);
        if (!fileLet.eof()) {  // Don't print EOF character
            cout << let[i];
            i++;
        }
    }
    let[i] = '\0';  // Null terminate the string
    fileLet.close();
    return let;
}

int Scritura(char *testo) {
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
    if (!Salvafile) { // Check if file opened successfully
        logAp("Errore di Scrittura su File");
        return 1;
    }
    
    Salvafile << testo;
    for (int aggiunta = 0; aggiunta < 50; aggiunta++) {
        printf("#");
        SLEEP_MS(20);
    }
    
    Salvafile.close();
    logAp("Scrittura riuscita");
    return 0;
}

void logAp(const char *testo) {
    time_t data;
    struct tm *datainfo;
    data = time(NULL);
    datainfo = localtime(&data);
    
    ofstream Salvafile("log.txt", ios::app);  // Append mode to preserve previous logs
    if (Salvafile) {
        Salvafile << "[" << (datainfo->tm_year + 1900) << "\\" 
                  << (datainfo->tm_mon + 1) << "\\" << (datainfo->tm_mday) 
                  << "\\ " << (datainfo->tm_hour) << ":" << (datainfo->tm_min) 
                  << "] " << testo << "\n" << endl;
        Salvafile.close();
    }
    return;
}