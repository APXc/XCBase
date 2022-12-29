/*
Copyright
Project: XCBase
Author: Alessio Pellizzaro <alessio.pellizzaro@apserial.it>
Github User: ApXc
Year: 2016
Version: 0.5
Nation: Italy

commercial use not authorized
*/

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fstream> 
#include <iostream>
#include <time.h>




#define Max_word 122 //massimo di lettura 
#pragma warning(disable : 4996)

using namespace std;
char *xcIn(char*);
char *xcOt(char*);
char *lett(char file[], char*);
int Scritura(char *testo);
void logAp(const char*);



int main(int argc, char *argv[]) {

	int aggiunta;
	int menu;
	char Maxparola[Max_word];
	printf(ITTitolo);
	char *string;
	int scr = 3;
	char *dat;
	cout << "Selezionare Menu" << endl;
	Sleep(5);
	cout << "Criptaggio(1), DeCriptaggio(2), Gestione da File(3)" << endl;
	logAp("avvio Programma Coretto");
	cin >> menu;
	switch (menu){
		case 1:
			logAp("selezionato menu 1 per criptaggio\n");
			cout << "inserisci la parola\n" << endl;
			scanf_s("%s", &Maxparola, sizeof(Maxparola));
			string = xcIn(Maxparola);
			for (aggiunta = 0; aggiunta < 50; aggiunta++) {
				printf("#");
				Sleep(20);
			}
			printf("\n%s\n\n", string);
			scr = Scritura(string);
			if (scr != 0) {
				printf_s("\nImposibile salvare in report\n");
				logAp("Imposibile salvare in report\n");
			}
			else {
				printf_s("\nScrittura file riuscita\n");
				logAp("Scrittura file riuscita\n");
			}
			break;
		case 2:
			logAp("Selezionato Menu per Decriptaggio\n");
			cout << "inserisci la parola" << endl;
			scanf_s("%s", &Maxparola, sizeof(Maxparola));
			string = xcOt(Maxparola);
			for (aggiunta = 0; aggiunta < 50; aggiunta++) {
				printf("#");
				Sleep(20);
			}
			printf("\n%s\n\n", string);
			scr = Scritura(string);
			if (scr != 0) {
				printf_s("Imposibile salvare in report\n");
				logAp("Imposibile salvare in report\n");
			}
			else {
				printf_s("Scrittura file riuscita\n");
				logAp("Scrittura file riuscita\n");
			}
			break;
		case 3:
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
			char text = *risul;
			printf_s("\n%s\n", &risul);
			int sel = 0;
			char *texte;
			printf_s("Criptare Testo(1) o DeCrptare Testo(2)?\n");
			cin >> sel;
			if (sel == 1) {
				texte = xcIn(risul);
				for (int aggiunta = 0; aggiunta < 50; aggiunta++) {
					printf("#");
					Sleep(20);
				}
				printf("\n%s\n\n", texte);
				scr = Scritura(texte);
				if (scr != 0) {
					printf_s("Imposibile salvare in report\n");
					logAp("Imposibile salvare in report\n");
				}
				else {
					printf_s("Scrittura file riuscita\n");
					logAp("Scrittura file riuscita\n");
				}
			}
			else if (sel == 2) {
				texte = xcOt(risul);
				for (int aggiunta = 0; aggiunta < 50; aggiunta++) {
					printf("#");
					Sleep(20);
				}
				printf("\n%s\n\n", texte);
				scr = Scritura(texte);
				if (scr != 0) {
					printf_s("Imposibile salvare in report\n");
					logAp("Imposibile salvare in report\n");
				}
				else {
					printf_s("Scrittura file riuscita\n");
					logAp("Scrittura file riuscita\n");
				}

			}
			else {
				return -1;
			}
			
			break;
	}


	return 0;
}

