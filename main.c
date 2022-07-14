#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"chess.h"
#include"game.h"
#include"Omok.h"

typedef struct
{
	char arr[50];
}record;

void print_menu();
void recording(char* ocgame, int win);

void main()
{
	SetConsoleMode(COUT, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	Mouse_Able();
	while (1)
	{
		consol_clear();
		gotocurserXY(0, 0);
		print_menu();
		Mouse_Check();
		consol_clear();
		gotocurserXY(0, 0);
		int win;
		if (mouse_y == 6)
		{
			printf("player1의 이름을 입력하세요 : ");
			scanf_s("%s", playername[0], 9);
			printf("player2의 이름을 입력하세요 : ");
			scanf_s("%s", playername[1], 9);
		}
		else if (mouse_y == 8)
		{
			recording("Chess", Chess_start());

		}
		else if (mouse_y == 10)
		{

			recording("Omok", Omok_start());
		}
		else if (mouse_y == 12)
		{
			consol_clear();
			gotocurserXY(0, 0);
			FILE* f = fopen("record.txt", "r");
			int i = 0;
			char arr[50];
			do
			{
				fgets(arr, 49, f);
				printf("%s", arr);
				i++;
			} while (strcmp(arr, "end\n") != 0);
			printf("마우스를 클릭하면 메뉴화면으로 넘어갑니다.");
			Mouse_Check();

		}
		else if (mouse_y == 14)
		{
			FILE* f = fopen("record.txt", "w");
			fprintf(f, "end\n");
			fclose(f);
			consol_clear();
			gotocurserXY(0, 0);
			printf("전적을 초기화 하였습니다.\n마우스를 클릭하면 메뉴화면으로 넘어갑니다.");
			Mouse_Check();
		}
	}
}

void print_menu()
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                오목 체스 게임기                ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("                                                    \n");
	printf("                   메뉴를 선택하세요                \n");
	printf("                                                    \n");
	printf("                  ▶플레이어 이름 입력              \n");
	printf("                                                    \n");
	printf("                  ▷체스 시작                       \n");
	printf("                                                    \n");
	printf("                  ▶오목 시작                       \n");
	printf("                                                    \n");
	printf("                  ▷전적 확인하기                   \n");
	printf("                                                    \n");
	printf("                  ▶전적 초기화                     \n");


}

void recording(char* ocgame, int win)
{
	FILE* f = fopen("record.txt", "r");
	record* rec = (record*)malloc(sizeof(record));
	int i = 0;
	do
	{
		rec = (record*)realloc(rec, sizeof(record) * (i + 1));
		fgets(rec[i].arr, 49, f);
		i++;
	} while (strcmp(rec[i - 1].arr, "end\n") != 0);
	fclose(f);
	f = fopen("record.txt", "w");
	int j;
	for (j = 0; j < i - 1; j++)
	{
		fprintf(f, "%s", rec[j].arr);
	}
	fprintf(f, "   <%s vs %s> \n   %s %s win!!!\nend\n", playername[0], playername[1], ocgame, playername[win - 1]);
	fclose(f);
	free(rec);
}