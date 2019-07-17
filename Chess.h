#ifndef CHESS_H
#define CHESS_H

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

void printMenu(char mode);
void decodeInput();
void displayBoard();
void updateBoard(char color);
int Chessmain(char mode);

#endif
