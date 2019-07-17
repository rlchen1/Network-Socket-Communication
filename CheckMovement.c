/* Team 7: Seg Fault
 * *  EECS 22L Software Engineering Class
 * *  CheckMovement.c - returns array of possible destination coordinates that are legal moves
 * *  Functions: PawnCheck, RookCheck, KingCheck, QueenCheck, KnightCheck, BishopCheck
 * */

#include <stdio.h>
#include <stdlib.h>
#include "CheckMovement.h"

/**************************************************************************************************
//USE PARAMETERS (int Scol, int Srow, char color, struct PIECE chessboard[8][8]) for all functions
***************************************************************************************************/

struct MV KnightCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8]){
struct MV ps;
// int *movement;
        int n=0;
        int i =0;

       if((chessboard[Srow-2][Scol-1].color!=color)&&((Srow-2)>=0&&(Srow-2)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
        n=n+2;
              }                                                                                                                                                         
       if((chessboard[Srow-1][Scol-2].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol-2)>=0&&(Scol-2)<8)){
        n=n+2;}

       if((chessboard[Srow+1][Scol-2].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol-2)>=0&&(Scol-2)<8)){
        n=n+2;}

       if((chessboard[Srow+2][Scol-1].color!=color)&&((Srow+2)>=0&&(Srow+2)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
        n=n+2;}

       if((chessboard[Srow+2][Scol+1].color!=color)&&((Srow+2)>=0&&(Srow+2)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
        n=n+2;}

       if((chessboard[Srow+1][Scol+2].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol+2)>=0&&(Scol+2)<8)){
        n=n+2;}

       if((chessboard[Srow-1][Scol+2].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol+2)>=0&&(Scol+2)<8)){
        n=n+2;}

       if((chessboard[Srow-2][Scol+1].color!=color)&&((Srow-2)>=0&&(Srow-2)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
        n=n+2;}


       ps.movement=(int*) calloc(n,sizeof(int));


     
       if((chessboard[Srow-2][Scol-1].color!=color)&&((Srow-2)>=0&&(Srow-2)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
                ps.movement[i]=Scol-1;
                ps.movement[i+1]=Srow-2;
                i=i+2;
        }

       if((chessboard[Srow-1][Scol-2].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol-2)>=0&&(Scol-2)<8)){

                ps.movement[i]=Scol-2;
                ps.movement[i+1]=Srow-1;
                i=i+2;
        }

       if((chessboard[Srow+1][Scol-2].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol-2)>=0&&(Scol-2)<8)){

                ps.movement[i]=Scol-2;
                ps.movement[i+1]=Srow+1;
                i=i+2;
        }

       if((chessboard[Srow+2][Scol-1].color!=color)&&((Srow+2)>=0&&(Srow+2)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
                ps.movement[i]=Scol-1;
                ps.movement[i+1]=Srow+2;
                i=i+2;
        }

       if((chessboard[Srow+2][Scol+1].color!=color)&&((Srow+2)>=0&&(Srow+2)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
                ps.movement[i]=Scol+1;
                ps.movement[i+1]=Srow+2;
                i=i+2;
        }

       if((chessboard[Srow+1][Scol+2].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol+2)>=0&&(Scol+2)<8)){
                ps.movement[i]=Scol+2;
                ps.movement[i+1]=Srow+1;
                i=i+2;
        }

       if((chessboard[Srow-1][Scol+2].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol+2)>=0&&(Scol+2)<8)){
                ps.movement[i]=Scol+2;
                ps.movement[i+1]=Srow-1;
                i=i+2;
        }

	if((chessboard[Srow-2][Scol+1].color!=color)&&((Srow-2)>=0&&(Srow-2)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
                ps.movement[i]=Scol+1;
                ps.movement[i+1]=Srow-2;
        }

//        for (int i=0; i<n;i++){
//        printf( "%d", ps.movement[i]);
//        printf("\n");
//        }
	ps.n=n;
        return ps;
}

struct MV PawnCheck(int Scol, int Srow, char type, char color, char lastmove[4], struct PIECE chessboard[8][8])
{       
	struct MV ps;
	int n = 0;
	int i = 0;
	
