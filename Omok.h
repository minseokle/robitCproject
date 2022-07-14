#ifndef Omok
#define Omok
#include"game.h"

int Omok_board[19][19];


int Omok_start();
void Omok_board_set(int c, int r);
void Omok_stone_down();
int Omok_check();
int Omok_end();

#endif // !Omok
