#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include <string.h>

/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

//create board
char **board(int n) {
	char** t = new char* [n];
	for (int i = 0; i < n; i++){
		t[i] = new char[n];
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			t[i][j] = '0';
	}
	return t;
	}

//copy 2 places bigger than original
char** copy_2(char** t, int n, int checkvalue) {
	char** copy = new char* [n + 2];
	for (int i = 0; i < n + 2; i++)
	{
		copy[i] = new char[n + 2];
	}
	if (checkvalue == 2)
		for (int i = 0; i < n + 2; i++) {
			copy[i][0] = '2';
			copy[0][i] = '2';
			copy[i][n + 1] = '2';
			copy[n + 1][i] = '2';
		}
	if (checkvalue == 1)
		for (int i = 0; i < n + 2; i++) {
			copy[i][0] = '1';
			copy[0][i] = '1';
			copy[i][n + 1] = '1';
			copy[n + 1][i] = '1';
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			copy[i + 1][j + 1] = t[i][j];
		}
	return copy;
}

//beats stones
void beat(char** t, float& score1, float& score2, int n, int checkvalue, int &a) {
	char** copy = copy_2(t, n, checkvalue);
	if ((a==0)||a==2)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (copy[i][j] == '1')
					if ((copy[i - 1][j] == '2') && (copy[i + 1][j] == '2') && (copy[i][j - 1] == '2') && (copy[i][j + 1] == '2')) {
						t[i-1][j-1] = '0';
						score2 = score2 + 1;
					}
			}
	if ((a == 0) || a == 1)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (copy[i][j] == '2')
					if ((copy[i - 1][j] == '1') && (copy[i + 1][j] == '1') && (copy[i][j - 1] == '1') && (copy[i][j + 1] == '1')) {
						t[i - 1][j - 1] = '0';
						score1 = score1 + 1;
					}
			}
}

//draws board
void draw_board(int x_board, int y_board, int n, char **t) {
	textbackground(BLUE);
	y_board--;
	for (int i = 0; i < n - 1; i++) {
		y_board++;
		gotoxy(x_board, y_board);
		for (int j = 0; j < n - 1; j++) {
			if(t[i][j]=='0')
				cputs(" ");
			else if (t[i][j] == '1') {
				textcolor(0);
				cputs("@");
			}
			else if (t[i][j] == '2') {
				textcolor(15);
				cputs("@");
			}
			textcolor(7);
			cputs("---");
		}
		if (t[i][n - 1] == '0')
			cputs(" ");
		else if (t[i][n - 1] == '1') {
			textcolor(0);
			cputs("@");
		}
		else if (t[i][n - 1] == '2') {
			textcolor(15);
			cputs("@");
		}

		y_board++;
		gotoxy(x_board, y_board);
		for (int j = 0; j < n; j++) {
			textcolor(7);
			putch('|');
			if (j == n - 1)
				break;
			cputs("   ");
		}
	}
	y_board++;
	gotoxy(x_board, y_board);
	for (int j = 0; j < n - 1; j++) {
		if (t[n - 1][j] == '0')
			cputs(" ");
		else if (t[n - 1][j] == '1') {
			textcolor(0);
			cputs("@");
		}
		else if (t[n - 1][j] == '2') {
			textcolor(15);
			cputs("@");
		}
		textcolor(7);
		cputs("---");
	}
if (t[n - 1][n - 1] == '0')
cputs(" ");
else if (t[n - 1][n - 1] == '1') {
	textcolor(0);
	cputs("@");
}
else if (t[n - 1][n - 1] == '2') {
	textcolor(15);
	cputs("@");
}
}

