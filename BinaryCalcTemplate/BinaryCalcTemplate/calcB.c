#include <stdlib.h>
#include <stdio.h>
#include "ConsoleTools.h"
#include "calcB.h"
#include <locale.h>

//
//	Auteur : Pascal RICQ
//	version projet :  1.0
//  date 26 sept 2019
//	remarque : développement … vocation pédagogique
//	public : néophytes


COORD org = { POSX,POSY };
char allKey[] = "()wW0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMmNoOqQrRsStTuUwWyxXYzZ+-*/=<.\n\r";

int main(int argc, char* argv[]) {
	//system("CHCP 850");
	//printf("\nsetlocale : %s\n", setlocale(LC_ALL, ".850")); /* option de localisation pour les caractères accentués  */


	// programme principale : Calculatrice Binaire
	// Objectif : reproduire la calculatrice  mode 'développeur' de Windows 10 pour la Console Windows.

	// étape I
	COORD pos = { 0,0 };
	OpenConsole();
  	afficherCalculatrice();

	char key;
	do {
		key = readChar(allKey);
		switch (key)
		{
		case '(':
			pos.X = POSXBRAOPEN; pos.Y = POSYBRAOPEN;
			blink(pos, 5, 3, 250);
			break;
		case ')':
			pos.X = POSXBRACLOS; pos.Y = POSYBRACLOS;
			blink(pos, 5, 3, 250);
			break;
		case 'w':
		case 'W' :
			pos.X = POSXSIGN; pos.Y = POSYSIGN;
			blink(pos, 5, 3, 250);
			break;
		case '0':
			pos.X = POSXZERO; pos.Y = POSYZERO;
			blink(pos, 5, 3, 250);
		break;
		case '1' :
			pos.X = POSXONE; pos.Y = POSYONE;
			blink(pos, 5, 3, 250);
			char val = 0b0110;
			COORD posVal = { 2 ,0 };
			dispBinaryValue(posVal, 30, true, (void*)& val, Byte);
			break;
		case '2':
			pos.X = POSXTWO; pos.Y = POSYTWO;
			blink(pos, 5, 3, 250);
			break;
		case '3':
			pos.X = POSXTHREE; pos.Y = POSYTHREE;
			blink(pos, 5, 3, 250);
			break;
		case '+':
			pos.X = POSXPLUS; pos.Y = POSYPLUS;
			blink(pos, 5, 3, 250);
			break;
		case 'x' :
		case 'X':
			clearScreen();
			break;
		case '\n':
		case '\r' :
		case '=' :
			pos.X = POSXEQUAL; pos.Y = POSYEQUAL;
			blink(pos, 5, 3, 250);
			evaluate();
		default:
			break;
		} 
		
	} while (key != 'x' && key != 'X');
	
	
	
	
	CloseConsole();
 }
int initCalc()
{
	currentBase = Dec;
	Op1Val_byte = 0;
	Op1Val_valid = true;

	return 0;
}
int clearScreen(void) {
	GotoXY(POSX, POSY);
	for (size_t i = 0; i < 32; i++)
	{
		printf_s("%80s","\n");
	}
	GotoXY(POSX, POSY);
	return 0;
}

int evaluate() {
	GotoXY(0,1);
	printf("%30s","processing..");
	return 0;
}
int dispBinaryValue(COORD pos, int maxLen, bool truncate, void *op, mode opSize ) {
	int c = pos.X;
	int l = pos.X;
	int nbBits = 8 * opSize;
	int mask = 1 << (nbBits - 1);
	bool start = false;
	switch (opSize) {
	case 1 :
		do {
			if (*(char*)op & mask) {
				//afficher le 1
				start = true;
				if (c >= maxLen) { c = pos.X; l++; }
				GotoXY(c, l);
				PlotChar('1');
				c++;
			}
			else {
				if (start) {
					// afficher le zéro si pas en tête
					if (c >= maxLen) { c = pos.X; l++; }
					GotoXY(c, l);
					PlotChar('0');
					c++;
				}
			}
			mask >> 1;
		} while (mask);
		break;
	default :
		break;
	}
	return 0;
}
int ajouterDigitDroite() {

}

// Affichage du dessin de la calculatrice
int afficherCalculatrice(void)
{
	GotoXY(POSX, POSY);
	printf("Calculatrice   Programmeur             M‚moire                                ");
	printf("\n                                                                            ");
	printf("\n                                                                            ");
	printf("\n(H)HEX                                                                      ");
	printf("\n                                                                            ");
	printf("\n(I)DEC                                                                      ");
	printf("\n                                                                            ");
	printf("\n(J)OCT                                                                      ");
	printf("\n                                                                            ");
	printf("\n(K)BIN                                                                      ");
	printf("\n                                                                            ");
	printf("\n                                                                            ");
	printf("\n QWORD   memory Store Get clYr                                              ");
	printf("\nÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿                                              ");
	printf("\n³Lsh³³Rsh³³ Or³³Xor³³noT³³aNd³                                              ");
	printf("\nÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙ                                              ");
	printf("\nÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿                                              ");
	printf("\n³ Up³³Mod³³ z ³³ Z ³³ < ³³ ö ³                                              ");
	printf("\nÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙ                                              ");
	printf("\nÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿                                              ");
	printf("\n³ A ³³ B ³³ 7 ³³ 8 ³³ 9 ³³ x ³                                              ");
	printf("\nÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙ                                              ");
	printf("\nÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿                                              ");
	printf("\n³ C ³³ D ³³ 4 ³³ 5 ³³ 6 ³³ - ³                                              ");
	printf("\nÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙ                                              ");
	printf("\nÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿                                              ");
	printf("\n³ E ³³ F ³³ 1 ³³ 2 ³³ 3 ³³ + ³                                              ");
	printf("\nÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙ                                              ");
	printf("\nÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿ÚÄÄÄ¿                                              ");
	printf("\n³ ( ³³ ) ³³ ñ ³³ 0 ³³ , ³³ = ³                                              ");
	printf("\nÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙÀÄÄÄÙ                                              ");
	
	return 0;
}

