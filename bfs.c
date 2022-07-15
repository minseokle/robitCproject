
#include"bfs.h"

int bfs_start()
{
	Color_set(WHITE);
	int x[4] = { 1,0,-1,0 };
	int y[4] = { 0,1,0,-1 };
	int der = 0;
	int arr2[20][20] = { 0, };
	int arr[20][20] = { 0, };
	for (int j = 0; j < 22; j++)
	{
		printf("■");
	}
	printf("\n");
	for (int i = 1; i < 21; i++)
	{
		printf("■");
		for (int j = 1; j < 21; j++)
		{
			printf("  ");
		}
		printf("■");
		printf("\n");
	}
	for (int j = 0; j < 22; j++)
	{
		printf("■");
	}
	printf("\n");
	printf("┌────┐\n");
	printf("│시작│\n");
	printf("└────┘\n");
	while (1)
	{
		Mouse_drag();
		gotocurserXY(1, 25);
		if (mouse_x <= 41 && mouse_x >= 2 && mouse_y >= 1 && mouse_y <= 21)
		{
			int x = (mouse_x - (mouse_x % 2)) / 2;
			int y = mouse_y;
			arr[y - 1][x - 1] = 1;
			gotocurserXY(x * 2, y);
			printf("■");
		}
		else if (mouse_x >= 1 && mouse_x <= 5 && mouse_y == 23)
		{
			break;
		}
	}
	Color_set(RED);
	gotocurserXY(2, 1);
	printf("■");
	arr[0][0] = 2;
	arr2[0][0] = 1;
	int check[100] = { 00,0, };
	int checknum = 0;

	do
	{
		int j = check[0] % 100;
		int i = (check[0] - j) / 100;
		for (int k = 0; k < checknum; k++)
		{
			check[k] = check[k + 1];
		}
		check[checknum] = 0;
		checknum--;
		for (der = 0; der < 4; der++)
		{
			int si = i + y[der];
			int sj = j + x[der];
			if (si >= 0 && si < 20 && sj >= 0 && sj < 20)
			{
				if (arr[si][sj] == 0)
				{
					arr2[si][sj] = arr2[i][j] + 1;
					arr[si][sj] = 2;
					checknum++;
					check[checknum] = si * 100 + sj;
					Color_set(RED);
					gotocurserXY(sj * 2 + 2, si + 1);
					printf("■");
				}
			}
		}
	} while (check[0] != 0);


	if (arr2[19][19] == 0)
	{

		Color_set(WHITE);
		gotocurserXY(0, 22);
		printf("                      \n");
		printf("                      \n");
		printf("                      \n");
		printf("                      \n");
		gotocurserXY(1, 22);
		printf("출구를 찾을 수 없습니다.\n");
	}
	else
	{
		int check1 = 1919;
		Color_set(BLUE);
		gotocurserXY(40, 20);
		printf("■");
		do
		{
			int j = check1 % 100;
			int i = (check1 - j) / 100;
			for (der = 0; der < 4; der++)
			{
				int si = i + y[der];
				int sj = j + x[der];
				if (si >= 0 && si < 20 && sj >= 0 && sj < 20)
				{
					if (arr2[si][sj] == arr2[i][j] - 1)
					{
						check1 = si * 100 + sj;
						Color_set(BLUE);
						gotocurserXY(sj * 2 + 2, si + 1);
						printf("■");
						break;
					}
				}
			}
		} while (check1 != 0);
		Color_set(WHITE);
		gotocurserXY(0, 22);
		printf("                      \n");
		printf("                      \n");
		printf("                      \n");
		printf("                      \n");
		gotocurserXY(1, 22);
		printf("미로의 최단거리는 %d입니다.\n ", arr2[19][19]);
	}
	return 0;
}