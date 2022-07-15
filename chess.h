#ifndef chess
#define chess
#include"game.h"

int x1, y1, x2, y2, piece, state, turnend;
char chess_board[17][17];
int chess_game1[8][8];
int chess_game[8][8];


int Chess_start();
void Chess_Board();
void Chess_Play();
void Chess_Pawn();
void Chess_Rook();
void Chess_Knigt();
void Chess_Bishop();
void Chess_Queen();
void Chess_King();
void Chess_Castling();
int Chess_Check();
void Chess_End(int p);

#endif // !chess
