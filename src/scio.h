#pragma once
#include "uttt.h"

#define VERSION 1

void printBotInfo();

float positionValue(Board* board);
int bestMove(Board* board, int depth);
float minimax(Board* board, int depth, int alpha, int beta);
float bestValue(Board* board, int depth);

void testMove(Board* board, int move, bool make);
