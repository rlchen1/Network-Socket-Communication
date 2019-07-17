//CheckDestination File
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "CheckDestination.h"
#include "CheckMovement.h"

//void Compare(struct PIECE chessboard[8][8], char Scol, char Srow, char Dcol, char Drow){
	//check if destination is in possible moves array
	//check if there is a piece or not in destination, if valid destination
//}

void MovePiece(struct PIECE chessboard[8][8], int Scol, int Srow, int Dcol, int Drow,struct MV move){
	// call <Piece>check(), check if destination is in array
	// update struct array
	//
	// POSSIBLE WAY TO CHECK VALID/INVALID MOVE:
	// call PawnCheck(), KingCheck(), etc. to get possiblemoves array
	// run a for loop through the possiblemoves array with the statement and increment i by 2 in each iteration
	// if (possiblemoves[i] == destrow && possiblemoves[i+1] == destcol) { counter++
	// counter = 1 > move is valid
	// counter = 0 > move is invalid

	int counter;
	int success=0;
	counter = move.n;
//	printf("movement[0]:%d",move.movement[0]);
//	printf("movement[1]:%d\n",move.movement[1]);
	for (int i =0;i<counter;i=i+2){
          if((move.movement[i] == Dcol)&&(move.movement[i+1] == Drow)){
	
	Capture(chessboard,Scol,Srow,Dcol,Drow);
	chessboard[Drow][Dcol].type = chessboard[Srow][Scol].type;
  chessboard[Drow][Dcol].color = chessboard[Srow][Scol].color;
  chessboard[Srow][Scol].type = ' ';
  chessboard[Srow][Scol].color = ' ';
	success=1;

	 } 

	}
	if (success== 0){
	}
}

void Capture(struct PIECE chessboard[8][8], int Scol, int Srow, int Dcol, int Drow){
	
	if((chessboard[Drow][Dcol].color != chessboard[Srow][Scol].color)) //if enemy piece in destination, clear the enemy piece and set to own piece, clear own piece from source location
	{
		chessboard[Drow][Dcol].color = ' ';
		chessboard[Drow][Dcol].type = ' ';
		chessboard[Drow][Dcol].color = chessboard[Srow][Scol].color;
		chessboard[Drow][Dcol].type = chessboard[Srow][Scol].type;
	}
//	else
//	{
//		printf("Invalid move.\n");
		//need to return to the printMenu asking for coordinate input
//	}
}