	if (color == 'w')
	{
		if (Srow < 7 && Srow > 0) //allocation, white pawn moving forward 1 space
                {
                        if((chessboard[Srow-1][Scol].type == ' '))
                        {
                                n = n + 2;
                        }
                }
                if (Srow < 7 && Srow > 0) //allocation, white pawn standard diagonal captures 
                {
                        if((chessboard[Srow-1][Scol-1].type != ' ') && (chessboard[Srow-1][Scol-1].color!=color) && ((Scol-1)>0))
                        {
                                n = n + 2;
                        }
                        if((chessboard[Srow-1][Scol+1].type != ' ') && (chessboard[Srow-1][Scol+1].color!=color) && ((Scol+1)<8))
                        {
                                n = n + 2;
                        }
                }
                if (Srow == 3) //allocation, white pawn en passant capture condition
                {
                        if((chessboard[Srow][Scol+1].color!=color) && (chessboard[Srow][Scol+1].type=='P')) 
                        {
                                n = n + 2;
                        }
                        if((chessboard[Srow][Scol-1].color!=color) && (chessboard[Srow][Scol-1].type=='P'))
                        {
                                n = n + 2;
                        }
                }
                else if (Srow == 6) //allocation, white pawn moving forward by 2
                {
                        if((chessboard[Srow-2][Scol].type == ' ') && (chessboard[Srow-1][Scol].type == ' ')) //if both null spaces
                        {
                                n = n + 2;
                        }
		}

		ps.movement=(int*) calloc(n, sizeof(int)); //dynamically allocate memory for possible pawn movements


		if (Srow < 7 && Srow > 0) //indexing, white pawn moving forward by 1 space
		{
			if((chessboard[Srow-1][Scol].type == ' '))
			{
				 ps.movement[i] = Scol;
				 ps.movement[i+1] = Srow - 1;
				i = i + 2;	
			}
		}
		if (Srow < 7 && Srow > 0) //indexing, white pawn standard diagonal captures
		{
			if((chessboard[Srow-1][Scol-1].type != ' ') && (chessboard[Srow-1][Scol-1].color!=color) && ((Scol-1)>0))
			{
				 ps.movement[i] = Scol - 1;
				 ps.movement[i+1] = Srow - 1;
				i = i + 2;
			}
			if((chessboard[Srow-1][Scol+1].type != ' ') && (chessboard[Srow-1][Scol+1].color!=color) && ((Scol+1)<8))
			{
				 ps.movement[i] = Scol + 1;
				 ps.movement[i+1] = Srow - 1;
				i = i + 2;
			}
		}
		if (Srow == 3) //indexing, white pawn en passant capture condition
		{
			if((lastmove[0] == 'a') && (lastmove[1] == '7') && (lastmove[2] == 'a') && (lastmove[3] == '5')){
				if((chessboard[3][0].color!=color) && (chessboard[3][0].type=='P') && (chessboard[3][1].color==color) && (chessboard[3][1].type=='P'))//left EP column A
				{
					ps.movement[i] = 0;
					ps.movement[i+1] = 2;
					i = i + 2;

					chessboard[3][0].type = ' ';
					chessboard[3][0].color = ' ';
				}
			}
		
			if((lastmove[0] == 'b') && (lastmove[1] == '7') && (lastmove[2] == 'b') && (lastmove[3] == '5')){
                                if((chessboard[3][1].color!=color) && (chessboard[3][1].type=='P') && (chessboard[3][2].color==color) && (chessboard[3][2].type=='P'))//left EP column B
                                {
                                        ps.movement[i] = 1;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][1].type = ' ';
                                        chessboard[3][1].color = ' ';
                                }
				if((chessboard[3][1].color!=color) && (chessboard[3][1].type=='P') && (chessboard[3][0].color==color) && (chessboard[3][0].type=='P'))//right EP column B
                                {
                                        ps.movement[i] = 1;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][1].type = ' ';
                                        chessboard[3][1].color = ' ';
                                }
                        }

