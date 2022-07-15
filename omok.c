#include"Omok.h"


int Omok_board[19][19] = { 0, };



int Omok_start()
{
	player = 1;
	Color_set(WHITE);
	gotocurserXY(1, 19);
	printf("%s차례              ", playername[0]);
	Omok_board_set(18, 18);
	while (1)
	{
		Omok_stone_down();
		int win = Omok_end();
		if (win != 0)
		{
			return win;
		}
		player_change();
	}
}



void Omok_board_set(int c, int r)
{
	gotocurserXY(0, 0);
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[12];
	for (i = 1; i < 12; i++)
	{
		b[i] = 0xa0 + i;
	}
	printf(" %c%c ", a, b[3]);
	for (i = 0; i < c - 1; i++)
	{
		printf("%c%c ", a, b[8]);
	}
	printf("%c% c", a, b[4]);
	printf("\n");
	for (i = 0; i < r - 1; i++)
	{
		printf(" %c%c ", a, b[7]);
		for (j = 0; j < c - 1; j++)
		{
			printf("%c%c ", a, b[11]);
		}
		printf("%c%c ", a, b[9]);
		printf("\n");
	}
	printf(" %c%c ", a, b[6]);
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
			Omok_board[i][j] = 0;
		}
	}
}

void Omok_stone_down()
{
	int c3, c4, ob;
	do
	{
		int x, y;
		do
		{
			do
			{
				Mouse_Check();
			} while (!(mouse_x % 2 == 1 && mouse_x <= 37 && mouse_y >= 0 && mouse_y <= 18 && mouse_x >= 1));
			x = mouse_x / 2;
			y = mouse_y;
		} while (Omok_board[y][x] != 0);
		int dx[8] = { 1,-1,0,0,1,-1,1,-1 };
		int dy[8] = { 0,0,1,-1,1,-1,-1,1 };
		c3 = 0, c4 = 0, ob = 0;
		for (int k = 0; k < 8; k++)
		{
			int cnt = 0;
			for (int i = y + dy[k], j = x + dx[k]; Omok_board[i][j] == player && i < 19 && i >= 0 && j < 19 && j >= 0; i += dy[k], j += dx[k], cnt++);
			k++;
			for (int i = y + dy[k], j = x + dx[k]; Omok_board[i][j] == player && i < 19 && i >= 0 && j < 19 && j >= 0; i += dy[k], j += dx[k], cnt++);
			if (cnt == 3)
			{
				c4++;
			}
			if (cnt == 2)
			{
				c3++;
			}
			if (cnt > 4)
			{
				ob = 1;
			}
		}
		Print_Message("잘못된 수 입니다.");
	} while (player == 1 && (c4 > 1 || c3 > 1 || ob == 1));

	gotocurserXY(mouse_x, mouse_y);
	char* stone[2] = { "○", "●" };
	printf("%s", stone[player - 1]);
	Omok_board[mouse_y][(mouse_x - 1) / 2] = player;
}

int Omok_check()
{
	int x = (mouse_x - 1) / 2;
	int y = mouse_y;
	int dx[8] = { 1,-1,0,0,1,-1,1,-1 };
	int dy[8] = { 0,0,1,-1,1,-1,-1,1 };
	for (int k = 0; k < 8; k++)
	{
		int cnt = 0;
		for (int i = y + dy[k], j = x + dx[k]; Omok_board[i][j] == player && i < 19 && i >= 0 && j < 19 && j >= 0; i += dy[k], j += dx[k], cnt++);
		k++;
		for (int i = y + dy[k], j = x + dx[k]; Omok_board[i][j] == player && i < 19 && i >= 0 && j < 19 && j >= 0; i += dy[k], j += dx[k], cnt++);
		if (cnt == 4)
			return 1;
	}
	return 0;
}

int Omok_end()
{
	if (Omok_check() == 1)
	{
		consol_clear();
		gotocurserXY(0, 0);
		printf("%s(이)가 승리하였습니다.\n마우스를 클릭하면 게임 선택화면을 이동합니다.", playername[player - 1]);
		Sleep(1000);
		Mouse_Check();
		consol_clear();
		return player;
	}
	return 0;
}
