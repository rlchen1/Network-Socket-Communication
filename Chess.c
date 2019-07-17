//Main function containing: main, printMenu, displayBoard, updateBoard, decodeInput functions

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Constants.h"
#include "CheckDestination.h"
#include "CheckMovement.h"
#include "AIStrategies.h"
#include "Chess.h"

int Scol, Srow, Dcol, Drow; //converted coordinates
char Scol_in, Srow_in, Dcol_in, Drow_in; //input coordinates
int sc, sr, dc, dr;
bool ccolor;//Keep track of player color for castling, 0 for white, 1 for black
bool WK = 0; //Used to keep track of whether the white King has moved, 0 for not moved, 1 for moved
bool BK = 0; //Used to keep track of whether the black King has moved, 0 for not moved, 1 for moved
bool WRR = 0; //Used to keep track of whether the Rook on the right side has moved, 0 for not moved, 1 for moved
bool WLR = 0; //Used to keep track of whether the Rook on the left side has moved, 0 for not moved, 1 for moved
bool BRR = 0; //Used to keep track of whether the Rook on the right side has moved, 0 for not moved, 1 for moved
bool BLR = 0; //Used to keep track of whether the Rook on the left side has moved, 0 for not moved, 1 for moved
char ptype; //Used to keep track of selected piece type for log file
char coord[3]; //Used to store destination coordinate for log file
char color;
char color2 = ' '; //used for pawn color comparison
char mode = ' '; //checks for pvp or player vs AI
char hintmode = ' '; //checks for hint mode on or off
int turn = 1; //alternates player turns
int myturn = 1; //used in AI turn alternation
int startturn = 1; //set white to have first move if player chooses black
int count = 1;
int check = 0; //check if king is in check 
int Exit = 0; //checks user input-based exit
int castleflow = 0; //check if castling
int whitecastle = 0; //if white has not castled yet
int blackcastle = 0; //if black has not castled yet
int myturncastle = 0; //player vs AI, if player has not castled yet
struct PIECE chessboard[8][8];
char whitelastmove[4]; //stores the last move made(src,dest), used in en passant
char blacklastmove[4]; //stores the last move made(src,dest), used in en passant
char castle = ' '; //takes y or n input to call Castling function
char side_in = ' '; //chooses side for castling q or k
int checkmate = 0;

void printMenu();
void decodeInput();
void displayBoard();
void updateBoard(char color);
int Chessmain();

