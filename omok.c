#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>

#define CIN GetStdHandle(STD_INPUT_HANDLE) // 표준 입력 디바이스
#define COUT GetStdHandle(STD_OUTPUT_HANDLE)
#define RED 4
#define BLUE 1
#define WHITE 7 
#define YELLOW 6


INPUT_RECORD rec;
DWORD	dwNOER;
DWORD mode;

int game_board[19][19] = { 0, };
int mouse_x, mouse_y;
int player = 1;

void gotoMouseXY(int x, int y);
void Mouse_Able();
void Mouse_Check();
void setColor(int color);
void omok_board(int c, int r);
void omok_stone_down();
void omok_win();
void Error_Message(char* mas);
void player_change();

void main()
{
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	Mouse_Able();
	omok_board(18, 18);
	while (1)
	{
		omok_stone_down();
		player_change();
	}
}

void gotoMouseXY(int x, int y) {
	COORD cur;
	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void Mouse_Able()
{
	GetConsoleMode(CIN, &mode); // 현재 콘솔 입력 모드를 가져온다.
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT); // 마우스 입력을 허용한다.
}

void Mouse_Check()
{
	while (1)
	{
		ReadConsoleInput(CIN, &rec, 1, &dwNOER);
		if (rec.EventType == MOUSE_EVENT)
		{
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				mouse_x = rec.Event.MouseEvent.dwMousePosition.X;
				mouse_y = rec.Event.MouseEvent.dwMousePosition.Y;
				return;
			}

		}
	}
}

void setColor(int color) {
	SetConsoleTextAttribute(COUT, color);
}

void omok_board(int c, int r)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[12];
	for (i = 1; i < 12;
		i++)
		b[i]
		= 0xa0 + i;
	printf("%c%c ", a, b[3]);
	for (i = 0; i < c - 1; i++)
		printf("%c%c ", a, b[8]);
	printf("%c% c", a, b[4]);
	printf("\n");
	for (i = 0; i < r - 1; i++)
	{
		printf("%c%c ", a, b[7]);
		for (j = 0; j < c - 1; j++)
			printf("%c%c ", a, b[11]);
		printf("%c%c ", a, b[9]);
		printf("\n");
	}
	printf("%c%c ", a, b[6]);
	for (i = 0; i < c - 1; i++)
		printf("%c%c ", a, b[10]);
	printf("%c%c ", a, b[5]);
	printf("\n");
}

void Error_Message(char* mas)
{
	setColor(WHITE);
	gotoMouseXY(2, 21);
	printf("%s", mas);
}

void player_change()
{
	if (player == 1)
	{
		player = 2;
		Error_Message("플레이어2차례");
	}
	else
	{
		player = 1;
		Error_Message("플레이어1차례");
	}
}

void omok_stone_down()
{
	do
	{
		do
		{
			Mouse_Check();
		} while (!(mouse_x % 2 == 0 && mouse_x <= 36 && mouse_y>=0 && mouse_y <= 18 && mouse_x>=0));
	} while (game_board[mouse_y][(mouse_x ) / 2] != 0);
	
	gotoMouseXY(mouse_x, mouse_y);
	char* stone[2] = { "○", "●" };
	printf("%s",stone[player - 1]);
	game_board[mouse_y][(mouse_x) / 2] = player;
}

void omok_win()
{
	int x = mouse_x / 2;
	int y = mouse_y;
}
