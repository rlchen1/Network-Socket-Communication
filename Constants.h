#ifndef CONSTANTS_H
#define CONSTANTS_H
struct PIECE{
    int pts;      //points that help AI determine which move is more valuable
    char type;    //type of pieces (P, N, R, B, Q, K)
    char color;   //color of pieces (w, b)
    char col;     //column location of pieces
    char row;     //row location of pieces
};

struct MV{
        int* movement;
        int n;
};

#define  a  0;
#define  b  1;
#define  c  2;
#define  d  3;
#define  e  4;
#define  f  5;
#define  g  6;
#define  h  7;

#endif

