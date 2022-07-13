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

int omok_board[19][19] = { 0, };
int mouse_x, mouse_y;
int player = 1;

void consol_clear();
void gotocurserXY(int x, int y);
void Mouse_Able();
void Mouse_Check();
void Color_set(int color);
void omok_board_set(int c, int r);
void omok_stone_down();
int omok_check();
void omok_end();
void Error_Message(char* mas);
void player_change();

void main()
{
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	Mouse_Able();
	omok_board_set(18, 18);
	while (1)
	{
		omok_stone_down();
		omok_end();
		player_change();
	}
}


void consol_clear()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(COUT, ' ', 80 * 80, Coor, &dw);
}

void gotocurserXY(int x, int y) {
	COORD cur;
	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void Mouse_Able()
{
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
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

void Color_set(int color) {
	SetConsoleTextAttribute(COUT, color);
}

void omok_board_set(int c, int r)
{
	gotocurserXY(0, 0);
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[12];
	for (i = 1; i < 12; i++)
	{
		b[i] = 0xa0 + i;
	}
	printf("%c%c ", a, b[3]);
	for (i = 0; i < c - 1; i++)
	{
		printf("%c%c ", a, b[8]);
	}
	printf("%c% c", a, b[4]);
	printf("\n");
	for (i = 0; i < r - 1; i++)
	{
		printf("%c%c ", a, b[7]);
		for (j = 0; j < c - 1; j++)
		{
			printf("%c%c ", a, b[11]);
		}
		printf("%c%c ", a, b[9]);
		printf("\n");
	}
	printf("%c%c ", a, b[6]);
	for (i = 0; i < c - 1; i++)
	{
		printf("%c%c ", a, b[10]);
	}
	printf("%c%c ", a, b[5]);
	printf("\n");
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			omok_board[i][j] = 0;
		}
	}
}

void Error_Message(char* mas)
{
	Color_set(WHITE);
	gotocurserXY(2, 21);
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
		} while (!(mouse_x % 2 == 0 && mouse_x <= 36 && mouse_y >= 0 && mouse_y <= 18 && mouse_x >= 0));
	} while (omok_board[mouse_y][(mouse_x) / 2] != 0);

	gotocurserXY(mouse_x, mouse_y);
	char* stone[2] = { "○", "●" };
	printf("%s", stone[player - 1]);
	omok_board[mouse_y][(mouse_x) / 2] = player;
}

int omok_check()
{
	int x = mouse_x / 2;
	int y = mouse_y;
	int dx[8] = { 1,-1,0,0,1,-1,1,-1 };
	int dy[8] = { 0,0,1,-1,1,-1,-1,1 };
	for (int k = 0; k < 8; k++)
	{
		int cnt = 0;
		for (int i = y + dy[k], j = x + dx[k]; omok_board[i][j] == player && i < 19 && i >= 0 && j < 19 && j >= 0; i += dy[k], j += dx[k], cnt++);
		k++;
		for (int i = y + dy[k], j = x + dx[k]; omok_board[i][j] == player && i < 19 && i >= 0 && j < 19 && j >= 0; i += dy[k], j += dx[k], cnt++);
		if (cnt == 4)
			return 1;
	}
	return 0;
}

void omok_end()
{
	if (omok_check() == 1)
	{
		consol_clear();
		gotocurserXY(0, 0);
		printf("플레이어%d이 승리하였습니다.\n마우스를 클릭하면 다음판이 진행 됩니다.", player);
		Sleep(1000);
		Mouse_Check();
		consol_clear();
		omok_board_set(18, 18);
	}
}
