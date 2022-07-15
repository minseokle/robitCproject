#ifndef chess
#define chess
#include"game.h"

int x1, y1, x2, y2, piece, state, turnend;
char chess_board[17][17][5];
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
void road(int x, int y);
void Chess_Pawn_road(int x, int y);
void Chess_Rook_road(int x, int y);
void Chess_Knigt_road(int x, int y);
void Chess_Bishop_road(int x, int y);
void Chess_Queen_road(int x, int y);
void Chess_King_road(int x, int y);
void Chess_Castling();
int Chess_Check();
void Chess_End(int p);
void background(int x, int y);

#endif // !chess