char *xcIn(char* word) {
	int val = 0;
	int carateri = strlen(word);
	int temp;
	cout << "Criptaggio in corso" << endl;
	logAp("Criptaggio in corso....");
	while (val <= carateri) {
		temp = word[val];
		if (temp == 32) { //se il carater è spazio divente €
			temp = 128;
		}
		temp = temp++;
 		if (temp == 126 || temp > 126) { //se il caratere e ~ porta a !
			temp = 33;
			
		}
		else if (temp == 32 || temp < 32) { //se il careterew è spazio porta a ù 
		    temp = 249;
			
		}
		else {
			
		}
		word[val] = temp;
		val++;
		int *fp = &val;
		if (val == 0) {
			*fp = 1;
			continue;
		}
		//else
		//{
		//	/*cout << word[val] << endl;*/
		//	continue;
		//}
	}


	return word;
}

char *xcOt(char* word) {
	int val = 0;
	int carateri = strlen(word);
	int temp;
	cout << "deCriptaggio in corso" << endl;
	logAp("DeCriptaggio in corso....");
	while (val <= carateri) {
		temp = word[val];
		//cout << "ciclo " + val << endl;
		if (temp == 128) { //se il carater è spazio divente €
			temp = 32;
		}
		/*cout << temp << endl;*/
		temp = temp--;
		if (temp == 33 || temp < 33) { //se il caratere e ~ porta a !
			temp = 126;

		}
		else if (temp == 249 || temp > 249) { //se il careterew è spazio porta a ù 
			temp = 32;

		}
		
		word[val] = temp;
		val++;
		int *fp = &val;
		if (val == 0) {
			*fp = 1;
			continue;
		}
		
	}
	return word;
}



char *lett(char file[], char *var) {
	ifstream fileLet;
	cout << "lettura file in corso" << endl;
	logAp("lettura file in corso");
	fileLet.open(file, ifstream::in);
	if (!fileLet) {
		printf_s("Errore di Lettura di file imposibile continuare");
		logAp("Errore di Lettura");
		return NULL;
	}
	//char ch;
	char let[MAXWORD];
	int i = 0;
	/*for (int agg = 0; agg < MAXWORD; agg++) {
		fileLet.get(let[i]);
		cout << let[i];
		i++;
	}*/
	while (!fileLet.eof()) {
		fileLet.get(let[i]);
		cout << let[i];
		i++;
	}
	*var = *let;
	fileLet.close();
	return let;
}


int Scritura(char *testo) {
	int alfa = 0;
	time_t data;
	tm *datainfo;
	data=time(NULL);
	datainfo = localtime(&data);
	printf("\nScritura su File\n");
	logAp("Scritura su File");
	cout << (datainfo->tm_year+1900) << "\\"<< (datainfo->tm_mon+1) << "\\" << (datainfo->tm_mday) << "\\ " << (datainfo->tm_hour) <<":" << (datainfo->tm_min) << endl;
	//int dl[] = { (datainfo->tm_year),(datainfo->tm_mon) ,(datainfo->tm_mday), (datainfo->tm_hour) };
	ofstream Salvafile("report.txt");
	Salvafile << testo;
	for (int aggiunta = 0; aggiunta < 50; aggiunta++) {
		printf("#");
		Sleep(20);
	}
	if (!Salvafile) {//in caso di errore restituisce 1
		logAp("Erorre di Scritura su File");
		return 1;
	}
	Salvafile.close();
	logAp("Scritura riuscita");
	return 0;
}

void logAp( const char *testo) {
	int alfa = 0;
	time_t data;
	tm *datainfo;
	data = time(NULL);
	datainfo = localtime(&data);
	char sec = (datainfo->tm_sec);
	/*ifstream letturafile("log.txt");
	char let[];
	int i = 0;
	while (!letturafile.eof()) {
		letturafile.get(let[i]);
		i++;
	}
	letturafile.close();*/
	ofstream Salvafile("log.txt");
	//Salvafile << let;
	Salvafile <<"["<<(datainfo->tm_year + 1900) << "\\" << (datainfo->tm_mon + 1) << "\\" << (datainfo->tm_mday) << "\\ " << (datainfo->tm_hour) << ":" << (datainfo->tm_min)<<"]"<< testo <<"\n"<<endl;
	Salvafile.close();
	return;
}


