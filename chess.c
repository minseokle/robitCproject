#include"chess.h"

int x1, y1, x2, y2, piece, state, turnend;
int playtime[2];
char chess_board[17][17][5] =
{
	{"┌ ","─ ","┬ ","─ ","┬ ","─ ","┬ ","─ ","┬ ","─ ","┬ ","─ ","┬ ","─ ","┬ ","─ ","┐"},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"├ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┼ ","─ ","┤ "},
	{"│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│","   ","│",},
	{"└ ","─ ","┴ ","─ ","┴ ","─ ","┴ ","─ ","┴ ","─ ","┴ ","─ ","┴ ","─ ","┴ ","─ ","┘ "},

};

int chess_game1[8][8] =
{
	{11,21,31,41,51,31,21,11},
	{01,01,01,01,01,01,01,01},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{02,02,02,02,02,02,02,02},
	{12,22,32,42,52,32,22,12},
};

int chess_game[8][8] =
{
	{11,21,31,41,51,31,21,11},
	{01,01,01,01,01,01,01,01},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{02,02,02,02,02,02,02,02},
	{12,22,32,42,52,32,22,12},
};



int Chess_start()
{
	player = 1;
	Chess_Board();
	Color_set(WHITE);
	gotocurserXY(1, 19);
	printf("%s차례\n", playername[0]);
	playtime[0] = 600000;
	playtime[1] = 600000;
	gotocurserXY(1, 20);
	printf("%s 남은시간 %d분 %d초\n", playername[0], playtime[0] / 60000, (playtime[0] % 60000) / 1000);
	printf(" %s 남은시간 %d분 %d초\n", playername[1], playtime[1] / 60000, (playtime[1] % 60000) / 1000);
	while (1)
	{
		int start = (int)clock();
		Chess_Play();
		Chess_Board();
		playtime[player - 1] -= (int)clock() - start;
		player_change();
		int win = Chess_Check();
		if (win != 0)
		{
			return win;
		}
		if (playtime[0] < 0)
		{
			return 2;
		}
		if (playtime[1] < 0)
		{
			return 1;
		}
		gotocurserXY(1, 20);
		printf("%s 남은시간 %d분 %d초\n", playername[0], playtime[0] / 60000, (playtime[0] % 60000) / 1000);
		printf(" %s 남은시간 %d분 %d초\n", playername[1], playtime[1] / 60000, (playtime[1] % 60000) / 1000);
	}
}

void Chess_Play()
{
	while (1)
	{


		do
		{
			Mouse_Check();
			x1 = (mouse_x - 1) / 4;
			y1 = (mouse_y - 1) / 2;
			Sleep(100);
		} while (!(chess_game[y1][x1] % 10 == player && mouse_x % 4 != 0 && mouse_y % 2 == 1));
		road(x1, y1);

		while (1)
		{
			Mouse_Check();
			x2 = (mouse_x - 1) / 4;
			y2 = (mouse_y - 1) / 2;
			if (chess_game[y2][x2] % 10 == player)
			{
				if (((chess_game[y1][x1] - player) / 10) == 1 && ((chess_game[y2][x2] - player) / 10) == 5)
				{
					piece = 6;
					break;
				}
				else
				{

					x1 = x2;
					y1 = y2;
					Chess_Board();
					road(x1, y1);
				}
			}
			else if (mouse_x % 4 != 1 && mouse_y % 2 == 1)
			{
				break;
			}
		}
		if (piece != 6)
		{
			piece = (chess_game[y1][x1] - player) / 10;
		}
		if (chess_game[y2][x2] % 10 == 0)
		{
			state = 0;
		}
		else
		{
			state = 1;
		}
		switch (piece)
		{
		case 0:
			Chess_Pawn();
			break;
		case 1:
			Chess_Rook();
			break;
		case 2:
			Chess_Knigt();
			break;
		case 3:
			Chess_Bishop();
			break;
		case 4:
			Chess_Queen();
			break;
		case 5:
			Chess_King();
			break;
		case 6:
			Chess_Castling();
			piece = -1;
			break;
		default:
			break;
		}
		if (turnend == 1)
		{
			turnend = 0;
			break;
		}
		Chess_Board();
		Print_Message("이상한 위치입니다.");
		gotocurserXY(1, 20);
		printf("%s 남은시간 %d분 %d초\n", playername[0], playtime[0] / 60000, (playtime[0] % 60000) / 1000);
		printf(" %s 남은시간 %d분 %d초\n", playername[1], playtime[1] / 60000, (playtime[1] % 60000) / 1000);
	}

}

