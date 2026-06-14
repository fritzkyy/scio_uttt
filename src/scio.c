#include "uttt.h"
#include "scio.h"
#include <stdio.h>
#include <string.h>

#define INF 2147483646
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

const int gridWeight = 5;
const int posBonus[] = {
	3, 2, 3, 2, 4, 2, 3, 2, 3
};

void printBotInfo() {
	printf("Scio bot by Fritzky\n");
	printf("Version %d, 14/06/2026\n", VERSION);
	printf("https://github.com/fritzkyy/scio_uttt\n\n");
}

int positionValue(Board* board) {
	switch (gameState(board)) {
		case NONE:
			break;
		case OWIN:
			return -INF;
		case XWIN:
			return INF;
		case DRAW:
			return 0;
	}

	int g = 0, c = 0;
    for (int i = 0; i < 9; i++) {
		int v = gridValue(board, i);
		g += v * posBonus[i];

		if (v != 0) continue;
		for (int j = 0; j < 9; j++) {
			c += board->cells[i * 9 + j] * posBonus[j];
		}
	}
	return g * gridWeight + c;
}

int bestMove(Board* board, int depth) {
    int bestValue = board->xToPlay ? -INF : INF;

	int lmoves[81];
	memcpy(lmoves, board->legalMoves, sizeof(lmoves));
    int moveToPlay = lmoves[0];

    for (int i = 0; i < 81 && lmoves[i]; i++) {
        testMove(board, lmoves[i], true);
        int moveValue = minimax(board, depth - 1);
        testMove(board, lmoves[i], false);

        if ((board->xToPlay && moveValue > bestValue) || (!board->xToPlay && moveValue < bestValue)) {
            bestValue = moveValue;
            moveToPlay = lmoves[i];
        }
    }

    return moveToPlay;
}

int minimax(Board* board, int depth) {
    if (depth == 0 || gameState(board)) return positionValue(board);

	int lmoves[81];
	memcpy(lmoves, board->legalMoves, sizeof(lmoves));
	int bestValue = board->xToPlay ? -INF : INF;

    for (int i = 0; i < 81 && lmoves[i]; i++) {
        testMove(board, lmoves[i], true);
        bestValue = board->xToPlay ? min(bestValue, minimax(board, depth - 1)) : max(bestValue, minimax(board, depth - 1));
        testMove(board, lmoves[i], false);
    }

    return bestValue;
}

int bestValue(Board* board, int depth) {
    int bestValue = board->xToPlay ? -INF : INF;

	int lmoves[81];
	memcpy(lmoves, board->legalMoves, sizeof(lmoves));

    for (int i = 0; i < 81 && lmoves[i]; i++) {
        testMove(board, lmoves[i], true);
        int moveValue = minimax(board, depth - 1);
        testMove(board, lmoves[i], false);

        if ((board->xToPlay && moveValue > bestValue) || (!board->xToPlay && moveValue < bestValue)) {
            bestValue = moveValue;
        }
    }

    return bestValue;
}

void testMove(Board* board, int move, bool make) {
	if (make) {
		board->cells[cellToIndex(move)] = board->xToPlay ? 1 : -1;
		board->lastMovePlayed = move;
		board->xToPlay = !board->xToPlay;
		setLegalMoves(board);
	} else {
		board->cells[cellToIndex(move)] = 0;
		board->lastMovePlayed = board->movesPlayed[board->turn];
		board->xToPlay = !board->xToPlay;
		setLegalMoves(board);
	}
}
