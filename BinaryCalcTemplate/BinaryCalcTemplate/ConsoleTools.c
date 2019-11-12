#include "ConsoleTools.h"

char readChar(const char* filtre) {

	char car = -1;
	char* tmp;
	while (car == -1) {
		car = 0;
		while (car == 0) car = (char)_getch();

		if ((tmp = strchr(filtre, car)) != NULL) {
			car = *tmp;
		}
		else car = -1;
	};
	return car;
}


int OpenConsole() {

	// Seed the random-number generator with the current time so that
	// the numbers will be different every time we run.
	srand((unsigned)time(NULL));


	// Get handles to STDIN and STDOUT. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE ||
		hStdout == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
			MB_OK);
		return 1;
	}
	// Save the current text colors. 

	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),
			TEXT("Console Error"), MB_OK);
		return 1;
	}

	wOldColorAttrs = csbiInfo.wAttributes;
	// Save the current consoleMode
	
	if (!GetConsoleMode(hStdout, &Mode))
	{
		MessageBox(NULL, TEXT("GetConsoleMode"),
			TEXT("Console Error"), MB_OK);
		return 1;
	}
	wOldMode = Mode;
	return(0);
}

int blink(COORD pos, DWORD length, DWORD heigth, DWORD duration) {
	WORD *oldAttrib;
	DWORD nbAttrib;
	WORD newAttrib;
	COORD pix = pos;
	// sauvegarde des attributs de chaque pixel
	oldAttrib = (WORD*) malloc(sizeof(WORD) * length * heigth);
	if (oldAttrib == NULL) return(1);
	for (size_t l = 0; l < heigth; l++)
	{
		for (size_t c = 0; c < length; c++)
		{
			int offset = (l * length + c);
			pix.X = pos.X + (short) c; pix.Y = pos.Y + (short)l;
			if (!ReadConsoleOutputAttribute(hStdout, oldAttrib + offset, 1, pix, &nbAttrib))
			{
				MessageBox(NULL, TEXT("ReadConsoleOutputAttribute"),
					TEXT("Console Error"), MB_OK);
				return 1;
			}
			else {
				newAttrib = *(oldAttrib + offset);
				newAttrib = newAttrib | COMMON_LVB_REVERSE_VIDEO;
				if (!WriteConsoleOutputAttribute(hStdout, &newAttrib, 1, pix, &nbAttrib))
				{
					MessageBox(NULL, TEXT("WriteConsoleOutputAttribute"),
						TEXT("Console Error"), MB_OK);
					return 1;
				}
			}
		}
	}

	Sleep(duration);
	pix = pos;
	for (size_t l = 0; l < heigth; l++)
	{
		for (size_t c = 0; c < length; c++)
		{
				int offset = (l * length + c);
				pix.X = pos.X + (short)c; pix.Y=pos.Y + (short) l;
				if (!WriteConsoleOutputAttribute(hStdout, oldAttrib + offset, 1, pix, &nbAttrib))
				{
					MessageBox(NULL, TEXT("WriteConsoleOutputAttribute"),
						TEXT("Console Error"), MB_OK);
					return 1;
				}
			
		}
	}
	free(oldAttrib);
	return 0;
}

int CloseConsole() {
	// Restore the original text colors. 

	SetConsoleTextAttribute(hStdout, wOldColorAttrs);
	return(0);
}


COORD GetConsoleSize() {
	COORD Size;

	Size.X = csbiInfo.dwSize.X;
	Size.Y = csbiInfo.dwSize.Y;
	return(Size);
}

void GotoXY(unsigned short int X, unsigned short int Y) {

	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(hStdout, pos);
	
	return;
}
int PlotChar(char SomeChar) {
	chBuffer[0] = SomeChar;
	chBuffer[1] = 0;
	cRead = 1;
	if (WriteFile(hStdout, chBuffer, cRead, &cWritten, NULL)) {
		return(0);
	}
	else {
		return(GetLastError());
	}
}

int RangedRand(int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	
		int u = (int) ((double)rand() / ((double)RAND_MAX + 1) * ((double)range_max - (double)range_min))   + range_min;	
	return(u);
}