void Chess_Board()
{
	consol_clear();
	Color_set(WHITE);
	gotocurserXY(0, 0);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			printf("%s", chess_board[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			gotocurserXY(j * 4 + 1, i * 2 + 1);
			if (chess_game[i][j] % 10 == 1)
			{

				Color_set(SKY);
				switch ((chess_game[i][j] - 1) / 10)
				{
				case 0:
					printf(" P");
					break;
				case 1:
					printf(" R");
					break;
				case 2:
					printf(" N");
					break;
				case 3:
					printf(" B");
					break;
				case 4:
					printf(" Q");
					break;
				case 5:
					printf(" K");
					break;
				default:
					break;
				}
			}
			else if (chess_game[i][j] % 10 == 2)
			{
				Color_set(RED);
				switch ((chess_game[i][j] - 1) / 10)
				{
				case 0:
					printf(" P");
					break;
				case 1:
					printf(" R");
					break;
				case 2:
					printf(" N");
					break;
				case 3:
					printf(" B");
					break;
				case 4:
					printf(" Q");
					break;
				case 5:
					printf(" K");
					break;
				default:
					break;
				}
			}
			else
			{
				printf(" ");
			}
		}
	}
}

void Chess_Pawn()
{
	if (player == 1)
	{
		if (state == 1)
		{
			if ((x1 - x2 == 1 || x2 - x1 == 1) && y2 - y1 == 1)
			{
				if (y2 == 7)
				{
					int sta;
					do
					{
						gotocurserXY(1, 19);
						printf("어떤기물을 선택하시겠습니까?\n1 :룩 2 : 나이트 3 : 비숍 4 : 퀸\n    ");
						gotocurserXY(1, 21);
						scanf_s("%d", &sta);
					} while (!(sta == 4 || (sta <= 3 && sta >= 1)));
					chess_game[y2][x2] = sta * 10 + 1;
					chess_game[y1][x1] = 00;
				}
				else
				{

					chess_game[y2][x2] = 01;
					chess_game[y1][x1] = 00;
				}

				turnend = 1;
			}
		}
		else
		{
			if (x1 == x2 && y2 - y1 == 1)
			{
				if (y2 == 7)
				{
					int sta;
					do
					{
						gotocurserXY(1, 19);
						printf("어떤기물을 선택하시겠습니까?\n1 :룩 2 : 나이트 3 : 비숍 4 : 퀸\n    ");
						gotocurserXY(1, 21);
						scanf_s("%d", &sta);
					} while (!(sta == 4 || (sta <= 3 && sta >= 1)));
					chess_game[y2][x2] = sta * 10 + 1;
					chess_game[y1][x1] = 00;
				}
				else
				{

					chess_game[y2][x2] = 01;
					chess_game[y1][x1] = 00;
				}
				turnend = 1;
			}
			else if (x1 == x2 && y2 - y1 == 2)
			{
				if (y1 == 1 && chess_game[y1 + 1][x1] == 00)
				{

					chess_game[y2][x2] = 01;
					chess_game[y1][x1] = 00;
					turnend = 1;

				}
			}
		}
	}
	else
	{
		if (state == 1)
		{
			if ((x1 - x2 == 1 || x2 - x1 == 1) && y1 - y2 == 1)
			{
				if (y2 == 0)
				{
					int sta;
					do
					{
						gotocurserXY(1, 19);
						printf("어떤기물을 선택하시겠습니까?\n1 :룩 2 : 나이트 3 : 비숍 4 : 퀸\n    ");
						gotocurserXY(1, 21);
						scanf_s("%d", &sta);
					} while (!(sta == 4 || (sta <= 3 && sta >= 1)));
					chess_game[y2][x2] = sta * 10 + 2;
					chess_game[y1][x1] = 00;
				}
				else
				{

					chess_game[y2][x2] = 02;
					chess_game[y1][x1] = 00;
				}
				turnend = 1;
			}
		}
		else
		{
			if (x1 == x2 && y1 - y2 == 1)
			{
				if (y2 == 0)
				{

					int sta;
					do
					{
						gotocurserXY(1, 19);
						printf("어떤기물을 선택하시겠습니까?\n1 :룩 2 : 나이트 3 : 비숍 4 : 퀸\n    ");
						gotocurserXY(1, 21);
						scanf_s("%d", &sta);
					} while (!(sta == 4 || (sta <= 3 && sta >= 1)));
					chess_game[y2][x2] = sta * 10 + 2;
					chess_game[y1][x1] = 00;
				}
				else
				{

					chess_game[y2][x2] = 02;
					chess_game[y1][x1] = 00;
				}
				turnend = 1;
			}
			else if (x1 == x2 && y1 - y2 == 2)
			{
				if (y1 == 6 && chess_game[y1 - 1][x1] == 00)
				{

					chess_game[y2][x2] = 02;
					chess_game[y1][x1] = 00;
					turnend = 1;

				}
			}
		}
	}
}