void printMenu(){

    int err = 0;
    bool bf = 0;
    bool rf = 0;
    char date[20];
    char DnTm[20];
    char *fname;
    time_t t = time(NULL);
    struct tm *TM = localtime(&t);
    struct MV move;
    strftime(date, 19, "%Y%m%d%H%M", TM); 
    date[19] = 0;
    strftime(DnTm, 19, "%Y-%m-%d, %H:%M", TM);
    date[19] = 0; 
    if((fname = malloc(strlen("Log_.txt")+strlen(date)+1)) != NULL){
        fname[0] = '\0';
        strcat(fname, "Log_");
        strcat(fname, date);
        strcat(fname, ".txt");
    }
    char pcol[2];
    FILE *file = fopen(fname, "w");
        char Head[40];
        Head[0] = '\0';
        strcat(Head, "Game starts at: ");
        strcat(Head, DnTm);
        fprintf(file, Head);

	printf("\n\nWelcome to Medieval Warfare!\n");

	printf("\nHint mode prints all the possible moves of a selected piece.\n");
	while(hintmode != 'Y' || hintmode != 'y' || hintmode != 'N' || hintmode != 'n'){
		printf("Enable hint mode? (Y/N) :\n");
		scanf(" %c", &hintmode); 
		if(hintmode == 'Y' || hintmode == 'y' || hintmode == 'N' || hintmode == 'n'){
			break;}
	} //end hintmode error check
	while(mode != '1' || mode!= '2'){
	printf("Select game mode:\n");
	printf("1 : Player vs Player\n");
	printf("2 : Player vs AI\n");
	scanf(" %c", &mode);
	if(mode == '1' || mode == '2'){
		break;}
	}
	if(mode == '1'){
		printf("Player vs. Player mode selected!\n");}
	else if(mode == '2'){
		printf("Player vs. AI mode selected!\n");}

	while((color != 'b') || (color != 'B') || (color != 'w') || (color != 'W')){
	    printf("\nSelect your color (Black or White)\n");
	    printf("'B' for Black and 'W' for White: ");
	    scanf(" %c", &color);
		if(((color == 'b') && (mode == '2')) || ((color == 'B') && (mode == '2'))){
			turn = 2;
			myturn = 2;
			color2 = 'w';
			fprintf(file, "\nPlayer 1 is Black, AI is White\n");
			break;}
		else if(((color == 'w') && (mode == '2')) || ((color == 'W') && (mode == '2'))){
			color2 = 'b';
			fprintf(file, "\nPlayer 1 is White, AI is Black\n");
			break;}
		else if(((color == 'b') && (mode == '1')) || ((color == 'B') && (mode == '1'))){
			turn = 2;
			myturn = 2;
			color2 = 'w';
			fprintf(file, "\nPlayer 1 is Black, Player 2 is White\n");
			break;}
		else if(((color == 'w') && (mode == '1')) || ((color == 'W') && (mode == '1'))){
			color2 = 'b';
			fprintf(file, "\nPlayer 1 is White, Player 2 is Black\n");
			break;}
	
	} //end while(color != b)
	displayBoard();

if(mode == '1'){	
	while (checkmate != 1) //set checkmate = 1 if in checkmate(king has no possible legal moves, pieces cannot block)
	{
	    while(startturn != 0){
		turn = 1; //works for PvP
		startturn--;}
		
	    if (turn % 2 == 1){
		turn = 1;}
	    else if (turn % 2 == 0){
		turn = 2;}
	
	    if (turn == 1){
		printf("It is White's turn.\n");
                fprintf(file, "White: ");}
	    else if (turn == 2){
		printf("It is Black's turn.\n");
                fprintf(file, "Black: ");}

	    do{
                err = 0;
			// CASTLING
			if(turn%2==1){
			    ccolor = 0;
			}
			else{
			    ccolor = 1;
			}
			if(((ccolor==0)&&(WK==0)&&((WRR==0)||(WLR==0))&&(((chessboard[7][5].type==' ')&&(chessboard[7][6].type==' '))||((chessboard[7][3].type==' ')&&(chessboard[7][2].type==' ')&&(chessboard[7][1].type==' '))))||((ccolor==1)&&(BK==0)&&((BRR==0)||(BLR==0))&&(((chessboard[0][5].type==' ')&&(chessboard[0][6].type==' '))||((chessboard[0][3].type==' ')&&(chessboard[0][2].type==' ')&&(chessboard[0][1].type==' '))))){
			if(((((turn%2)==1) && (whitecastle == 0)) || (((turn%2)==0) && (blackcastle == 0)))){ //if player turn has not castled yet, print this section
			printf("Would you like to castle? y/n ");
			scanf(" %c", &castle);
			if ((castle == 'y') || (castle == 'Y')){
				printf("Would you like to castle on the queen's side or king's side?\n");
				printf("Please enter 'K' for king's side or 'Q' for queen's side: ");
				scanf(" %c", &side_in);
				if ((side_in == 'K') || (side_in == 'k')){
					castleflow = 0;
					if((turn%2)==1){
						whitecastle = 1;}
					else if((turn%2)==0){
						blackcastle = 1;}
					Castling(chessboard, 1, turn);
					break;
				}
				else if ((side_in == 'Q') || (side_in == 'q')){
					castleflow = 0;
					if((turn%2)==1){
						whitecastle = 1;}
					else if((turn%2)==0){
						blackcastle = 1;}
					Castling(chessboard, 2, turn);
					break;
				}
			} //end if castle = y
				else{
					printf("Castling off.\n");
					castleflow = 1;}	
			} //end if player has not castled before
			else{
				castleflow = 1;} // if both sides have castled, always set castleflow to 1
		}//end giant if
		else{
		    castleflow = 1;
		}
		if(castleflow == 1){
			printf("Please enter the coordinates for the piece you would like to move. 9 to quit.\n");
                do{
	            printf("Column (a-h): ");
	            scanf(" %c", &Scol_in);
                    if(Scol_in!='9'){
                        if((((int)Scol_in)<97)||(((int)Scol_in)>104)){
                            printf("Invalid Input!\n");
                            rf = 1;
                        }
                        else{
                            rf = 0;
                        }
                    }
                }while(rf == 1); 
		if((turn%2)== 1){
			whitelastmove[0] = Scol_in;} //store to last move array
		else if((turn%2)== 0){
			blacklastmove[0] = Scol_in;} //store to last move array
		if(Scol_in == '9'){
			Exit = 1;
			break;}			
                do{
	            printf("Row (1-8): ");	
	            scanf(" %c", &Srow_in);
                    if((((int)Srow_in)<49)||(((int)Srow_in)>56)){
                        printf("Invalid Input!\n");
                        rf = 1;
                    }
                    else{
                        rf = 0;
                    }
                }while(rf == 1);
		if((turn%2)==1){
			whitelastmove[1] = Srow_in;} //store to last move array
		else if((turn%2)== 0){
			blacklastmove[1] = Srow_in;} //store to last move array
	        decodeInput();
                if((turn == 1) && (chessboard[Srow][Scol].color != 'w')){
                    printf("\nERROR! - Invalid Choice!\n");
                    printf("You cannot choose that piece!\n");
                    printf("\nIt is White's turn.\n");
		    err = 1;
                }
                else if((turn == 2) && (chessboard[Srow][Scol].color != 'b')){
                    printf("\nERROR! - Invalid Choice!\n");
                    printf("You cannot choose that piece!\n");
                    printf("\nIt is Black's turn.\n");
		    err = 1;
                }
	    }//end if castleflow = 1
	}//end do loop
	    while(err != 0);
            if(Exit == 1)
            {
                break;
            }	

            switch(chessboard[Srow][Scol].type)
            {
                case 'P':
			if((turn%2) == 1){
		    move=PawnCheck(Scol, Srow, chessboard[Srow][Scol].type, chessboard[Srow][Scol].color, blacklastmove, chessboard);}
			else if((turn%2) == 0){
		    move=PawnCheck(Scol, Srow, chessboard[Srow][Scol].type, chessboard[Srow][Scol].color, whitelastmove, chessboard);}
                    printf("You selected a Pawn.\n");
                    break;
                case 'B':
		    move=BishopCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected a Bishop.\n");
                    break;
                case 'N':
		    move=KnightCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected a Knight.\n");
                    break;
                case 'R':
		    move=RookCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected a Rook.\n");
                    break;
                case 'Q':
		    move=QueenCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected the Queen.\n");
                    break;
                case 'K':
		    move=KingCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected the King.\n");
                    break;
                default: 
                    break;
            }
           // printf("move.n = %d\n", move.n);
           if(castleflow == 1){
	  //  do{
                err = 0;
	        printf("Where would you like to move to? 9 to quit.\n");
		if (hintmode == 'Y' || hintmode == 'y'){
		printf("Possible moves: ");
		for (int i=0;i<move.n;i=i+2){
			printf("(%c,%c) ", (char)(move.movement[i]+97), (char)(56-move.movement[i+1]));
			}
		printf("\n");
		}
                do{
	            printf("Column (a-h): ");
	            scanf(" %c", &Dcol_in);
                    if(Dcol_in!='9'){
                        if((((int)Dcol_in)<97)||(((int)Dcol_in)>104)){
                            printf("Invalid Input!\n");
                            rf = 1;
                        }
                        else{
                            rf = 0;
                        }
                    }
                }while(rf == 1); 
		if(Dcol_in == '9'){
			Exit = 1;
			break;}
		if((turn%2)== 1){
			whitelastmove[2] = Dcol_in;} //store to last move array
		else if((turn%2)== 0){
			blacklastmove[2] = Dcol_in;} //store to last move array
                do{
	            printf("Row (1-8): ");	
	            scanf(" %c", &Drow_in);
                    if((((int)Drow_in)<49)||(((int)Drow_in)>56)){
                        printf("Invalid Input!\n");
                        rf = 1;
                    }
                    else{
                        rf = 0;
                    }
                }while(rf == 1);
	        printf("\n");
		if((turn%2)== 1){
			whitelastmove[3] = Drow_in;} //store to last move array
		else if((turn%2)== 0){
			blacklastmove[3] = Drow_in;} //store to last move array
                decodeInput();
		int tester = 0;
		int counter;
		counter = move.n;
		for (int i=0;i<counter;i=i+2){
			if((move.movement[i] == Dcol)&&(move.movement[i+1] == Drow)){
				tester++;}
		}
                if((turn == 1) && (chessboard[Drow][Dcol].color == 'w')){
                    printf("ERROR! - Invalid Choice!\n");
                    printf("You cannot move your piece to that coordinate!\n");
                    err = 1;
                }
                else if((turn == 2) && (chessboard[Drow][Dcol].color == 'b')){
                    printf("ERROR! - Invalid Choice!\n");
                    printf("You cannot move your piece to that coordinate!\n");
                    err = 1;
                } 
		if(tester==0) {
		printf("ERROR! - Invalid Choice!\n");
		printf("That is not a valid move for that piece type!\n\n");
		turn++;
		}
           // }//end do loop
	}//end if castle = 1 
	while(err != 0);
            if(Exit == 1)
            {
                break;
            }	
            coord[0] = Dcol_in;
            coord[1] = Drow_in;
            coord[2] = 0;	
	    switch (chessboard[Srow][Scol].type)
	    {
		case 'P': 
			pcol[0] = Scol_in;
                        pcol[1] = 0;
                        if(chessboard[Drow][Dcol].color != ' '){
                            fprintf(file, pcol);
                            fprintf(file, "x");
                        }
                        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			PawnPromotion(chessboard, Dcol, Drow, color, color2, chessboard[Drow][Dcol].type, move);
			break;
		case 'R':
                        fprintf(file, "R");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
		        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
			if((Scol == 0)&&(Srow == 7)){
			    WLR = 1;
			}
			else if((Scol == 7)&&(Srow == 7)){
			    WRR = 1;
			}
			else if((Scol == 0)&&(Srow == 0)){
			    BLR = 1;
			}
			else if((Scol == 7)&&(Srow == 0)){
			    BRR = 1;
			}
			if((WLR==1)&&(WRR==1)){
			    whitecastle = 1;
                        }
			else if((BLR==1)&&(BRR==1)){
			    blackcastle = 1;
                        }
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'N':
                        fprintf(file, "N");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
			MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'B':
                        fprintf(file, "B");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
			MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'Q':
                        fprintf(file, "Q");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
                        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'K':
                        fprintf(file, "K");
			if((Scol == 4)&&(Srow == 7)){
			    WK = 1;
			    whitecastle = 1;
                        }
			if((Scol == 4)&&(Srow == 0)){
			    BK = 1;
			    blackcastle = 1;
			}
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
                        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		default:
			break;
	    }
	updateBoard(color);
	 if((turn%2)==1){  
	 check = Check(chessboard, color, color2, blacklastmove, chessboard[Srow][Scol].type);} //after MovePiece executed, see if enemy king is in check
	 else if((turn%2)==0){
	 check = Check(chessboard, color, color2, whitelastmove, chessboard[Srow][Scol].type);}
	    if(check == 1 && ((turn % 2) == 1)){
		printf("Black is in check!\n");
                for(int i = 0; i < 8; i++)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        if((chessboard[i][j].type=='K')&&(chessboard[i][j].color==color)){
                            Srow = i; 
                            Scol = j;
                            bf = 1;
                            break;
                        }
                    }
                    if(bf==1)
                    {
                        break;
                    }
                }
                    move = KingCheck(Scol, Srow, 'b', chessboard);
                    if(move.n == 0){
                        printf("Black is in Checkmate!\n");
                        printf("Black lose..\n");
                        exit(1);
                    }
                }
	    else if(check == 1 && ((turn % 2) == 0)){
		printf("White is in check!\n");
                for(int i = 0; i < 8; i++)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        if((chessboard[i][j].type=='K')&&(chessboard[i][j].color==color)){
                            Srow = i; 
                            Scol = j;
                            bf = 1;
                            break;
                        }
                    }
                    if(bf==1)
                    {
                        break;
                    }
                }
                    move = KingCheck(Scol, Srow, 'w', chessboard);
                    if(move.n == 0){
                        printf("White is in Checkmate!\n");
                        printf("White lose..\n");
                        exit(1);
                    }
            }
	 
            turn++;
	} //end while(checkmate != 1)
	} //end if(mode == 1) 