//places stone on board
void place_stone(int x_board, int y_board, int x, int y, int n, char** t, int color, int checkvalue, int &a, unsigned int& ko) {
	char** copy = copy_2(t, n, checkvalue);
	int place_x = (x - x_board) / 4;
	int place_y = (y - y_board) / 2;
	char** check = board(n);
	check = t;
	char** check_copy = copy_2(check, n, checkvalue);

	if (color == 1) {
		check_copy[place_y + 1][place_x + 1] = '1';
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (check_copy[i][j] == '2')
					if ((check_copy[i - 1][j] == '1') && (check_copy[i + 1][j] == '1') && (check_copy[i][j - 1] == '1') && (check_copy[i][j + 1] == '1')) {
						check_copy[i][j] = '0';
					}
			}
		if (((copy[place_y][place_x + 1] == '2') && (copy[place_y + 2][place_x + 1] == '2') && (copy[place_y + 1][place_x] == '2') && (copy[place_y + 1][place_x + 2] == '2')) && ((check_copy[place_y][place_x + 1] == '0') || (check_copy[place_y + 2][place_x + 1] == '0') || (check_copy[place_y + 1][place_x] == '0') || (check_copy[place_y + 1][place_x + 2] == '0'))&&(ko!=1)) {
			t[place_y][place_x] = '1';
			a = 1;
			ko = 2;
		}
		else if (((copy[place_y][place_x + 1] == '0') || (copy[place_y + 2][place_x + 1] == '0') || (copy[place_y + 1][place_x] == '0') || (copy[place_y + 1][place_x + 2] == '0'))||((copy[place_y][place_x + 1] == '1') || (copy[place_y + 2][place_x + 1] == '1') || (copy[place_y + 1][place_x] == '1') || (copy[place_y + 1][place_x + 2] == '1')))
			t[place_y][place_x] = '1';
	}

	if (color == 2) {
		check_copy[place_y + 1][place_x + 1] = '2';
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (check_copy[i][j] == '1')
					if ((check_copy[i - 1][j] == '2') && (check_copy[i + 1][j] == '2') && (check_copy[i][j - 1] == '2') && (check_copy[i][j + 1] == '2')) {
						check_copy[i][j] = '0';
					}
			}
		if (((copy[place_y][place_x + 1] == '1') && (copy[place_y + 2][place_x + 1] == '1') && (copy[place_y + 1][place_x] == '1') && (copy[place_y + 1][place_x + 2] == '1')) && ((check_copy[place_y][place_x + 1] == '0') || (check_copy[place_y + 2][place_x + 1] == '0') || (check_copy[place_y + 1][place_x] == '0') || (check_copy[place_y + 1][place_x + 2] == '0'))&&(ko!=1)) {
			t[place_y][place_x] = '2';
			a = 2;
			ko = 2;
		}

		else if (((copy[place_y][place_x + 1] == '0') || (copy[place_y + 2][place_x + 1] == '0') || (copy[place_y + 1][place_x] == '0') || (copy[place_y + 1][place_x + 2] == '0'))||((copy[place_y][place_x + 1] == '2') || (copy[place_y + 2][place_x + 1] == '2') || (copy[place_y + 1][place_x] == '2') || (copy[place_y + 1][place_x + 2] == '2')))
			t[place_y][place_x] = '2';
	}
}