void Chess_Rook()
{
	if (x1 == x2)
	{
		if (y2 > y1)
		{
			int i;
			for (i = 1; y1 + i < y2; i++)
			{
				if (chess_game[y1 + i][x1] != 00)
				{
					break;
				}
			}
			if (y1 + i == y2)
			{
				chess_game[y2][x2] = 10 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else
		{
			int i;
			for (i = 1; y1 - i > y2; i++)
			{
				if (chess_game[y1 - i][x1] != 00)
				{
					break;
				}
			}
			if (y1 - i == y2)
			{
				chess_game[y2][x2] = 10 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}

	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			int i;
			for (i = 1; x1 + i < x2; i++)
			{
				if (chess_game[y1][x1 + i] != 00)
				{
					break;
				}
			}
			if (x1 + i == x2)
			{
				chess_game[y2][x2] = 10 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else
		{
			int i;
			for (i = 1; x1 - i > x2; i++)
			{
				if (chess_game[y1][x1 - i] != 00)
				{
					break;
				}
			}
			if (x1 - i == x2)
			{
				chess_game[y2][x2] = 10 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}

	}
}

void Chess_Knigt()
{
	if ((abs(y1 - y2) == 2 && abs(x1 - x2) == 1) || (abs(y1 - y2) == 1 && abs(x1 - x2) == 2))
	{
		chess_game[y2][x2] = 20 + player;
		chess_game[y1][x1] = 00;
		turnend = 1;
	}
}

void Chess_Bishop()
{
	if (abs(x1 - x2) == abs(y1 - y2))
	{
		if (y1 < y2 && x1 < x2)
		{
			int i;
			for (i = 1; y1 + i < y2; i++)
			{
				if (chess_game[y1 + i][x1 + i] != 00)
				{
					break;
				}
			}
			if (y1 + i == y2)
			{
				chess_game[y2][x2] = 30 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else if (y1 < y2 && x1 > x2)
		{
			int i;
			for (i = 1; y1 + i < y2; i++)
			{
				if (chess_game[y1 + i][x1 - i] != 00)
				{
					break;
				}
			}
			if (y1 + i == y2)
			{
				chess_game[y2][x2] = 30 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else if (y1 > y2 && x1 < x2)
		{
			int i;
			for (i = 1; y1 - i > y2; i++)
			{
				if (chess_game[y1 - i][x1 + i] != 00)
				{
					break;
				}
			}
			if (y1 - i == y2)
			{
				chess_game[y2][x2] = 30 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else if (y1 > y2 && x1 > x2)
		{
			int i;
			for (i = 1; y1 - i > y2; i++)
			{
				if (chess_game[y1 - i][x1 - i] != 00)
				{
					break;
				}
			}
			if (y1 - i == y2)
			{
				chess_game[y2][x2] = 30 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}

	}
}

void Chess_Queen()
{
	if (abs(x1 - x2) == abs(y1 - y2))
	{
		if (y1 < y2 && x1 < x2)
		{
			int i;
			for (i = 1; y1 + i < y2; i++)
			{
				if (chess_game[y1 + i][x1 + i] != 00)
				{
					break;
				}
			}
			if (y1 + i == y2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else if (y1 < y2 && x1 > x2)
		{
			int i;
			for (i = 1; y1 + i < y2; i++)
			{
				if (chess_game[y1 + i][x1 - i] != 00)
				{
					break;
				}
			}
			if (y1 + i == y2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else if (y1 > y2 && x1 < x2)
		{
			int i;
			for (i = 1; y1 - i > y2; i++)
			{
				if (chess_game[y1 - i][x1 + i] != 00)
				{
					break;
				}
			}
			if (y1 - i == y2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else if (y1 > y2 && x1 > x2)
		{
			int i;
			for (i = 1; y1 - i > y2; i++)
			{
				if (chess_game[y1 - i][x1 - i] != 00)
				{
					break;
				}
			}
			if (y1 - i == y2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}

	}
	else if (x1 == x2)
	{
		if (y2 > y1)
		{
			int i;
			for (i = 1; y1 + i < y2; i++)
			{
				if (chess_game[y1 + i][x1] != 00)
				{
					break;
				}
			}
			if (y1 + i == y2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else
		{
			int i;
			for (i = 1; y1 - i > y2; i++)
			{
				if (chess_game[y1 - i][x1] != 00)
				{
					break;
				}
			}
			if (y1 - i == y2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}

	}
	else if (y1 == y2)
	{
		if (x1 < x2)
		{
			int i;
			for (i = 1; x1 + i < x2; i++)
			{
				if (chess_game[y1][x1 + i] != 00)
				{
					break;
				}
			}
			if (x1 + i == x2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else
		{
			int i;
			for (i = 1; x1 - i > x2; i++)
			{
				if (chess_game[y1][x1 - i] != 00)
				{
					break;
				}
			}
			if (x1 - i == x2)
			{
				chess_game[y2][x2] = 40 + player;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}

	}
}

void Chess_King()
{
	if ((abs(x1 - x2) == 1 || abs(x1 - x2) == 0) && (abs(y1 - y2) == 1 || abs(y1 - y2) == 0))
	{
		chess_game[y2][x2] = 50 + player;
		chess_game[y1][x1] = 00;
		turnend = 1;
	}
}

void road(int x, int y)
{
	background(x, y);
	switch ((chess_game[y][x] - player) / 10)
	{
	case 0:
		Chess_Pawn_road(x, y);
		break;
	case 1:
		Chess_Rook_road(x, y);
		break;
	case 2:
		Chess_Knigt_road(x, y);
		break;
	case 3:
		Chess_Bishop_road(x, y);
		break;
	case 4:
		Chess_Queen_road(x, y);
		break;
	case 5:
		Chess_King_road(x, y);
		break;
	}
}

void Chess_Pawn_road(int x, int y)
{
	if (player == 1)
	{
		if (y == 1)
		{
			for (int i = 1; i <= 2; i++)
			{
				if (chess_game[y + i][x] % 10 != 0)
					break;
				background(x, y + i);
			}
		}
		else
		{
			if (y + 1 <= 7 && y + 1 >= 0 && x <= 7 && x >= 0)
			{
				if (chess_game[y + 1][x] % 10 == 0)
				{
					background(x, y + 1);
				}
			}
		}
		if (y + 1 <= 7 && y + 1 >= 0 && x + 1 <= 7 && x + 1 >= 0)
		{
			if (chess_game[y + 1][x + 1] % 10 == 2)
			{
				background(x + 1, y + 1);
			}
		}
		if (y + 1 <= 7 && y + 1 >= 0 && x - 1 <= 7 && x - 1 >= 0)
		{
			if (chess_game[y + 1][x - 1] % 10 == 2)
			{
				background(x - 1, y + 1);
			}
		}
	}
	else
	{
		if (y == 6)
		{
			for (int i = 1; i <= 2; i++)
			{
				if (chess_game[y - i][x] % 10 != 0)
					break;
				background(x, y - i);
			}
		}
		else
		{
			if (y - 1 <= 7 && y - 1 >= 0 && x <= 7 && x >= 0)
			{
				if (chess_game[y - 1][x] % 10 == 0)
				{
					background(x, y - 1);
				}
			}
		}
		if (y - 1 <= 7 && y - 1 >= 0 && x - 1 <= 7 && x - 1 >= 0)
		{
			if (chess_game[y - 1][x - 1] % 10 == 1)
			{
				background(x - 1, y - 1);
			}
		}
		if (y - 1 <= 7 && y - 1 >= 0 && x + 1 <= 7 && x + 1 >= 0)
		{
			if (chess_game[y - 1][x + 1] % 10 == 1)
			{
				background(x + 1, y - 1);
			}
		}
	}
}

void Chess_Rook_road(int x, int y)
{
	int dx1[8] = { 1,-1,0,0};
	int dy1[8] = { 0,0,1,-1};
	for (int i = 0; i < 4; i++)
	{
		for (int py = y + dy1[i], px = x + dx1[i]; py <= 7 && py >= 0 && px <= 7 && px >= 0; py += dy1[i], px += dx1[i])
		{
			if (chess_game[py][px] % 10 != player)
			{
				background(px, py);
				if (chess_game[py][px] % 10 != 0)
				{
					break;
				}
			}
			else
			{
				if ((chess_game[py][px] - player) / 10 == 5 && (i == 0 || i == 1) && px == 4 && (x == 0 || x == 7))
				{
					background(px, py);
				}
				break;
			}
		}
	}
}

void Chess_Knigt_road(int x, int y)
{
	int dx1[8] = { 1,-1,1,-1,2,2,-2,-2 };
	int dy1[8] = { 2,2,-2,-2,1,-1,1,-1 };
	for (int i = 0; i < 8; i++)
	{
		int py = y + dy1[i], px = x + dx1[i];
		if (py <= 7 && py >= 0 && px <= 7 && px >= 0)
		{
			if (chess_game[py][px] % 10 != player)
			{
				background(px, py);
			}
		}
	}


}

void Chess_Bishop_road(int x, int y)
{
	int dx1[8] = { 1,1,-1,-1 };
	int dy1[8] = { 1,-1,1,-1 };
	for (int i = 0; i < 4; i++)
	{
		for (int py = y + dy1[i], px = x + dx1[i]; py <= 7 && py >= 0 && px <= 7 && px >= 0; py += dy1[i], px += dx1[i])
		{
			if (chess_game[py][px] % 10 != player)
			{
				background(px, py);
				if (chess_game[py][px] % 10 != 0)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}

void Chess_Queen_road(int x, int y)
{
	int dx1[8] = { 1,-1,0,0,1,1,-1,-1 };
	int dy1[8] = { 0,0,1,-1,1,-1,1,-1 };
	for (int i = 0; i < 8; i++)
	{
		for (int py = y + dy1[i], px = x + dx1[i]; py <= 7 && py >= 0 && px <= 7 && px >= 0; py += dy1[i], px += dx1[i])
		{
			if (chess_game[py][px] % 10 != player)
			{
				background(px, py);
				if (chess_game[py][px] % 10 != 0)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}

void Chess_King_road(int x, int y)
{
	int dx1[8] = { 1,-1,0,0,1,1,-1,-1 };
	int dy1[8] = { 0,0,1,-1,1,-1,1,-1 };
	for (int i = 0; i < 8; i++)
	{
		int py = y + dy1[i], px = x + dx1[i];
		if (py <= 7 && py >= 0 && px <= 7 && px >= 0)
		{
			if (chess_game[py][px] % 10 != player)
			{
				background(px, py);
			}
		}
	}
}

void Chess_Castling()
{

	if (y1 == y2 && (y1 == 0 || y1 == 7) && x2 == 4 && (x1 == 0 || x1 == 7))
	{
		if (x1 < x2)
		{
			int i;
			for (i = 1; x1 + i < x2; i++)
			{
				if (chess_game[y1][x1 + i] != 00)
				{
					break;
				}
			}
			if (x1 + i == x2)
			{
				chess_game[y2][x2] = 00;
				chess_game[y2][x1] = 00;
				chess_game[y2][3] = 10 + player;
				chess_game[y1][2] = 50 + player;
				turnend = 1;

			}
		}
		else
		{
			int i;
			for (i = 1; x1 - i > x2; i++)
			{
				if (chess_game[y1][x1 - i] != 00)
				{
					break;
				}
			}
			if (x1 - i == x2)
			{
				chess_game[y2][x2] = 00;
				chess_game[y2][x1] = 00;
				chess_game[y2][5] = 10 + player;
				chess_game[y1][6] = 50 + player;
				turnend = 1;
			}
		}

	}
}

int Chess_Check()
{
	int p1 = 0, p2 = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chess_game[i][j] == 51)
			{
				p1 = 1;
			}
			else if (chess_game[i][j] == 52)
			{
				p2 = 1;
			}
		}
	}
	if (p1 == 0)
	{
		Chess_End(2);
		return 2;
	}
	else if (p2 == 0)
	{
		Chess_End(1);
		return 1;
	}
	return 0;

}

void Chess_End(int p)
{
	consol_clear();
	gotocurserXY(0, 0);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			chess_game[i][j] = chess_game1[i][j];
		}
	}
	printf("%s(이)가 승리하였습니다.\n마우스를 클릭하면 게임 선택화면으로 이동합니다.", playername[p - 1]);
	Sleep(1000);
	Mouse_Check();
	consol_clear();
}

void background(int x, int y)
{
	int i = y * 2 + 1;
	int j = x * 4 + 2;
	gotocurserXY(j, i);
	Color_set(224);
	if (chess_game[y][x] % 10 == 1)
	{

		Color_set(SKY + BACK);
		switch ((chess_game[y][x] - 1) / 10)
		{
		case 0:
			printf("P ");
			break;
		case 1:
			printf("R ");
			break;
		case 2:
			printf("N ");
			break;
		case 3:
			printf("B ");
			break;
		case 4:
			printf("Q ");
			break;
		case 5:
			printf("K ");
			break;
		default:
			break;
		}
	}
	else if (chess_game[y][x] % 10 == 2)
	{
		Color_set(RED + BACK);
		switch ((chess_game[y][x] - 1) / 10)
		{
		case 0:
			printf("P ");
			break;
		case 1:
			printf("R ");
			break;
		case 2:
			printf("N ");
			break;
		case 3:
			printf("B ");
			break;
		case 4:
			printf("Q ");
			break;
		case 5:
			printf("K ");
			break;
		default:
			break;
		}
	}
	else
	{
		printf("  ");
	}
	Color_set(WHITE);
}