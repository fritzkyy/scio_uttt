#include "uttt.h"
#include "scio.h"
#include <stdio.h>
#include <string.h>
#define DEBUG
#ifdef DEBUG
	#include <time.h>
#endif

#define INF 2147483646
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

const int gridWeight = 9;
const int gridPosBonus = 4;
const int posBonus[] = {
	3, 2, 3, 2, 4, 2, 3, 2, 3
};

void printBotInfo() {
	printf("Scio bot by Fritzky\n");
	printf("Version %d, 16/06/2026\n", VERSION);
	printf("https://github.com/fritzkyy/scio_uttt\n\n");
}

float positionValue(Board* board) {
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

	float g = 0, c = 0;
    for (int grid = 0; grid < 9; grid++) {
		int v = gridValue(board, grid);
		g += v * posBonus[grid];

		if (v != 0) continue;
		for (int cell = 0; cell < 9; cell++) {
			c += board->cells[cell * 9 + cell] * posBonus[cell] * posBonus[grid] / gridPosBonus;
		}
	}
	return g * gridWeight + c;
}

int bestMove(Board* board, int depth) {
    float bestValue = board->xToPlay ? -INF : INF;

	#ifdef DEBUG
		clock_t start, end;
		double time;
		start = clock();
	#endif

	int lmoves[81];
	memcpy(lmoves, board->legalMoves, sizeof(lmoves));
    int moveToPlay = lmoves[0];

    for (int i = 0; i < 81 && lmoves[i]; i++) {
        testMove(board, lmoves[i], true);
        float moveValue = minimax(board, depth - 1, -INF, INF);
        testMove(board, lmoves[i], false);

        if ((board->xToPlay && moveValue > bestValue) || (!board->xToPlay && moveValue < bestValue)) {
            bestValue = moveValue;
            moveToPlay = lmoves[i];
        }
    }

	#ifdef DEBUG
		end = clock();
		time = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("time %f s\n", time);
	#endif

    return moveToPlay;
}

float minimax(Board* board, int depth, int alpha, int beta) {
    if (depth == 0 || gameState(board)) return positionValue(board);

    int lmoves[81];
    memcpy(lmoves, board->legalMoves, sizeof(lmoves));
	float bestValue = board->xToPlay ? -INF : INF;

    if (board->xToPlay) {
        for (int i = 0; i < 81 && lmoves[i]; i++) {
            testMove(board, lmoves[i], true);
            float value = minimax(board, depth - 1, alpha, beta);
            testMove(board, lmoves[i], false);

            bestValue = max(bestValue, value);
            alpha = max(alpha, bestValue);

            if (beta <= alpha) break;
        }
        return bestValue;
    }
    else {
        for (int i = 0; i < 81 && lmoves[i]; i++) {
            testMove(board, lmoves[i], true);
            float value = minimax(board, depth - 1, alpha, beta);
            testMove(board, lmoves[i], false);

            bestValue = min(bestValue, value);
            beta = min(beta, bestValue);

            if (beta <= alpha) break;
        }
        return bestValue;
    }
}

float bestValue(Board* board, int depth) {
    float bestValue = board->xToPlay ? -INF : INF;

	#ifdef DEBUG
		clock_t start, end;
		double time;
		start = clock();
	#endif

	int lmoves[81];
	memcpy(lmoves, board->legalMoves, sizeof(lmoves));

    for (int i = 0; i < 81 && lmoves[i]; i++) {
        testMove(board, lmoves[i], true);
        float moveValue = minimax(board, depth - 1, -INF, INF);
        testMove(board, lmoves[i], false);

        if ((board->xToPlay && moveValue > bestValue) || (!board->xToPlay && moveValue < bestValue)) {
            bestValue = moveValue;
        }
    }

	#ifdef DEBUG
		end = clock();
		time = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("time %f s\n", time);
	#endif

    return bestValue;
}

void testMove(Board* board, int move, bool make) {
	board->cells[cellToIndex(move)] = make ? (board->xToPlay ? 1 : -1) : 0;
	board->lastMovePlayed = make ? move : board->movesPlayed[board->turn - 1];
	board->xToPlay = !board->xToPlay;
	setLegalMoves(board);
}