int main() {
	unsigned int ko = 0; // check if ko was played
	float score1 = 0, score2 = 0; //players score
	int n = 0; // size of board
	int zn = 0, x = 50, y = 1, attr = 7, back = 0, zero = 0, a = 0;
	char txt[32]; //array to print txt coursor position
	char p1[30];
	char p2[30]; //arrays to print players points
	int old_x = 0; 
	int old_y = 0; //previous position xy of 
	int color = 0; //intiger to change colors
	char** t = board(n); //board creation
	char fname[20];
	int handicap = 0;  //is handicap on
	int end_hendicap = 0; //has handicap ended
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("Jakub Gumkowski, 193036");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	do {
		// we set black to be the background color
		// check conio2.h for available colors
		textbackground(BLACK);
		// clear the screen: we fill it out with spaces with
		// the specified background color
		clrscr();
		// we set the text color (7 == LIGHTGRAY)
		textcolor(7);
		// we move the coursor to column 48 and row 1
		// rows and column are numbered starting with 1
		gotoxy(1, 1);
		// we print out a text at a given cursor position
		// the cursor will move by the length of the text
		cputs("Jakub Gumkowski, nr. 193036");
		gotoxy(1, 2);
		cputs("q     = quit game");
		gotoxy(1, 3);
		cputs("n     = start a new game");
		gotoxy(1, 4);
		cputs("enter = confirm your choice");
		gotoxy(1, 5);
		cputs("esc   = cancel current action");
		gotoxy(1, 6);
		cputs("i     = place a stone");
		gotoxy(1, 7);
		cputs("s     = save the game state");
		gotoxy(1, 8);
		cputs("l     = load the game state");
		sprintf(p1, "player1 points: %.1f", score1);
		gotoxy(1, 11);
		cputs(p1);
		sprintf(p2, "player2 points: %.1f", score2);
		gotoxy(1, 12);
		cputs(p2);
		// print out the position on board
		sprintf(txt, "postion: %i, %i", ((x - 50) / 4) + 1, ((y - 1) / 2) + 1);
		gotoxy(1, 14);
		cputs(txt);
		//prints information about hendicap
		if (end_hendicap == 0) {
			gotoxy(1, 9);
			cputs("h     = hendicap(to end press esc)");
		}

		//if board is above 0
		if (n > 0) {
			//place stone
			if ((zn == 'i') && (t[(y - 1) / 2][(x - 50) / 4] == '0')&&(handicap==0)) {
				if ((old_x != -1) && (old_y != -1))
					if ((t[old_y][old_x] == '1') || (t[old_y][old_x] == '2'))
						t[old_y][old_x] = '0';
				if (color == 0)
					place_stone(50, 1, x, y, n, t, 1, 2, a, ko);
				else
					place_stone(50, 1, x, y, n, t, 2, 1, a, ko);
				old_x = (x - 50) / 4;
				old_y = (y - 1) / 2;
				end_hendicap = 1;
			}

			//confirm decision
			if ((zn == 0x0d) && (old_x != -1) && (old_y != -1) && (handicap == 0)) {
				if ((t[old_y][old_x] == '1') || (t[old_y][old_x] == '2')) {
					if (color == 1)
						color = 0;
					else
						color = 1;
				}
				if (ko > 0)
					ko--;
				old_x = -1;
				old_y = -1;
				beat(t, score1, score2, n, 1, a);
				beat(t, score1, score2, n, 2, a);
				a = 0;
				sprintf(p1, "player1 points: %.1f", score1);
				gotoxy(1, 11);
				cputs(p1);
				sprintf(p2, "player2 points: %.1f", score2);
				gotoxy(1, 12);
				cputs(p2);
			}

			//hendicap
			if ((zn == 'h') && (end_hendicap==0)) 
				handicap = 1;
			if (handicap == 1) {
				if ((zn == 'i') && (t[(y - 1) / 2][(x - 50) / 4] == '0')) {
					if ((old_x != -1) && (old_y != -1))
						if ((t[old_y][old_x] == '1'))
							t[old_y][old_x] = '0';
					place_stone(50, 1, x, y, n, t, 1, 2, a, ko);
					old_x = (x - 50) / 4;
					old_y = (y - 1) / 2;
				}
				if ((zn == 0x0d) && (old_x != -1) && (old_y != -1)) {
					if ((t[old_y][old_x] == '1') || (t[old_y][old_x] == '2')) {

						old_x = -1;
						old_y = -1;
					}
				}
				if (zn == 0x1B) {
					handicap = 0;
					end_hendicap = 1;
				}
				if (end_hendicap == 1)
					color = 1;
			}
		}

		//starts new game
		if (zn == 'n') {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					t[i][j] = '0';
			score1 = 0;
			score2 = 0;
			n = 0;
			end_hendicap = 0;
		}

		//choose size of board
		if(n==0 || zn=='n') {
			gotoxy(1, 15);
			cputs("choose board size:");
			gotoxy(1, 16);
			cputs("1     = 9x9");
			gotoxy(1, 17);
			cputs("2     = 13x13");
			gotoxy(1, 18);
			cputs("3     = 19x19");
			gotoxy(1, 19);
			cputs("4     = custom size(type number)");
			if (zn == 0x31) {
					n = 9;
					t = board(n);
			}
			if (zn == 0x32) {
				n = 13;
				t = board(n);
			}
			if (zn == 0x33) {
				n = 19;
				t = board(n);
			}
			if (zn == 0x34) {
				gotoxy(1,21);
				cputs("type size of board:");
				char size[10] = { 0 };
				for (int i = 0; i < 10; i++) {
					char sizeT;
					sizeT = getch();
					if (sizeT == 0x0d)
						break;
					size[i] = sizeT;
					putch(size[i]);
				}
				const char* wsk = size;
				n = atoi(wsk);
				t = board(n);
			}
		}

		//save game to a file
		if (zn == 's') {
			gotoxy(1, 21);
			cputs("name your file: ");
			char filename[64] = { 0 };
			for (int i = 0; i < 64; i++) {
				char file_T;
				file_T = getch();
				if (file_T == 0x0d)
					break;
				filename[i] = file_T;
				putch(filename[i]);
			}
			strcat(filename, ".txt");
			FILE* pFile = fopen(filename, "w");
			fprintf(pFile, "%d\r%f\r%f\r", n, score1, score2);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					fprintf(pFile, "%c", t[i][j]);
			fclose(pFile);
		}

		//load a file
		if (zn == 'l') {
			gotoxy(1, 21);
			cputs("type your saved file name: ");
			char filename[64] = { 0 };
			for (int i = 0; i < 64; i++) {
				char file_T;
				file_T = getch();
				if (file_T == 0x0d)
					break;
				filename[i] = file_T;
				putch(filename[i]);
			}
			strcat(filename, ".txt");
			FILE* pFile = fopen(filename, "r");
			fscanf(pFile, "%d\r%f\r%f\r", &n, &score1, &score2);
			t = board(n);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					fscanf(pFile, "%c", &t[i][j]);
			fclose(pFile);
		}

		//draw a board
		if(n != 0)
			draw_board(50, 1, n, t);

		// we draw a star
		gotoxy(x, y);
		textcolor(attr);
		textbackground(RED);
		// putch prints one character and moves the cursor to the right
		putch('@');
		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		zero = 0;
		zn = getch();
		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if(zn == 0) {
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if(zn == 0x48 && y>1) y-=2;	// will be a special key
			else if(zn == 0x50 && y<(n*2)-1) y+=2;
			else if(zn == 0x4b && x>50) x-=4;
			else if(zn == 0x4d && x<48+(n+(3*(n-1)))) x+=4;
		} else if(zn == ' ') attr = (attr + 1) % 16;
		//else if(zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
					// visible after the program ends
	gotoxy(1, 30);

	return 0;
}
