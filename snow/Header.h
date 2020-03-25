#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <iomanip>

 
using namespace std;

bool game=TRUE;
char a[19][19];
int timer= 11;
int timerBullet = 2;
int lives = 0;
int scor = 0;
int n;
int m;
int ScorMaxim;
int ScorLast;

struct Sageata {
	int x;
	int y; 
	char s ;
	Sageata * next;
};

struct fulg {
	int x = 0;
	int y = 0;
	fulg* next;
};



fulg* nodpFulg, startFulg,* NodNouFulg;
Sageata* nodpSageata, startSageata, *NodNouSageata;

FILE* file;

void Afisare(char a[][19], int poz);
void Introduce(int* poz);
void Inceput();
void Fulgi();
void Sageti();
void Meniu();
void GameOver();





void Afisare(int poz) {
	
	//completarea tabloului cu spatii libere;
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++) {
			a[i][j] = ' ';
		}

	a[18][poz] = '@';

	//completarea matrici cu fulgi
	nodpFulg = startFulg.next;
	while (nodpFulg)
	{
		if ((nodpFulg->x > -1)&&(nodpFulg->x < 20)) {
			a[nodpFulg->y][nodpFulg->x] = '*';
			nodpFulg = nodpFulg->next;
		}
		else
		break;
	}

	//completez matricea cu sageti(glonte)
	nodpSageata = startSageata.next;
	while (nodpSageata)
	{
			a[nodpSageata->y][nodpSageata->x] = nodpSageata->s;
 		 	nodpSageata = nodpSageata->next;
	}
	system("CLS");
	//afisez
	cout << "Lives: " << lives << "  SCOR:" << scor << endl << endl;
	cout << "#####################\n";
	
	for (int i = 0; i < 19; i++) {
		cout << "#";
		
		for (int j = 0; j < 19; j++)
			cout << a[i][j];
		cout << "#\n";
	}

	cout << "#####################\n";	
}

void Introduce(int *poz) {
	//verifica daca sa apasat vro tasta;
	if (kbhit()) {
		switch (getch()) {

		case 75:
			if (*poz > 0) {
				(*poz)--;
			}
			break;

		case 77:
			if (*poz < 18) {
				(*poz)++;
			}
			break;

		case 32: 
			
			//Adaugam inca o sageata
			timerBullet = -888881;
			NodNouSageata = (Sageata*)malloc(sizeof(Sageata));
			NodNouSageata->next = startSageata.next;
			NodNouSageata->x = *poz;
			NodNouSageata->y = 18;
			NodNouSageata->s = '^';
			startSageata.next = NodNouSageata;
			break;
		
		case 27:game = FALSE; break;
		}		
	}
	
}

void Fulgi() {

	int g=0;
	time_t t;

	timer++;
	if (timer %11== 0) {//peste fiecare 11 tacturi se incrementeaza pozitilie fulgilor si se genereaza fulgi noi
		
		nodpFulg = startFulg.next;
		fulg* tempFulg = &startFulg;
		while(nodpFulg!=NULL) {

				if (nodpFulg->y <= 16) {
					nodpFulg->y++;
					nodpFulg = nodpFulg->next;
					tempFulg = tempFulg->next;
				}
				else {//cand fulgul ajunge jos se scade din vieti si se sterge fulgul
					tempFulg->next = nodpFulg->next;
					free(nodpFulg);
					lives--;
					nodpFulg = tempFulg->next;
						
				}
		}
		
		//generarea fulgilor
		srand((unsigned)(time(&t)));
		for (int i = 1; i <= 19; i++) {
			g = (rand() % 20); 
			if (g < n ) {//n reprezinta nivelul de complexitate
				
				NodNouFulg = (fulg*)malloc(sizeof(fulg));
				NodNouFulg->next = startFulg.next;
				NodNouFulg->x = i-1;
				NodNouFulg->y = 0;
				startFulg.next = NodNouFulg;
			}
		}
	}
	
}

void Sageti() {

	timerBullet++;
	if (timerBullet % 2 == 0) {//peste fiecare 2 tacturi se decrementeaza pozitia sagetii si se fac verificari

		nodpSageata = startSageata.next;
		Sageata* tempSageata = &startSageata;

		while (nodpSageata) {

			if (nodpSageata->y >= 0) {
				nodpSageata->y--;
				nodpSageata = nodpSageata->next;
				tempSageata = tempSageata->next;
			}
			else {//sageata se sterge din lista cand ajunge sus
				tempSageata->next = nodpSageata->next;
				free(nodpSageata);
				nodpSageata = tempSageata->next;
			}

		}


		nodpSageata = startSageata.next;
		Sageata* temporar = &startSageata;

		while (nodpSageata) {

			if (nodpSageata->s == 'X') {
				temporar->next = nodpSageata->next;
				free(nodpSageata);
				nodpSageata = temporar->next;
			}
			else {
				nodpSageata = nodpSageata->next;
				temporar = temporar->next;
			}
		}



		nodpSageata = startSageata.next;

		while (nodpSageata) {

			nodpFulg = startFulg.next;
			fulg* tempp = &startFulg;

			while (nodpFulg) {

				if (((nodpSageata->x) == (nodpFulg->x)) && ((nodpSageata->y) == (nodpFulg->y))) {//verific daca sunt fulgi si sageti cu aceiasi pozitie
					scor++;
					nodpSageata->s = 'X';
					tempp->next = nodpFulg->next;
					free(nodpFulg);
					nodpFulg = tempp->next;
				}
				else {
					nodpFulg = nodpFulg->next;
					tempp = tempp->next;
				}
			}

			nodpFulg = startFulg.next;
			tempp = &startFulg;

			while (nodpFulg) {
				if (((nodpSageata->x) == (nodpFulg->x)) && ((nodpSageata->y) == (nodpFulg->y-1))) {//verific daca a trecut vrun fulg de sageata   *  ->^
					scor++;                                                                        //                                             ^  ->*
 					nodpSageata->s = 'X';
					tempp->next = nodpFulg->next;
					free(nodpFulg);
					nodpFulg = tempp->next;
				}
				else {
					nodpFulg = nodpFulg->next;
					tempp = tempp->next;
				}
			
			}
			nodpSageata = nodpSageata->next;
		}
	}
}

void Inceput() {
	char c='x';
	int poz=9;

    lives = 3;
	scor = 0;
    n = 1;
	m = 50;

	startSageata.next = NULL;
	nodpSageata = &startSageata;

	startFulg.next = NULL;
	nodpFulg = &startFulg;

	cout << "Inceput\n";
	

	a[18][9] = '@';

	while ((game!=FALSE)&&(lives>0)) {
		Afisare(poz);
		Introduce(&poz);
		Introduce(&poz);//doua introduceri pentru a putea si da drumu la sageata si dea ma misca intrun singur tact.
		Fulgi();
		Sageti();
		Sleep(30);
		if (scor >= m)
		{
			n++;
			m = m + m;
		}

	}
	GameOver();
}