			 if((lastmove[0] == 'c') && (lastmove[1] == '7') && (lastmove[2] == 'c') && (lastmove[3] == '5')){
                                if((chessboard[3][2].color!=color) && (chessboard[3][2].type=='P') && (chessboard[3][3].color==color) && (chessboard[3][3].type=='P'))//left EP column C
                                {
                                        ps.movement[i] = 2;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][2].type = ' ';
                                        chessboard[3][2].color = ' ';
                                }
                                if((chessboard[3][2].color!=color) && (chessboard[3][2].type=='P') && (chessboard[3][1].color==color) && (chessboard[3][1].type=='P'))//right EP column C
                                {
                                        ps.movement[i] = 2;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][2].type = ' ';
                                        chessboard[3][2].color = ' ';
                                }
                        }

			if((lastmove[0] == 'd') && (lastmove[1] == '7') && (lastmove[2] == 'd') && (lastmove[3] == '5')){
                                if((chessboard[3][3].color!=color) && (chessboard[3][3].type=='P') && (chessboard[3][4].color==color) && (chessboard[3][4].type=='P'))//left EP column D
                                {
                                        ps.movement[i] = 3;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][3].type = ' ';
                                        chessboard[3][3].color = ' ';
                                }
                                if((chessboard[3][3].color!=color) && (chessboard[3][3].type=='P') && (chessboard[3][2].color==color) && (chessboard[3][2].type=='P'))//right EP column D
                                {
                                        ps.movement[i] = 3;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][3].type = ' ';
                                        chessboard[3][3].color = ' ';
                                }
                        }

			if((lastmove[0] == 'e') && (lastmove[1] == '7') && (lastmove[2] == 'e') && (lastmove[3] == '5')){
                                if((chessboard[3][4].color!=color) && (chessboard[3][4].type=='P') && (chessboard[3][5].color==color) && (chessboard[3][5].type=='P'))//left EP column E
                                {
                                        ps.movement[i] = 4;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][4].type = ' ';
                                        chessboard[3][4].color = ' ';
                                }
                                if((chessboard[3][4].color!=color) && (chessboard[3][4].type=='P') && (chessboard[3][3].color==color) && (chessboard[3][3].type=='P'))//right EP column E
                                {
                                        ps.movement[i] = 4;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][4].type = ' ';
                                        chessboard[3][4].color = ' ';
                                }
                        }

			if((lastmove[0] == 'f') && (lastmove[1] == '7') && (lastmove[2] == 'f') && (lastmove[3] == '5')){
                                if((chessboard[3][5].color!=color) && (chessboard[3][5].type=='P') && (chessboard[3][6].color==color) && (chessboard[3][6].type=='P'))//left EP column F
                                {
                                        ps.movement[i] = 5;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][5].type = ' ';
                                        chessboard[3][5].color = ' ';
                                }
                                if((chessboard[3][5].color!=color) && (chessboard[3][5].type=='P') && (chessboard[3][4].color==color) && (chessboard[3][4].type=='P'))//right EP column F
                                {
                                        ps.movement[i] = 5;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][5].type = ' ';
                                        chessboard[3][5].color = ' ';
                                }
                        }
			
			if((lastmove[0] == 'g') && (lastmove[1] == '7') && (lastmove[2] == 'g') && (lastmove[3] == '5')){
                                if((chessboard[3][6].color!=color) && (chessboard[3][6].type=='P') && (chessboard[3][7].color==color) && (chessboard[3][7].type=='P'))//left EP column G
                                {
                                        ps.movement[i] = 6;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][6].type = ' ';
                                        chessboard[3][6].color = ' ';
                                }
                                if((chessboard[3][6].color!=color) && (chessboard[3][6].type=='P') && (chessboard[3][5].color==color) && (chessboard[3][5].type=='P'))//right EP column G
                                {
                                        ps.movement[i] = 6;
                                        ps.movement[i+1] = 2;
                                        i = i + 2;

                                        chessboard[3][6].type = ' ';
                                        chessboard[3][6].color = ' ';
                                }
                        }

			if((lastmove[0] == 'h') && (lastmove[1] == '7') && (lastmove[2] == 'h') && (lastmove[3] == '5')){
				if((chessboard[3][7].color!=color) && (chessboard[3][7].type=='P') && (chessboard[3][6].color==color) && (chessboard[3][6].type=='P'))//right EP column H
				{
					ps.movement[i] = 7;
					ps.movement[i+1] = 2;
					i = i + 2;

					chessboard[3][7].type = ' ';
					chessboard[3][7].color = ' ';
				}
			} 
		}

		else if (Srow == 6) //indexing, white pawn moving forward by 2 spaces
		{
			if((chessboard[Srow-2][Scol].type == ' ') && (chessboard[Srow-1][Scol].type == ' ')) //if both null spaces
			{
				 ps.movement[i] = Scol;
				 ps.movement[i+1] = Srow - 2;	
				i = i + 2;
			}
		}
	}

	if (color == 'b')
	{
		if (Srow > 0 && Srow < 7) //allocation, black pawn moving forward by 1 space
                {
                        if((chessboard[Srow+1][Scol].type == ' '))
                        {
                                n = n + 2;
                        }
                }

                if (Srow > 0 && Srow < 7) //allocation, black pawn standard diagonal captures
                {
                        if((chessboard[Srow+1][Scol-1].type != ' ') && (chessboard[Srow+1][Scol-1].color!=color) && ((Scol-1)>0))
                        {
                                n = n + 2;
                        }
                        if((chessboard[Srow+1][Scol+1].type != ' ') && (chessboard[Srow+1][Scol+1].color!=color) && ((Scol+1)<8))
                        {
                                n = n + 2;
                        }
                }

                if (Srow == 4) //allocation, black pawn en passant capture condition
                {
                        if((chessboard[Srow][Scol+1].color!=color) && (chessboard[Srow][Scol+1].type=='P')) //TO DO: add last move parameter as condition here
                        {
                                n = n + 2;
                        }
                        if((chessboard[Srow][Scol-1].color!=color) && (chessboard[Srow][Scol-1].type=='P'))
                        {
                                n = n + 2;
                        }
                }

		else if (Srow == 1) //allocation, black pawn moving forward by 2 spaces
                {
                        if((chessboard[Srow+2][Scol].type == ' ') && (chessboard[Srow+1][Scol].type == ' ')) //if both null spaces
                        {
                                n = n + 2;
                        }
                }

		ps.movement=(int*) calloc(n, sizeof(int)); //dynamically allocate memory for possible movements


		if (Srow > 0 && Srow < 7) //indexing, black pawn moving forward by 1 space
		{
			if((chessboard[Srow+1][Scol].type == ' '))
			{
				 ps.movement[i] = Scol;
				 ps.movement[i+1] = Srow + 1;
				i = i + 2;
			}
		}
		if (Srow > 0 && Srow < 7) //indexing, black pawn standard diagonal captures
                {
                        if((chessboard[Srow+1][Scol-1].type != ' ') && (chessboard[Srow+1][Scol-1].color!=color) && ((Scol-1)>0))
                        {
                                 ps.movement[i] = Scol - 1;
                                 ps.movement[i+1] = Srow + 1;
                                i = i + 2;
                        }
                        if((chessboard[Srow+1][Scol+1].type != ' ') && (chessboard[Srow+1][Scol+1].color!=color) && ((Scol+1)<8))
                        {
                                 ps.movement[i] = Scol + 1;
                                 ps.movement[i+1] = Srow + 1;
                                i = i + 2;
                        }
                }

		if (Srow == 4) //indexing, black pawn en passant capture condition
		{
			 if((lastmove[0] == 'a') && (lastmove[1] == '2') && (lastmove[2] == 'a') && (lastmove[3] == '4')){
                                if((chessboard[4][0].color!=color) && (chessboard[4][0].type=='P') && (chessboard[4][1].color==color) && (chessboard[4][1].type=='P'))//left EP column A
                                {
                                        ps.movement[i] = 0;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][0].type = ' ';
                                        chessboard[4][0].color = ' ';
                                }
                        }

                        if((lastmove[0] == 'b') && (lastmove[1] == '2') && (lastmove[2] == 'b') && (lastmove[3] == '4')){
                                if((chessboard[4][1].color!=color) && (chessboard[4][1].type=='P') && (chessboard[4][2].color==color) && (chessboard[4][2].type=='P'))//left EP column B
                                {
                                        ps.movement[i] = 1;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][1].type = ' ';
                                        chessboard[4][1].color = ' ';
                                }
                                if((chessboard[4][1].color!=color) && (chessboard[4][1].type=='P') && (chessboard[4][0].color==color) && (chessboard[4][0].type=='P'))//right EP column B
                                {
                                        ps.movement[i] = 1;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][1].type = ' ';
                                        chessboard[4][1].color = ' ';
                                }
                        }
	
			if((lastmove[0] == 'c') && (lastmove[1] == '2') && (lastmove[2] == 'c') && (lastmove[3] == '4')){
                                if((chessboard[4][2].color!=color) && (chessboard[4][2].type=='P') && (chessboard[4][3].color==color) && (chessboard[4][3].type=='P'))//left EP column C
                                {
                                        ps.movement[i] = 2;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][2].type = ' ';
                                        chessboard[4][2].color = ' ';
                                }
                                if((chessboard[4][2].color!=color) && (chessboard[4][2].type=='P') && (chessboard[4][1].color==color) && (chessboard[4][1].type=='P'))//right EP column C
                                {
                                        ps.movement[i] = 2;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][2].type = ' ';
                                        chessboard[4][2].color = ' ';
                                }
                        }

			if((lastmove[0] == 'd') && (lastmove[1] == '2') && (lastmove[2] == 'd') && (lastmove[3] == '4')){
                                if((chessboard[4][3].color!=color) && (chessboard[4][3].type=='P') && (chessboard[4][4].color==color) && (chessboard[4][4].type=='P'))//left EP column D
                                {
                                        ps.movement[i] = 3;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][3].type = ' ';
                                        chessboard[4][3].color = ' ';
                                }
                                if((chessboard[4][3].color!=color) && (chessboard[4][3].type=='P') && (chessboard[4][2].color==color) && (chessboard[4][2].type=='P'))//right EP column D
                                {
                                        ps.movement[i] = 3;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][3].type = ' ';
                                        chessboard[4][3].color = ' ';
                                }
                        }

			if((lastmove[0] == 'e') && (lastmove[1] == '2') && (lastmove[2] == 'e') && (lastmove[3] == '4')){
                                if((chessboard[4][4].color!=color) && (chessboard[4][4].type=='P') && (chessboard[4][5].color==color) && (chessboard[4][5].type=='P'))//left EP column E
                                {
                                        ps.movement[i] = 4;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][4].type = ' ';
                                        chessboard[4][4].color = ' ';
                                }
                                if((chessboard[4][4].color!=color) && (chessboard[4][4].type=='P') && (chessboard[4][3].color==color) && (chessboard[4][3].type=='P'))//right EP column E
                                {
                                        ps.movement[i] = 4;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][4].type = ' ';
                                        chessboard[4][4].color = ' ';
                                }
                        }

			if((lastmove[0] == 'f') && (lastmove[1] == '2') && (lastmove[2] == 'f') && (lastmove[3] == '4')){
                                if((chessboard[4][5].color!=color) && (chessboard[4][5].type=='P') && (chessboard[4][6].color==color) && (chessboard[4][6].type=='P'))//left EP column F
                                {
                                        ps.movement[i] = 5;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][5].type = ' ';
                                        chessboard[4][5].color = ' ';
                                }
                                if((chessboard[4][5].color!=color) && (chessboard[4][5].type=='P') && (chessboard[4][4].color==color) && (chessboard[4][4].type=='P'))//right EP column F
                                {
                                        ps.movement[i] = 5;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][5].type = ' ';
                                        chessboard[4][5].color = ' ';
                                }
                        }

			if((lastmove[0] == 'g') && (lastmove[1] == '2') && (lastmove[2] == 'g') && (lastmove[3] == '4')){
                                if((chessboard[4][6].color!=color) && (chessboard[4][6].type=='P') && (chessboard[4][7].color==color) && (chessboard[4][7].type=='P'))//left EP column G
                                {
                                        ps.movement[i] = 6;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][6].type = ' ';
                                        chessboard[4][6].color = ' ';
                                }
                                if((chessboard[4][6].color!=color) && (chessboard[4][6].type=='P') && (chessboard[4][5].color==color) && (chessboard[4][5].type=='P'))//right EP column G
                                {
                                        ps.movement[i] = 6;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][6].type = ' ';
                                        chessboard[4][6].color = ' ';
                                }
                        }
			
			if((lastmove[0] == 'h') && (lastmove[1] == '2') && (lastmove[2] == 'h') && (lastmove[3] == '4')){
				if((chessboard[4][7].color!=color) && (chessboard[4][7].type=='P') && (chessboard[4][6].color==color) && (chessboard[4][6].type=='P'))//right EP column H
                                {
                                        ps.movement[i] = 7;
                                        ps.movement[i+1] = 5;
                                        i = i + 2;

                                        chessboard[4][7].type = ' ';
                                        chessboard[4][7].color = ' ';
                                }
			}
		}

		else if (Srow == 1) //indexing, black pawn moving forward by 2 spaces
		{
			if((chessboard[Srow+2][Scol].type == ' ') && (chessboard[Srow+1][Scol].type== ' ')) //if both null spaces
			{
				 ps.movement[i] = Scol;
				 ps.movement[i+1] = Srow + 2;
				i = i + 2;
			}
		}	
	}
	#ifdef DEBUG
	//for(int i = 0; i < n; i++) //fill the dynamically allocated memory with the possible and legal moves
	//{
	//	printf("%d\n",  ps.movement[i]);
	//}
	#endif
	ps.n=n;
	return ps;

}

