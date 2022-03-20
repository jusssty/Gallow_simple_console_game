#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "windows.h"
#define G_CLR SetConsoleTextAttribute(hConsole, 10);
#define R_CLR SetConsoleTextAttribute(hConsole, 4);
#define B_CLR SetConsoleTextAttribute(hConsole, 9);
#define Y_CLR SetConsoleTextAttribute(hConsole, 14);
#define P_CLR SetConsoleTextAttribute(hConsole, 13);

using namespace std;

const int QI = 28, ATT = 9;
char gal[6][6];
vector <string> words = {"FATHER", "MOTHER", "PROGRAMMER", "IN", "MATH", "ANONIMYS", "GATES", "SPOON", "ARKASHA", "PAPICH", "DOTA", "HTML", "PYTON", "ITMO",
		     			 "LIPTON", "TIKTOK", "CHOICE", "LORDRENTO", "JONGL", "CSGO", "POSTAL", "HOTEL", "TRONE", "RESPONSE", "CAP", "CAT", "ALONE", "BEER"};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void sw(int tr) {
	switch(tr) {
		case 1:
			for (int i = 1; i < 6; i++) gal[i][0] = '|';
			break;
		case 2:
			gal[0][0] = '+';
			for (int i = 1; i < 5; i++) gal[0][i] = '-';
			break;
		case 3:
			gal[1][4] = '|';
			break;
		case 4:
			gal[2][4] = 'o';
			break;
		case 5:
			gal[3][4] = '|';
			break;
		case 6: 
			gal[3][3] = '/';
			break;
		case 7:
			gal[3][5] = '\\';
			break;
		case 8:
			gal[4][3] = '/';
			break;
		case 9:
			gal[4][5] = '\\';
			break;
	}
	return;
}

void game() {
	Y_CLR;
	system("cls");
	string word, prog, alph, endd; 
	alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	srand(time(0));
	word = words[rand() % (QI - 1)];
	endd = word;
	for (int i = 0; i < (int)word.size(); i++) prog.push_back('_');
	int tr = 0, shu = 0;
	for (int i = 0; i < 6; i++) 
		for (int j = 0; j < 6; j++) gal[i][j] = ' ';
	while (tr < ATT && shu < (int)prog.size()) {
		char letter;
		G_CLR;
		for (int i = 0; i < (int)prog.size(); i++) cout << prog[i] << ' ';
		cout << endl << "put any letter from this list:\n";
		B_CLR;
		for (int i = 0; i < (int)alph.size(); i++) cout << alph[i] << ' ';
		cout << endl;
		R_CLR;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) cout << gal[i][j];
			cout << endl;
		}
		P_CLR;
		cout << endl << ATT - tr << ' ' << "attempts remaining\n";
		cin >> letter;
		if (letter > 96 && letter < 123) letter -= 32;
		if (alph.find(letter) == alph.npos) {
			R_CLR;
			cout << "invalid character\n"; Sleep(500); tr++; system("cls");
			sw(tr);
			continue;
		} 
		int it = 0, cnt = 0;
		bool help = false; 
		while (word.find(letter, it) != word.npos) {
			help = true;
			prog[word.find(letter, it)] = letter;
			cnt++;
			word[word.find(letter, it)] = '0';
			if (cnt == 1) alph.erase(alph.begin() + alph.find(letter));
			if (word.find(letter, it) == word.npos) break; 
			else it = word.find(letter, it);
		}
		R_CLR;
		cout << (help == false ? "opps, u missed :(\n" : "nice! good job!");
		if (help == false) {
			tr++; 
			alph.erase(alph.begin() + alph.find(letter));
			sw(tr);
		}
		else shu += cnt;
		Sleep(500);
		system("cls");
	}
	if (shu == (int)prog.size()) {
		Y_CLR;
		cout << "congratulations, you have won!\nit was " << endd << endl;
		return;
	}
	else {
		R_CLR;
		cout << "unfortunately, you lost. try again\nit was " << endd << endl;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) cout << gal[i][j];
			cout << endl;
		}
		return;
	}
}

int main() {
	while (true) {
		Y_CLR;
		int act;
		cout << "1) play game; 2) exit;\n";
		cin >> act;
		if (act == 1) {
			system("cls");
			game();
			continue;
		}
		if (act == 2) {
			cout << "Goodbye!\n";
			goto ext;
		}
		else {
			cout << "I have nothing to do...\n";
			ext:
				system("pause");
				CloseHandle(hConsole);
				return 0;
		}
	}
	return 0;
}