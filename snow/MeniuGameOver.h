#include "Header.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void Meniu();
void GameOver();
void Afisare(int poz);

void Meniu() {
	bool statut = FALSE;
	int m = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char c;
	char scorM[5] = { ' ',' ',' ',' ',' ' };
	char scorL[5] = { ' ',' ',' ',' ',' ' };
	ScorMaxim = 0;
	ScorLast = 0;

	if ((file = fopen("scor.txt", "r")) != NULL) {
		fgets(scorM, 5, file);
		ScorMaxim = ScorMaxim + (scorM[0] - 48) * 1000;
		ScorMaxim = ScorMaxim + (scorM[1] - 48) * 100;
		ScorMaxim = ScorMaxim + (scorM[2] - 48) * 10;
		ScorMaxim = ScorMaxim + (scorM[3] - 48);
		fgetc(file);
		fgets(scorL, 5, file);

		fclose(file);
	}




	while (statut == FALSE) {
		system("CLS");
		game = TRUE;


		cout << "#####################\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		if (m == 0) {
			cout << "#     ";
			SetConsoleTextAttribute(hConsole, 12);
			cout << "S T A R T";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "     #\n";
			cout << "#                   #\n";
			cout << "#      E X I T      #\n";
		}
		else {
			cout << "#     S T A R T     #\n";
			cout << "#                   #\n";
			cout << "#      ";
			SetConsoleTextAttribute(hConsole, 12);
			cout << "E X I T";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "      #\n";
		}
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#      B E S T      #\n";
		cout << "#                   #\n";
		cout << "#      S C O R      #\n";
		cout << "#                   #\n";
		cout << "#       ";
		cout << scorM;
		cout << "        #\n";
		cout << "#                   #\n";
		cout << "#                   #\n";
		cout << "#  Last Scor: ";
		cout << scorL << "  #\n";
		cout << "#                   #\n";
		cout << "#####################\n";

		if ((c = getch()) == 80)
			if (m == 0)
				m = 1;

		if (c == 72)
			if (m == 1)
				m = 0;

		if ((c == 13) || (c == 32)) {
			if (m == 1)exit(0);
			if (m == 0)Inceput();
		}

	}

}

void GameOver() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Sleep(500);
	system("CLS");
	cout << "#####################\n";
	cout << "#  X      X   x     #\n";
	cout << "#   X    x     X    #\n";
	cout << "#          x        #\n";
	cout << "#      X         x  #\n";
	cout << "#  xX     x    xxx  #\n";
	cout << "#X      x       X   #\n";
	cout << "#      ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "G A M E";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "      #\n";
	cout << "#  XX     x     XX  #\n";
	cout << "#      ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "O V E R";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "      #\n";
	cout << "#  X     x     xx   #\n";
	cout << "#     X      X      #\n";
	cout << "#    x   X  x X     #\n";
	cout << "#  X   ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "S C O R";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "   X  #\n";
	cout << "#      X ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << left;
	cout << setw(4) << scor;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "  x    #\n";
	cout << "#   X     x     X   #\n";
	cout << "#  X       x x   X  #\n";
	cout << "#     X      X      #\n";
	cout << "#      X         x  #\n";
	cout << "#  xX     x    xxx  #\n";
	cout << "#X      x       X   #\n";
	cout << "#   X   x      X    #\n";
	cout << "#####################\n";
	
	Sleep(3000);
	while(getch()!=13);

	int scorl = scor;
	if (scor > ScorMaxim) {
		int p = 1000;
		file = fopen("scor.txt", "w");
		for (int i = 0; i < 4; i++) {
			fputc(48 + scor / p, file);
			scor = scor % p;
			p /= 10;
		}
		fputc('\n', file);
		p = 1000;
		for (int i = 0; i < 4; i++) {
			fputc(48 + scorl / p, file);
			scorl = scorl % p;
			p /= 10;
		}
		fclose(file);
	}
	else {
		int p = 1000;
		file = fopen("scor.txt", "w");
		for (int i = 0; i < 4; i++) {
			fputc(48 + ScorMaxim / p, file);
			ScorMaxim = ScorMaxim % p;
			p /= 10;
		}
		p = 1000;
		fputc('\n', file);
		for (int i = 0; i < 4; i++) {
			fputc(48 + scorl / p, file);
			scorl = scorl % p;
			p /= 10;
		}
		fclose(file);
	}
	Meniu();
}