void PawnPromotion(struct PIECE chessboard[8][8], int Dcol, int Drow, char color, char color2, char type, struct MV move){
	//need to check that the color is 'w' or 'b', and type is pawn 'P'
	//call PawnCheck(), check if destination is in array
	int counter;
	char promote = ' ';
	counter = move.n;
	
	for(int i=0; i<counter; i=i+2)
	{
	   if((move.movement[i] == Dcol) && (move.movement[i+1] == Drow))
		{	
			if((color == 'w' && type == 'P' && Drow == 0) || (color == 'b' && type == 'P' && Drow == 7) || (color2 == 'w' && type == 'P' && Drow == 0) || (color2 == 'b' && type == 'P' && Drow == 7)){
				printf("What piece shall pawn be promoted to?\n");
				printf("'Q': queen, 'R': rook, 'B': bishop, 'N': knight. Promote to:\n");
				scanf(" %c", &promote);
				if(promote == 'Q' || promote == 'q'){
					chessboard[Drow][Dcol].type = 'Q';
					printf("Pawn has been promoted to queen.\n");}
				else if(promote == 'R' || promote == 'r'){
					chessboard[Drow][Dcol].type = 'R';
					printf("Pawn has been promoted to rook.\n");}
				else if(promote == 'B' || promote == 'b'){
					chessboard[Drow][Dcol].type = 'B';
					printf("Pawn has been promoted to bishop.\n");}
				else if(promote == 'N' || promote == 'n'){
					chessboard[Drow][Dcol].type = 'N';
					printf("Pawn has been promoted to knight.\n");}
			}//end user pawn promotion

			//TO DO: AI hard code to 'Q'
/*			if(color == 'b' && type == 'P' && Drow == 7){
				chessboard[Drow][Dcol].type = 'Q';}
			if(color2 == 'w' && type == 'P' && Drow == 0){
				chessboard[Drow][Dcol].type = 'Q';}
			if(color2 == 'b' && type == 'P' && Drow == 7){
				chessboard[Drow][Dcol].type = 'Q';}
*/		}
	}
}
int Check(struct PIECE chessboard[8][8], char color, char color2, char lastmove[4], char type){

	struct MV counter;
/*	struct MV counter1;
	struct MV counter2;
	struct MV counter3;
	struct MV counter4;
	struct MV counter5;*/

	int check = 0;
	
	//pathway: for every enemy piece on the board, filter by piece type and check all possible movements
	//if any possible movements of enemy contain own king, set check = 1	

	// 1. first check if king has any possible destinations
	// if king has possible destinations
	// 2. compare all possible destinations of opposite color with king's location and king's possible destinations
	// if 1. is false and 2. is true, check = 1

	// set color2 to opposite of color
	if (color == 'w'){
		color2 = 'b';
	}else if (color == 'b'){
		color2 = 'w';
	}	

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(chessboard[i][j].color == color2) // enemy piece
			{
				if(chessboard[i][j].type == 'P') 
				{
					counter = PawnCheck(i, j, 'P', color2, lastmove, chessboard);
					for(int k=0; k<counter.n; k=k+2) // counter = move.n, movement is stored col, row in 1D array
					{
						if((chessboard[counter.movement[k]][counter.movement[k+1]].type == 'K') && (chessboard[counter.movement[k]][counter.movement[k+1]].color == color))
						{
							//printf("PAWN");
							check = 1;
						}
					}
				}
				
				if(chessboard[i][j].type == 'R')
				{
					counter = RookCheck(j, i, color2, chessboard);
					for(int k=0; k<counter.n; k=k+2)
					{	 
						if((chessboard[counter.movement[k+1]][counter.movement[k]].type == 'K') && (chessboard[counter.movement[k+1]][counter.movement[k]].color == color))
						{
							//printf("ROOK");
							check = 1;
						}
					}			
				}

				if(chessboard[i][j].type == 'N')
				{
					counter = KnightCheck(i, j, color2, chessboard);
					for(int k=0; k<counter.n; k=k+2)
					{
           					
						if((chessboard[counter.movement[k+1]][counter.movement[k]].type == 'K') && (chessboard[counter.movement[k+1]][counter.movement[k]].color == color))
            					{					
							//printf("KNIGHT");
            						check = 1;
          					}
					}
				}
				
				if(chessboard[i][j].type == 'B')
				{
					counter = BishopCheck(i, j, color2, chessboard);
					for(int k=0; k<counter.n; k=k+2)
          {
           
			//printf("(%c,%c) ", (char)(counter.movement[k]+97), (char)(56-counter.movement[k+1]));
			//printf("\n");
			if((chessboard[counter.movement[k]][counter.movement[k+1]].type == 'K') && (chessboard[counter.movement[k]][counter.movement[k+1]].color == color))
            {
		//printf("BISHOP");
              check = 1;
            }
          }
				}
			
				if(chessboard[i][j].type == 'Q')
				{
					counter = QueenCheck(j, i, color2, chessboard);
					for(int k=0; k<counter.n; k=k+2)
 	        			{
     						if((chessboard[counter.movement[k+1]][counter.movement[k]].type == 'K') && (chessboard[counter.movement[k+1]][counter.movement[k]].color == color))
           					{
							//printf("QUEEN");
           						check = 1;
         					}
				         }
				}
			}	
		}
	}
	return check;
}