struct MV RookCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8])
{
  // NOTE: The col/row parameters are int, but in the struct, they are char
  // - maybe we should create a new variable in decode input (in Chess.c)
  
  // Rook can only move forward, backward, right, or left
  // for row i, col j: can move (i-n, 0), (i+n, 0), (0, j+n), (0, j-n)
  
  //int possibleDestinations[64]; // array of possible destination coordinates
//  int *movement; // pseudo dynamic array, pointer to array
  struct MV ps; 
  int i = 0; 
  int x = 0; // index counter
  int n = 0; // size counter
  
    //Check number of possible destinations in vertical direction
    //Break from the loop when it meets a piece with the same 
    //color as the input color
    //This for loop handles upward movement
    for(i = Srow; i < 7; i++)
    {
        if(chessboard[i+1][Scol].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles downward movement
    for(i = Srow; i > 0; i--)
    {
        if(chessboard[i-1][Scol].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //Check number of possible destinations in horizontal direction
    //Break from the loop when it meets a piece with the same
    //color as the input color
    //This for loop handles rightward movement
    for(i = Scol; i < 7; i++)
    {
        if(chessboard[Srow][i+1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles leftward movement
    for(i = Scol; i > 0; i--)
    {
        if(chessboard[Srow][i-1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
  

 ps.movement = (int*) calloc(n, sizeof(int)); //like malloc, but fancy

  // Vertical Movement
  // able to move forward/backward if i <= 8/i > 0
  // can move across ROWS, but restricted by columns
 
    //This for loop handles upward movement
    for(i = Srow; i < 7; i++)
    {
        if(chessboard[i+1][Scol].color != color){
            ps.movement[x+1] = i+1;
            ps.movement[x] = Scol;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles downward movement
    for(i = Srow; i > 0; i--)
    {
        if(chessboard[i-1][Scol].color != color){
            ps.movement[x+1] = i-1;
            ps.movement[x] = Scol;
            x = x + 2;
        }
        else{
            break;
        }
    }

  // Horizontal Movement
  // able to move right/left if j <= 8/j > 0
  // can move across COLS, but restricted by rows
    
    //This for loop handles rightward movement
    for(i = Scol; i < 7; i++)
    {
        if(chessboard[Srow][i+1].color != color){
            ps.movement[x+1] = Srow;
            ps.movement[x] = i+1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles leftward movement
    for(i = Scol; i > 0; i--)
    {
        if(chessboard[Srow][i-1].color != color){
            ps.movement[x+1] = Srow;
            ps.movement[x] = i-1;
            x = x + 2;
        }
        else{
            break;
        }
    }

  // TESTING
 // for (int i = 0; i < x; i++){
 //   printf("%d, ", ps.movement[i]);
  //  if(i == x - 1){
   //     printf("\n");
   // }
 // }
  ps.n=x;
  return ps;
  //return possibleDestinations;
}

struct MV KingCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8])
{
	//King can only move forward, backward, right, left, or diagonal in any direction 1 spot
  struct MV ps;  	
//	int *movement;
	int n = 0;
	int i = 0;

	if ((chessboard[Srow+1][Scol].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol)>=0&&(Scol)<8)){
		n=n+2;
	}
	if ((chessboard[Srow-1][Scol].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol)>=0&&(Scol)<8)){
		n=n+2;
	}
	if ((chessboard[Srow][Scol+1].color!=color)&&((Srow)>=0&&(Srow)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
		n=n+2;
	}
	if ((chessboard[Srow][Scol-1].color!=color)&&((Srow)>=0&&(Srow)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
		n=n+2;
	}
	if ((chessboard[Srow+1][Scol+1].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
		n=n+2;
	}
	if ((chessboard[Srow+1][Scol-1].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
		n=n+2;
	}
	if ((chessboard[Srow-1][Scol-1].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
		n=n+2;
	}
	if ((chessboard[Srow-1][Scol+1].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
		n=n+2;
	}

	ps.movement=(int*) calloc(n,sizeof(int));

	//Vertical Movement Up
	if ((chessboard[Srow+1][Scol].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol)>=0&&(Scol)<8)){
	ps.movement[i] = Scol;
	ps.movement[i+1] = Srow+1;
	i=i+2;
	}

	//Vertical Movement Down
	if ((chessboard[Srow-1][Scol].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol)>=0&&(Scol)<8)){
	ps.movement[i] = Scol;
	ps.movement[i+1] = Srow-1;
	i=i+2;
	}

	//Horizontal Movement Right
	if ((chessboard[Srow][Scol+1].color!=color)&&((Srow)>=0&&(Srow)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
	ps.movement[i] = Scol+1;
	ps.movement[i+1] = Srow;
	i=i+2;
	}

	//Horizontal Movement Left
	if ((chessboard[Srow][Scol-1].color!=color)&&((Srow)>=0&&(Srow)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
	ps.movement[i] = Scol-1;
	ps.movement[i+1] = Srow;
	i=i+2;
	}

	//Diagonal Movement Top Right
	if ((chessboard[Srow+1][Scol+1].color!=color)&&((Srow+1)>=0&&(Srow+1)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
	ps.movement[i] = Scol+1;
	ps.movement[i+1] = Srow+1;
	i=i+2;
	}

	//Diagonal Movement Top Left
	if ((chessboard[Srow+1][Scol-1].color!=color)&&((Srow+1)>0&&(Srow+1)<8)&&((Scol-1)>0&&(Scol-1)<8)){
	ps.movement[i] = Scol-1;
	ps.movement[i+1] = Srow+1;
	i=i+2;
	}

	//Diagonal Movement Bottom Left
	if ((chessboard[Srow-1][Scol-1].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol-1)>=0&&(Scol-1)<8)){
	ps.movement[i] = Scol-1;
	ps.movement[i+1] = Srow-1;
	i=i+2;
	}

	//Diagonal Movement Bottom Right
	if ((chessboard[Srow-1][Scol+1].color!=color)&&((Srow-1)>=0&&(Srow-1)<8)&&((Scol+1)>=0&&(Scol+1)<8)){
	ps.movement[i] = Scol+1;
	ps.movement[i+1] = Srow-1;
	i=i+2;
	}

//	for (int i=0; i<n; i++){
//		printf( "%d", ps.movement[i]);
//		printf("\n");
//	}
	ps.n= n;
	return ps;
}

struct MV QueenCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8])
{
    //Queen can move vertically, horizontally, and diagonally
  //  int *movement; //declare a pointer for dynamic array
    struct MV ps;
    int i, j;  //This two variables keeps track of the location on the
               //Chess board
    int n = 0; //This variable records the length of the dynamic array
    int x = 0; //This variable keeps track of the current index of the
               //dynamic array

    //Check number of possible destinations in vertical direction
    //Break from the loop when it meets a piece with the same 
    //color as the input color
    //This for loop handles upward movement
    for(i = Srow; i < 7; i++)
    {
        if(chessboard[i+1][Scol].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles downward movement
    for(i = Srow; i > 0; i--)
    {
        if(chessboard[i-1][Scol].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //Check number of possible destinations in horizontal direction
    //Break from the loop when it meets a piece with the same
    //color as the input color
    //This for loop handles rightward movement
    for(i = Scol; i < 7; i++)
    {
        if(chessboard[Srow][i+1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles leftward movement
    for(i = Scol; i > 0; i--)
    {
        if(chessboard[Srow][i-1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //Check number of possible destinations in diagonal direction
    //Break from the loop when it meets a piece with the same
    //color as the input color
    //This for loop handles upper-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j < 7); i++, j++)
    {
        if(chessboard[j+1][i+1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles upper-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j < 7); i--, j++)
    {
        if(chessboard[j+1][i-1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j > 0); i++, j--)
    {
        if(chessboard[j-1][i+1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j > 0); i--, j--)
    {
        if(chessboard[j-1][i-1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }

    //Allocate space for dynamic array
    ps.movement = (int*) calloc(n, sizeof(int));

    //Filling in the possible destination in vertical direction
    //Through the following 2 loops
    //Break from the loop once meet a piece with the same color
    //This for loop handles upward movement
    for(i = Srow; i < 7; i++)
    {
        if(chessboard[i+1][Scol].color != color){
            ps.movement[x+1] = i+1;
            ps.movement[x] = Scol;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles downward movement
    for(i = Srow; i > 0; i--)
    {
        if(chessboard[i-1][Scol].color != color){
            ps.movement[x+1] = i-1;
            ps.movement[x] = Scol;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //Filling in the possible destination in vertical direction
    //Through the following 2 loops
    //Break from the loop once meet a piece with the same color
    //This for loop handles rightward movement
    for(i = Scol; i < 7; i++)
    {
        if(chessboard[Srow][i+1].color != color){
            ps.movement[x+1] = Srow;
            ps.movement[x] = i+1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles leftward movement
    for(i = Scol; i > 0; i--)
    {
        if(chessboard[Srow][i-1].color != color){
            ps.movement[x+1] = Srow;
            ps.movement[x] = i-1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //Check number of possible destinations in diagonal direction
    //Break from the loop when it meets a piece with the same
    //color as the input color
    //This for loop handles upper-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j < 7); i++, j++)
    {
        if(chessboard[j+1][i+1].color != color){
            ps.movement[x+1] = j + 1;
            ps.movement[x] = i + 1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles upper-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j < 7); i--, j++)
    {
        if(chessboard[j+1][i-1].color != color){
            ps.movement[x+1] = j + 1;
            ps.movement[x] = i - 1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j > 0); i++, j--)
    {
        if(chessboard[j-1][i+1].color != color){
            ps.movement[x+1] = j - 1;
            ps.movement[x] = i + 1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j > 0); i--, j--)
    {
        if(chessboard[j-1][i-1].color != color){
            ps.movement[x+1] = j - 1;
            ps.movement[x] = i - 1;
            x = x + 2;
        }
        else{
            break;
        }
    }

#ifdef DEBUG
 //   for(i = 0; i < x; i = i + 2)
//    {
  //      printf("%d %d\n",ps.movement[i], ps.movement[i+1]); 
  //  }
#endif
    ps.n=x;
    return ps;
}

struct MV BishopCheck(int Scol, int Srow, char color, struct PIECE chessboard[8][8])
{
    //Bishop can move diagonally
    struct MV ps;
    int i, j;     //This variable keeps track of the location on the
               //Chess board
    int n = 0; //This variable records the length of the dynamic array
    int x = 0; //This variable keeps track of the current index of the
               //dynamic array
               
    //Check number of possible destinations in diagonal direction
    //Break from the loop when it meets a piece with the same
    //color as the input color
    //This for loop handles upper-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j < 7); i++, j++)
    {
        if(chessboard[j+1][i+1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles upper-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j < 7); i--, j++)
    {
        if(chessboard[j+1][i-1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j > 0); i++, j--)
    {
        if(chessboard[j-1][i+1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j > 0); i--, j--)
    {
        if(chessboard[j-1][i-1].color != color){
            n = n + 2;
        }
        else{
            break;
        }
    }

    //Allocate space for dynamic array
    ps.movement = (int*) calloc(n, sizeof(int));
    
    //Check number of possible destinations in diagonal direction
    //Break from the loop when it meets a piece with the same
    //color as the input color
    //This for loop handles upper-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j < 7); i++, j++)
    {
        if(chessboard[j+1][i+1].color != color){
            ps.movement[x+1] = j + 1;
            ps.movement[x] = i + 1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles upper-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j < 7); i--, j++)
    {
        if(chessboard[j+1][i-1].color != color){
            ps.movement[x+1] = j + 1;
            ps.movement[x] = i - 1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-right movement
    for(i = Scol, j = Srow; (i < 7)&&(j > 0); i++, j--)
    {
        if(chessboard[j-1][i+1].color != color){
            ps.movement[x+1] = j - 1;
            ps.movement[x] = i + 1;
            x = x + 2;
        }
        else{
            break;
        }
    }
    //This for loop handles lower-left movement
    for(i = Scol, j = Srow; (i > 0)&&(j > 0); i--, j--)
    {
        if(chessboard[j-1][i-1].color != color){
            ps.movement[x+1] = j - 1;
            ps.movement[x] = i - 1;
            x = x + 2;
        }
        else{
            break;
        }
    }


#ifdef DEBUG
//    for(i = 0; i < x; i = i + 2)
//    {
//        printf("%d %d\n",ps.movement[i], ps.movement[i+1]); 
//    }
#endif
    ps.n=x;
    return ps;
}
