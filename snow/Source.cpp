 
#include "MeniuGameOver.h"
#include <stdlib.h>




using namespace std;

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void main() {
	system("mode con lines=24 cols=21");
	hidecursor();
	Meniu();	
}