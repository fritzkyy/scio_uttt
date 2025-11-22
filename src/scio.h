#ifndef scio
#define scio

#include "uttt.h"

Board analysisBoard = {{0}, {0}, {0}, 0};

int bestMove(Board* board) {
	return board->legalMoves[0];
}

#endif
