#pragma once
#include "uttt.h"

#define VERSION 1

void printBotInfo();

int positionValue(Board* board);
int bestMove(Board* board, int depth);
int minimax(Board* board, int depth);
int bestValue(Board* board, int depth);

void testMove(Board* board, int move, bool make);
