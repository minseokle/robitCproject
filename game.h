#ifndef game
#define game
#include<stdio.h>
#include<Windows.h>
#include<time.h>

#define CIN GetStdHandle(STD_INPUT_HANDLE)
#define COUT GetStdHandle(STD_OUTPUT_HANDLE)
#define RED 4
#define BLUE 1
#define WHITE 7 
#define YELLOW 6

INPUT_RECORD rec;
DWORD	dwNOER;
DWORD mode;

char playername[2][10];

int player;
int mouse_x;
int mouse_y;

void gotocurserXY(int x, int y);
void Mouse_Able();
void Mouse_Check();
void Mouse_drag();
void Color_set(int color);
void Print_Message(char* mas);
void player_change();
void consol_clear();

#endif // !1