int Checkmate(struct PIECE chessboard[8][8], char color, char type, struct MV move){
	// checkmate conditions
	// king does not have possible destinations OR
	// king's possible destinations match ALL other pieces' destinations
/******************************************	
// TO DO: PIECE BLOCKING 
******************************************/
	int checkmate = 0;
	
	if (move.n <= 0){ // king does not have possible moves
		checkmate = 0;
	}
	return checkmate;
}
void Castling(struct PIECE chessboard[8][8], int side, int turn)
{
    //Kingside = 1, QueenSide = 2
    if(turn % 2 == 1)              //WHITE SIDE CASTLING
    {
        if(chessboard[7][4].type == 'K' && chessboard[7][4].color == 'w' && chessboard[7][5].type == ' ' && chessboard[7][6].type == ' ' && chessboard[7][7].type == 'R' && chessboard[7][7].color == 'w' && side == 1) //WHITE KING SIDE CASTLING
        {
            //set king to new spot/remove old spot
            chessboard[7][6].type = chessboard[7][4].type;  
            chessboard[7][6].color = chessboard[7][4].color; 
            chessboard[7][4].type = ' ';
            chessboard[7][4].color = ' ';
            //set rook to new spot/remove old spot
            chessboard[7][5].type = chessboard[7][7].type;
            chessboard[7][5].color = chessboard[7][7].color;;
            chessboard[7][7].type = ' ';
            chessboard[7][7].color = ' ';

        }
        else if(chessboard[7][4].type == 'K' && chessboard[7][4].color == 'w' && chessboard[7][3].type == ' ' && chessboard[7][2].type == ' ' && chessboard[7][1].type == ' ' && chessboard[7][0].type == 'R' && chessboard[7][0].color == 'w' && side == 2)  //WHITE QUEEN SIDE CASTLING
        {
            //set king to new spot/remove old spot
            chessboard[7][2].type = chessboard[7][4].type;  
            chessboard[7][2].color = chessboard[7][4].color; 
            chessboard[7][4].type = ' ';
            chessboard[7][4].color = ' ';
            //set rook to new spot/remove old spot
            chessboard[7][3].type = chessboard[7][0].type;
            chessboard[7][3].color = chessboard[7][0].color;;
            chessboard[7][0].type = ' ';
            chessboard[7][0].color = ' ';
 
        }
    }
    else if(turn % 2 == 0)     //BLACK SIDE CASTLING
    {
        if(chessboard[0][4].type == 'K' && chessboard[0][4].color == 'b' && chessboard[0][5].type == ' ' && chessboard[0][6].type == ' ' && chessboard[0][7].type == 'R' && chessboard[0][7].color == 'b' && side == 1)//BLACK KING SIDE CASTLING
        {
            //set king to new spot/remove old spot
            chessboard[0][6].type = chessboard[0][4].type;  
            chessboard[0][6].color = chessboard[0][4].color; 
            chessboard[0][4].type = ' ';
            chessboard[0][4].color = ' ';
            //set rook to new spot/remove old spot
            chessboard[0][5].type = chessboard[0][7].type;
            chessboard[0][5].color = chessboard[0][7].color;;
            chessboard[0][7].type = ' ';
            chessboard[0][7].color = ' ';
 
        }
        else if(chessboard[0][4].type == 'K' && chessboard[0][4].color == 'b' && chessboard[0][3].type == ' ' && chessboard[0][2].type == ' ' && chessboard[0][1].type == ' ' && chessboard[0][0].type == 'R' && chessboard[0][0].color == 'b' && side == 2)  //BLACK SIDE QUEEN CASTLING
        {
            //set king to new spot/remove old spot
            chessboard[0][2].type = chessboard[0][4].type;  
            chessboard[0][2].color = chessboard[0][4].color; 
            chessboard[0][4].type = ' ';
            chessboard[0][4].color = ' ';
            //set rook to new spot/remove old spot
            chessboard[0][3].type = chessboard[0][0].type;
            chessboard[0][3].color = chessboard[0][0].color;;
            chessboard[0][0].type = ' ';
            chessboard[0][0].color = ' ';

        }
    }
    
}

