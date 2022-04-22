#pragma once
#include <windows.h>
#include <conio.h>
#include <fstream>

//use arrow keys for moving
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;

//Color text (choose from 1 to 16 colors)
void SetColor(WORD color);

//Color background (choose from 1 to 16 colors)
void SetBGColor(WORD color);


//Clear the screen (only with WindowsAPI)
void clrscr(void);

//Move the cursor to select(x: column,  y: row)
void gotoxy(short x, short y);

//Get the text data of the console and return the current text data
WORD textAttr();

//Reset the attribute of the console
void resetTextAttr();

//Color the text and its own background based on the position
void setColorBGTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, ...);


//true/false to show/hide the cursor
void ShowConsoleCursor(bool showFlag);
