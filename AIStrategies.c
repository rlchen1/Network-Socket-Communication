/* This file contains the strategies that the AI use */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "AIStrategies.h"
#include "CheckMovement.h"
#include "CheckDestination.h"
#include "Constants.h"

//RandomMove allows the AI to randomly choose a piece
//on the broad and move to the first coordinate in
//the possible move array return by the CheckMovement
//functions. The first 8 steps are hard coded to move 
//all the pawns away from their orignal position

void RandomMove(FILE *file, struct PIECE chessboard[8][8], char AIcolor, char lastmove[4],int check)
{
    struct MV pm; 
    int scol, srow;
    int dcol, drow;
    int s;
    int i;
    int j, k;
    static int step = 1;
    int bflag = 0;
    int eflag = 0;
    char oppo;
    char ptype;
    char p[2];
    char aic1[8];
    char dest[3];

    srand(time(NULL));
    if(AIcolor == 'w'){
        strcat(aic1, "White: ");
    }
    else{
        strcat(aic1, "Black: ");
    }
    if(AIcolor == 'w'){
        oppo = 'b';
    }
    else{
        oppo = 'w';
    }
    //Fake king side castling
    //Step 1: Move the pawn in front of the King
    if((step == 1)&&(AIcolor == 'b')){
        scol = 4;
        srow = 1;
        dcol = 4;
        drow = 3;
    }
    else if((step == 1)&&(AIcolor == 'w')){
        scol = 4;
        srow = 6;
        dcol = 4;
        drow = 4;
    }
    //Step 2: Move the Bishop between the King and the right side Rook
    else if((step == 2)&&(AIcolor == 'b')){
        scol = 5;
        srow = 0;
        dcol = 2;
        drow = 3;
    }
    else if((step == 2)&&(AIcolor == 'w')){
        scol = 5;
        srow = 7;
        dcol = 2;
        drow = 4;
    }
    //Step 3: Move the knight between the King and the right side Rook
    else if((step == 3)&&(AIcolor == 'b')){
        scol = 6;
        srow = 0;
        dcol = 5;
        drow = 2;
    }
    else if((step == 3)&&(AIcolor == 'w')){
        scol = 6;
        srow = 7;
        dcol = 5;
        drow = 5;
    }
    //Step 4: Move the King and execute King side castling
    else if((step == 4)&&(AIcolor == 'b')){
        scol = 4;
        srow = 0;
        dcol = 6;
        drow = 0;
	chessboard[drow][dcol].type = chessboard[srow][scol].type;
        chessboard[drow][dcol].color = chessboard[srow][scol].color;
        chessboard[srow][scol].type = ' ';
        chessboard[srow][scol].color = ' ';
        dest[0] = (char)(dcol+97);
        dest[1] = (char)(56-drow);
        dest[2] = 0;
        fprintf(file, "K");
        fprintf(file, dest);
        fprintf(file, "\n");
        sleep(1.5);
        printf("The AI moves the piece at %c%c to %c%c. \n", (char)(scol+97), (char)(56-srow), (char)(dcol+97), (char)(56-drow));
        scol = 7;
        srow = 0;
        dcol = 5;
        drow = 0;
        printf("King side Castling executed\n");
        fprintf(file, "Black: King side Castling\n");
        fprintf(file, "Black: ");
    }
    else if((step == 4)&&(AIcolor == 'w')){
        scol = 4;
        srow = 7;
        dcol = 6;
        drow = 7;
	chessboard[drow][dcol].type = chessboard[srow][scol].type;
        chessboard[drow][dcol].color = chessboard[srow][scol].color;
        chessboard[srow][scol].type = ' ';
        chessboard[srow][scol].color = ' ';
        dest[0] = (char)(dcol+97);
        dest[1] = (char)(56-drow);
        dest[2] = 0;
        fprintf(file, "K");
        fprintf(file, dest);
        fprintf(file, "\n");
        sleep(1.5);
        printf("The AI moves the piece at %c%c to %c%c. \n", (char)(scol+97), (char)(56-srow), (char)(dcol+97), (char)(56-drow));
        scol = 7;
        srow = 7;
        dcol = 5;
        drow = 7;
        printf("King side Castling executed\n");
        fprintf(file, "White: King side Castling\n");
        fprintf(file, "White: ");
    }
    //The following code  randomly picks a 
    //piece and find it's possible destinations.
    //If there's no possible moves for the piece,
    //another number will be generated. It will
    //continue this process until it finds a piece
    //that have at least one possible legal move. 
    //And then the first coordinate in the legal
    //move array will be picked as the destination
    //of that piece.
    else if(step > 4){
        if(check == 1){
            ptype = 'K';
            for(j = 0; j < 8; j++)
            {
                for(k = 0; k < 8; k++)
                {
                     if((chessboard[j][k].type == ptype)&&(chessboard[j][k].color == AIcolor)){
                         srow = j;
                         scol = k;
                         bflag = 1;
                         break;
                     }
                }
                if(bflag == 1){
                   break;
                }
            }
            pm = KingCheck(scol, srow, AIcolor, chessboard);
            if(pm.n == 0){
                printf("There's no possible move for the King. AI is in Checkmate.\n");
                printf("Congratulations! You win the game! \n");
                exit(1);
            }
            else{
                s = rand() % pm.n;
                if(s % 2 == 0){
                    dcol = pm.movement[s];
                    drow = pm.movement[s+1];
                }
                else{
                    dcol = pm.movement[s-1];
                    drow = pm.movement[s];
                }
            }
        }
        if(check != 1){ 
            do{
                //Generate random source location
                do{
                    scol = rand() % 8;
                    srow = rand() % 8;
                }while(chessboard[srow][scol].color != AIcolor);

                ptype = chessboard[srow][scol].type; 
                //Check for possible destination for a Pawn
                if(ptype == 'P'){
                    pm = PawnCheck(scol, srow, chessboard[srow][scol].type, AIcolor, lastmove, chessboard);
                }
                //Check for possible destination for a Rook
                else if(ptype == 'R'){
                    pm = RookCheck(scol, srow, AIcolor, chessboard);
                }
                //Check for possible destination for a Knight
                else if(ptype == 'N'){
                    pm = KnightCheck(scol, srow, AIcolor, chessboard);
                }
                //Check for possible destination for a Bishop
                else if(ptype == 'B'){
                    pm = BishopCheck(scol, srow, AIcolor, chessboard);
                }
                //Check for possible destination for a Queen
                else if(ptype == 'Q'){
                    pm = QueenCheck(scol, srow, AIcolor, chessboard);
                }
                //Check for possible destination for a King
                else if(ptype == 'K'){
                    pm = KingCheck(scol, srow, AIcolor, chessboard);
                }
            }while(pm.n == 0);
        
            for(i = 0; i < pm.n; i = i+2)
            {
                if(chessboard[pm.movement[i+1]][pm.movement[i]].color == oppo){
                   eflag = 1;
                   dcol = pm.movement[i];
                   drow = pm.movement[i+1];
                   break;
                }
                else{
                    eflag = 0;
                }
            }
            if(eflag==0){
                s = rand() % pm.n;
                if(s % 2 == 0){
                    dcol = pm.movement[s];
                    drow = pm.movement[s+1];
                }
                else{
                    dcol = pm.movement[s-1];
                    drow = pm.movement[s];
                }
            }
        }
    }
            if(ptype != 'P'){
                p[0] = ptype;
                p[1] = 0;
                fprintf(file, p);
            }
            else{
                p[0] = (char)(scol+97);
                p[1] = 0;
            }
        dest[0] = (char)(dcol+97);
        dest[1] = (char)(56-drow);
        dest[2] = 0;
    //Check if the destination is empty or has something on it
    if(chessboard[drow][dcol].type == ' '){
	chessboard[drow][dcol].type = chessboard[srow][scol].type;
        chessboard[drow][dcol].color = chessboard[srow][scol].color;
        chessboard[srow][scol].type = ' ';
        chessboard[srow][scol].color = ' ';
        fprintf(file, dest);
        fprintf(file, "\n");
    }
    else{
        Capture(chessboard, scol, srow, dcol, drow);
	chessboard[drow][dcol].type = chessboard[srow][scol].type;
        chessboard[drow][dcol].color = chessboard[srow][scol].color;
        chessboard[srow][scol].type = ' ';
        chessboard[srow][scol].color = ' ';
        if(ptype == 'P'){
            fprintf(file, p);
        }
        fprintf(file, "x");
        fprintf(file, dest);
        fprintf(file, "\n");
    }
    step++;
    printf("The AI moves the piece at %c%c to %c%c. \n", (char)(scol+97), (char)(56-srow), (char)(dcol+97), (char)(56-drow));
}