if(mode == '2'){
	while (checkmate != 1) //set checkmate = 1 if in checkmate(king has no possible legal moves, pieces cannot block)
	{
	    while(startturn != 0){
		turn = 1; //works for PvP
		startturn--;}
		
	    if (turn % 2 == 1){
		turn = 1;}
	    else if (turn % 2 == 0){
		turn = 2;}
	
	    if (turn == 1){
		printf("It is White's turn.\n");
                fprintf(file, "White: ");}
	    else if (turn == 2){
		printf("It is Black's turn.\n");
                fprintf(file, "Black: ");}

//	printf("DEBUG: myturn = %d\n", myturn);
	if((myturn%2) == 1){
		do{
                err = 0;
		//CASTLING
		if(((color=='w')&&(WK==0)&&((WRR==0)||(WLR==0))&&(((chessboard[7][5].type==' ')&&(chessboard[7][6].type==' '))||((chessboard[7][3].type==' ')&&(chessboard[7][2].type==' ')&&(chessboard[7][1].type==' '))))){

			printf("Would you like to castle? y/n ");
                        scanf(" %c", &castle);
                        if(castle == 'y' || castle == 'Y'){
                                printf("Would you like to castle on the queen's side or king's side?\n");
                                printf("Please enter 'K' for king's side or 'Q' for queen's side: ");
                                scanf(" %c", &side_in);
                                if((side_in == 'K') || (side_in == 'k')){
                                        castleflow = 0;
                                        Castling(chessboard, 1, turn);
                                        break;}
                                else if((side_in == 'Q') || (side_in == 'q')){
                                        castleflow = 0;
                                        Castling(chessboard, 2, turn);
                                        break;}
                        } //end if castle = y
                        else{
                                printf("Castling off.\n");
                                castleflow = 1;} //end else if castle = n
                } //end if player has not castled before
                else{
                        castleflow = 1;} //if player has castled, always set castleflow = 1


		if((color=='b')&&(BK==0)&&((BRR==0)||(BLR==0))&&(((chessboard[0][5].type==' ')&&(chessboard[0][6].type==' '))||((chessboard[0][3].type==' ')&&(chessboard[0][2].type==' ')&&(chessboard[0][1].type==' ')))){

			printf("Would you like to castle? y/n ");
			scanf(" %c", &castle);
			if(castle == 'y' || castle == 'Y'){
				printf("Would you like to castle on the queen's side or king's side?\n");
				printf("Please enter 'K' for king's side or 'Q' for queen's side: ");
				scanf(" %c", &side_in);
				if((side_in == 'K') || (side_in == 'k')){
					castleflow = 0;
					Castling(chessboard, 1, turn);
					break;}
				else if((side_in == 'Q') || (side_in == 'q')){
					castleflow = 0;
					Castling(chessboard, 2, turn);
					break;}
			} //end if castle = y
			else{
				printf("Castling off.\n");
				castleflow = 1;} //end else if castle = n
		} //end if player has not castled before
		else{
			castleflow = 1;} //if player has castled, always set castleflow = 1

	if(castleflow == 1){
	        printf("Please enter the coordinates for the piece you would like to move. 9 to quit.\n");
                do{
	            printf("Column (a-h): ");
	            scanf(" %c", &Scol_in);
		   // sprintf(move, "%s", Scol_in);
                    if(Scol_in!='9'){
                        if((((int)Scol_in)<97)||(((int)Scol_in)>104)){
                            printf("Invalid Input!\n");
                            rf = 1;
                        }
                        else{
                            rf = 0;
                        }
                    }
                }while(rf == 1); 
		if(Scol_in == '9'){
			Exit = 1;
			break;}			
                do{
	            printf("Row (1-8): ");	
	            scanf(" %c", &Srow_in);
	//	    sprintf(move2, "%s", Srow_in);
                    if((((int)Srow_in)<49)||(((int)Srow_in)>56)){
                        printf("Invalid Input!\n");
                        rf = 1;
                    }
                    else{
                        rf = 0;
                    }
                }while(rf == 1);
	        decodeInput();

                if((turn == 1) && (chessboard[Srow][Scol].color != 'w')){
                    printf("\nERROR! - Invalid Choice!\n");
                    printf("You cannot choose that piece!\n");
                    printf("\nIt is White's turn.\n");
		    err = 1;
                }
                else if((turn == 2) && (chessboard[Srow][Scol].color != 'b')){
                    printf("\nERROR! - Invalid Choice!\n");
                    printf("You cannot choose that piece!\n");
                    printf("\nIt is Black's turn.\n");
		    err = 1;
                }
	    }// end if castleflow = 1
	} //end do loop
	 while(err!=0);
	}//end if myturn
	else if ((myturn%2) == 0){
		if(color == 'w'){
	RandomMove(file, chessboard, color2, blacklastmove, check);
	check = Check(chessboard, color, color2, blacklastmove, chessboard[Srow][Scol].type);} //AI Check Fix
		else if(color == 'b'){
	RandomMove(file, chessboard, color2, whitelastmove, check);
        check = Check(chessboard, color, color2, whitelastmove, chessboard[Srow][Scol].type);} //AI Check Fix
	} //end else if (myturn%2 == '0')
	//while(err != 0); //executes for both sides
            if(Exit == 1)
            {
                break;
            }	

	            switch(chessboard[Srow][Scol].type)
            {
                case 'P':
		    if((turn%2)==1){
		   	 move=PawnCheck(Scol, Srow, chessboard[Srow][Scol].type, chessboard[Srow][Scol].color, blacklastmove, chessboard);}
		    else if((turn%2)==0){
			 move=PawnCheck(Scol, Srow, chessboard[Srow][Scol].type, chessboard[Srow][Scol].color, whitelastmove, chessboard);}
                    printf("You selected a Pawn.\n");
                    break;
                case 'B':
		    move=BishopCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected a Bishop.\n");
                    break;
                case 'N':
		    move=KnightCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected a Knight.\n");
                    break;
                case 'R':
		    move=RookCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected a Rook.\n");
                    break;
                case 'Q':
		    move=QueenCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected the Queen.\n");
                    break;
                case 'K':
		    move=KingCheck(Scol, Srow, chessboard[Srow][Scol].color, chessboard);
                    printf("You selected the King.\n");
                    break;
                default: 
                    break;
            }
		
	if(((myturn%2) == 1) && (castleflow == 1)){ //executes only for the player
                err = 0;
	        printf("Where would you like to move to? 9 to quit.\n");
		if (hintmode == 'Y' || hintmode == 'y'){
		printf("Possible moves: ");
		for (int i=0; i<move.n; i=i+2){
			printf("(%c,%c) ", (char)(move.movement[i]+97), (char)(56-move.movement[i+1]));
			}
		printf("\n");
		}
                do{
	            printf("Column (a-h): ");
	            scanf(" %c", &Dcol_in);
	//	    sprintf(move3, "%s", Dcol_in);
                    if(Dcol_in!='9'){
                        if((((int)Dcol_in)<97)||(((int)Dcol_in)>104)){
                            printf("Invalid Input!\n");
                            rf = 1;
                        }
                        else{
                            rf = 0;
                        }
                    }
                }while(rf == 1);
		if(Dcol_in == '9'){
			Exit = 1;
			break;}
                do{
	            printf("Row (1-8): ");	
	            scanf(" %c", &Drow_in);
	//	    sprintf(move4, "%s", Drow_in);
                    if((((int)Drow_in)<49)||(((int)Drow_in)>56)){
                        printf("Invalid Input!\n");
                        rf = 1;
                    }
                    else{
                        rf = 0;
                    }
                }while(rf == 1);
	        printf("\n");
                decodeInput();
		/*
		strncpy(protocol, "MOV_", 256);
		strcat(protocol, move);
		strcat(protocol, "_");
		strcat(protocol, move2);
		strcat(protocol, "_");
		strcat(protocol, move3);
		strcat(protocol, "_");
		strcat(protocol, move4);
		strcat(protocol, "\n")l
		printf(%s", protocol);
*/
		//TO DO: error message if source is valid, destination is invalid (not within possible moves)
		int tester = 0;
		int counter;
		counter = move.n;
		for (int i=0;i<counter;i=i+2){
			if((move.movement[i] == Dcol)&&(move.movement[i+1] == Drow)){
				tester++;}
		}
                if((turn == 1) && (chessboard[Drow][Dcol].color == 'w')){
                    printf("ERROR! - Invalid Choice!\n");
                    printf("You cannot move your piece to that coordinate!\n");
                    err = 1;
                }
                else if((turn == 2) && (chessboard[Drow][Dcol].color == 'b')){
                    printf("ERROR! - Invalid Choice!\n");
                    printf("You cannot move your piece to that coordinate!\n");
                    err = 1;
                } 
		if(tester==0) {
		printf("ERROR! - Invalid Choice!\n");
		printf("That is not a valid move for that piece type!\n\n");
		turn++;
		}
		
	 }//end if (myturn == '1') err = 0
	while(err != 0); //what is this while loop?????????
            if(Exit == 1)
            {
                break;
            }	
            coord[0] = Dcol_in;
            coord[1] = Drow_in;
            coord[2] = 0;	
	if((myturn%2) == 1){
	    switch (chessboard[Srow][Scol].type) //executes for both sides
	    {
		case 'P': 
			pcol[0] = Scol_in;
                        pcol[1] = 0;
                        if(chessboard[Drow][Dcol].color != ' '){
                            fprintf(file, pcol);
                            fprintf(file, "x");
                        }
                        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			PawnPromotion(chessboard, Dcol, Drow, color, color2, chessboard[Drow][Dcol].type, move);
			break;
		case 'R':
                        fprintf(file, "R");
			if((Scol == 0)&&(Srow == 7)){
			    WLR = 1;
			}
			else if((Scol == 7)&&(Srow == 7)){
			    WRR = 1;
			}
			else if((Scol == 0)&&(Srow == 0)){
			    BLR = 1;
			}
			else if((Scol == 7)&&(Srow == 0)){
			    BRR = 1;
			}
			if((WLR==1)&&(WRR==1)){
			    whitecastle = 1;
                        }
			else if((BLR==1)&&(BRR==1)){
			    blackcastle = 1;
                        }
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
		        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'N':
                        fprintf(file, "N");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
			MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'B':
                        fprintf(file, "B");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
			MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'Q':
                        fprintf(file, "Q");
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
                        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		case 'K':
                        fprintf(file, "K");
			if((Scol == 4)&&(Srow == 7)){
			    WK = 1;
			    whitecastle = 1;
                        }
			if((Scol == 4)&&(Srow == 0)){
			    BK = 1;
			    blackcastle = 1;
			}
                        if(chessboard[Drow][Dcol].type != ' '){
                            fprintf(file, "x");
                        }
                        MovePiece(chessboard, Scol, Srow, Dcol, Drow, move);
                        fprintf(file, coord);
                        fprintf(file, "\n");
			break;
		default:
			break;
	    }
	}//end if(myturn%2) == 1)
	updateBoard(color);
	    if((myturn%2)==1){
	    	check = Check(chessboard, color, color2, blacklastmove, chessboard[Srow][Scol].type);} //after MovePiece executed, see if enemy king is in check
	    else if((myturn%2)==0){
	    	check = Check(chessboard, color, color2, whitelastmove, chessboard[Srow][Scol].type);}
	    if(check == 1 && ((myturn%2)==1)){
		printf("The AI is in check!\n");}
	    else if(check == 1 && ((myturn%2)==0)){
		printf("You are in check!\n");
                for(int i = 0; i < 8; i++)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        if((chessboard[i][j].type=='K')&&(chessboard[i][j].color==color)){
                            Srow = i; 
                            Scol = j;
                            bf = 1;
                            break;
                        }
                    }
                    if(bf==1)
                    {
                        break;
                    }
                }
                    move = KingCheck(Scol, Srow, color, chessboard);
                    if(move.n == 0){
                        printf("You're in Checkmate!\n");
                        printf("You lose..\n");
                        exit(1);
                    }
            }
	 
            turn++;
	    myturn++;
	} //end while(checkmate != 1)		
} //end if(mode == 2)
    fname = NULL;
    free(fname);
    fclose(file);
}


