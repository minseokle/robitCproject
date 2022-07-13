#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>

#define CIN GetStdHandle(STD_INPUT_HANDLE) // 표준 입력 디바이스
#define COUT GetStdHandle(STD_OUTPUT_HANDLE)
#define RED 4
#define BLUE 1
#define WHITE 7 
#define YELLOW 6

int x1, y1, x2, y2, piece, state, turnend;
int mouse_x, mouse_y, player = 1;
char chess_board[17][17] =
{
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
	{'|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},

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

INPUT_RECORD rec;
DWORD	dwNOER;
DWORD mode;

void gotoMouseXY(int x, int y);
void Mouse_Able();
void Mouse_Check();
void setColor(int color);
void Chess_Board();
void Chess_Play();
void Error_Message(char* mas);
void player_change()；
void Chess_Pawn();
void Chess_Rook();
void Chess_Knigt();
void Chess_Bishop();
void Chess_Queen();
void Chess_King();
void Chess_Check();
void Chess_End(int p);

void main()
{
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	Mouse_Able();
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			printf("%c", chess_board[i][j]);
		}
		printf("\n");
	}
	Chess_Board();
	Error_Message("플레이어1차례");
	while (1)
	{

		Chess_Play();
		Chess_Board();
		player_change();
		Chess_Check();
		
	}
}

void Chess_Play()
{
	while (1)
	{


		do
		{
			Mouse_Check();
			x1 = (mouse_x - 1) / 2;
			y1 = (mouse_y - 1) / 2;
			Sleep(100);
		} while (!(chess_game[y1][x1] % 10 == player && mouse_x % 2 == 1 && mouse_y % 2 == 1));
		while (1)
		{
			Mouse_Check();
			x2 = (mouse_x - 1) / 2;
			y2 = (mouse_y - 1) / 2;
			if (chess_game[y2][x2] % 10 == player)
			{
				x1 = x2;
				y1 = y2;
			}
			else if (mouse_x % 2 == 1 && mouse_y % 2 == 1)
			{
				break;
			}
		}
		piece = (chess_game[y1][x1] - player) / 10;
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
			Chess_King();
			break;
		case 5:
			Chess_Queen();
			break;

		default:
			break;
		}
		if (turnend == 1)
		{
			turnend = 0;
			break;
		}
		Error_Message("이상한 위치입니다.");
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

void Chess_Board()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(COUT, ' ', 80 * 80, Coor, &dw);
	setColor(WHITE);
	gotoMouseXY(0, 0);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			printf("%c", chess_board[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			gotoMouseXY(j * 2 + 1, i * 2 + 1);
			if (chess_game[i][j] % 10 == 1)
			{
				setColor(YELLOW);
				switch ((chess_game[i][j] - 1) / 10)
				{
				case 0:
					printf("P");
					break;
				case 1:
					printf("R");
					break;
				case 2:
					printf("N");
					break;
				case 3:
					printf("B");
					break;
				case 4:
					printf("K");
					break;
				case 5:
					printf("Q");
					break;
				default:
					break;
				}
			}
			else if (chess_game[i][j] % 10 == 2)
			{
				setColor(RED);
				switch ((chess_game[i][j] - 1) / 10)
				{
				case 0:
					printf("P");
					break;
				case 1:
					printf("R");
					break;
				case 2:
					printf("N");
					break;
				case 3:
					printf("B");
					break;
				case 4:
					printf("K");
					break;
				case 5:
					printf("Q");
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

void Error_Message(char* mas)
{
	setColor(WHITE);
	gotoMouseXY(1, 17);
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

void Chess_Pawn()
{
	if (player == 1)
	{
		if (state == 1)
		{
			if ((x1 - x2 == 1 || x2 - x1 == 1) && y2 - y1 == 1)
			{
				chess_game[y2][x2] = 01;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else
		{
			if (x1 == x2 && y2 - y1 == 1)
			{
				chess_game[y2][x2] = 01;
				chess_game[y1][x1] = 00;
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
				chess_game[y2][x2] = 02;
				chess_game[y1][x1] = 00;
				turnend = 1;
			}
		}
		else
		{
			if (x1 == x2 && y1 - y2 == 1)
			{
				chess_game[y2][x2] = 02;
				chess_game[y1][x1] = 00;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
				chess_game[y2][x2] = 50 + player;
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
		chess_game[y2][x2] = 40 + player;
		chess_game[y1][x1] = 00;
		turnend = 1;
	}
}

void Chess_Check()
{
	int p1 = 0, p2 = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chess_game[i][j] == 41)
			{
				p1 = 1;
			}
			else if (chess_game[i][j] == 42)
			{
				p2 = 1;
			}
		}
	}
	if (p1 == 0)
	{
		Chess_End(2);
	}
	else if (p2 == 0)
	{
		Chess_End(1);
	}

}

void Chess_End(int p)
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(COUT, ' ', 80 * 80, Coor, &dw);
	gotoMouseXY(0, 0);
	printf("플레이어%d이 승리하였습니다.\n마우스를 클릭하면 다음판이 진행 됩니다.", p);
	Sleep(1000);
	Mouse_Check();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			chess_game[i][j] = chess_game1[i][j];
		}
	}
	Chess_Board();
}