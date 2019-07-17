// Header file for CheckMovement.c
#ifndef CHECKMOVEMENT_H
#define CHECKMOVEMENT_H

#include "Constants.h"

struct MV PawnCheck(int Scol, int Srow, char type, char color, char lastmove[4], struct PIECE chessboard[8][8]);

struct MV RookCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8]);

struct MV KingCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8]);

struct MV QueenCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8]);

struct MV  KnightCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8]);

struct MV BishopCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8]);

#endif