void decodeInput(){
	//DECODE INPUT: converts character input to integers
	Scol = ((int)Scol_in)-97;
	Srow = (((int)Srow_in)-2*(((int)Srow_in)-52))-48;
	Dcol = ((int)Dcol_in)-97;
	Drow = (((int)Drow_in)-2*(((int)Drow_in)-52))-48;
}

void updateBoard(char color){
	for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
                        if (j == 0){
                                printf("%d", 8-i);
                        }
                        printf("|%c%c|", chessboard[i][j].color, chessboard[i][j].type);
                        if (j == 7){
                                printf("\n");
                                printf("----------------------------------\n");
                        }
        }
        }
        printf("   a   b   c   d   e   f   g   h\n");

}

void displayBoard(){

	for (int x = 2; x < 6; x++){
		for (int y = 0; y < 8; y++){
			chessboard[x][y].color = ' ';
			chessboard[x][y].type = ' ';
		}
	}
	// sets colors
	for (int y = 0; y < 8; y++){
		chessboard[0][y].color = 'b';
		chessboard[1][y].color = 'b';
	}
	for (int y = 0; y < 8; y++){
		chessboard[6][y].color = 'w';
		chessboard[7][y].color = 'w';
	}
	// sets pawns
	for (int y = 0; y < 8; y++){
		chessboard[1][y].type = 'P';
		chessboard[6][y].type = 'P';
	}
	// sets rooks
	chessboard[0][0].type = 'R';
	chessboard[0][7].type = 'R';
	chessboard[7][0].type = 'R';
	chessboard[7][7].type = 'R';
	// sets knights
	chessboard[0][1].type = 'N';
	chessboard[0][6].type = 'N';
	chessboard[7][1].type = 'N';
	chessboard[7][6].type = 'N';
	// sets brooks
	chessboard[0][2].type = 'B';
	chessboard[0][5].type = 'B';
	chessboard[7][2].type = 'B';
	chessboard[7][5].type = 'B';
	// sets queens
	chessboard[0][3].type = 'Q';
	chessboard[7][3].type = 'Q';
	// sets kings
	chessboard[0][4].type = 'K';
	chessboard[7][4].type = 'K';
	// prints
	for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
			if (j == 0){
				printf("%d", 8-i);
			}
			printf("|%c%c|", chessboard[i][j].color, chessboard[i][j].type);
			if (j == 7){
				printf("\n");
				printf("----------------------------------\n");
			}
        }        
        }
        printf("   a   b   c   d   e   f   g   h\n"); 
}

//int main(){
int main(){
	//struct MV ai;	
	while(Exit != 1)
	{
		printMenu(mode);
	}
	
	//ai= KnightCheck(2,7,'w',chessboard);
       // for (int i=0; i<ai.n;i++){
       // printf( "%d", ai.movement[i]);
       // printf("\n");
        //}

	 
	printf("You exit the chess program.\n");
	return 0;
}
