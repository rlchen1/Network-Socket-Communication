#ifndef CHECKDESTINATION_H
#define CHECKDESTINATION_H
//Header file for CheckDestination.c
void MovePiece(struct PIECE chessboard[8][8], int Scol, int Srow, int Dcol, int Drow, struct MV move);

void Capture(struct PIECE chessboard[8][8], int Scol, int Srow, int Dcol, int Drow);

void PawnPromotion(struct PIECE chessboard[8][8], int Dcol, int Drow, char color, char color2, char type, struct MV move);

int Check(struct PIECE chessboard[8][8], char color, char color2, char lastmove[4], char type);
	
int Checkmate(struct PIECE chessboard[8][8], char color, char type, struct MV move);

void Castling(struct PIECE chessboard[8][8], int side, int turn);

#endif
