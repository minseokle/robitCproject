#include"game.h"


char playername[2][10] = { "player1","player2" };

void consol_clear()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(COUT, ' ', 80 * 80, Coor, &dw);
}
void gotocurserXY(int x, int y) 
{
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
				clock_t start = clock();
				for (; rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED;)
				{
					ReadConsoleInput(CIN, &rec, 1, &dwNOER);
				}
				int cnt = clock() - start;
				if (cnt < 300)
				{
					return;
				}
			}

		}
	}

}
void Mouse_drag()
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

void Color_set(int color) 
{
	SetConsoleTextAttribute(COUT, color);
}


void Print_Message(char* mas)
{
	Color_set(WHITE);
	gotocurserXY(1, 19);
	printf("%s", mas);
}

void player_change()
{
	if (player == 1)
	{
		player = 2;
		Color_set(WHITE);
		gotocurserXY(1, 19);
		printf("%s차례         \n",playername[1]);
		printf("                             \n");
		printf("                             \n");
		printf("                             \n");
	}
	else
	{
		player = 1;
		Color_set(WHITE);
		gotocurserXY(1, 19);
		printf("%s차례          \n", playername[0]);
		printf("                             \n");
		printf("                             \n");
		printf("                             \n");
	}
}