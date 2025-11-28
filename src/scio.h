#ifndef scio
#define scio

#include "uttt.h"

/*typedef struct Engine {
        Board board;
        float eval;
} Engine;*/

//Board engineBoard = {{0}, {0}, {0}, 0, true};

int boardEval(Board* board);
int bestMove(Board* board, int depth, bool isXPlayer);
int minimax(Board* board, int depth, bool isXPlayer);
int max(int a, int b);
int min(int a, int b);

int boardEval(Board* board) {
    int cellEval = 0, gridEval = 0;

    for (int i = 0; i < 9; i++) {
		int g = gridValue(board, i + 1);
		if (g == 0) {
			for (int j = 0; j < 9; j++) {
				int c = board->cells[i * 9 + j];
				if (j == 4) c *= 4;
				else if (i % 2 == 0) c *= 3;
				else c *= 2;
				cellEval += c;
			}
		}

        if (i == 4) g *= 4;
		else if (i % 2 == 0) g *= 3;
		else g *= 2;
		gridEval += g;
    }

    return cellEval + gridEval * 5;
}

int bestMove(Board* board, int depth, bool isXPlayer) {
	int bestEval = isXPlayer ? -10000 : 10000;
	int moveToPlay = board->legalMoves[1];

    for (int i = 0; i < 81; i++) {
		int move = board->legalMoves[i];
		if (move == 0) return 0;
		makeMove(board, move, board->XToPlay ? 1 : -1, true);
		int moveEval = minimax(board, depth, turn % 2 == 0);
		makeMove(board, move, 0, true);

		if ((isXPlayer && moveEval > bestEval) || (!isXPlayer && moveEval < bestEval)) {
			bestEval = moveEval;
			moveToPlay = board->legalMoves[i];
		}
	}
	printf("returning %d\n", moveToPlay);
	return moveToPlay;
}

int minimax(Board* board, int depth, bool isXPlayer) {
	printf("legal moves ");
	for (int i = 0; i < 81; i++) {
		if (board->legalMoves[i] == 0) continue;
		printf("%d ", board->legalMoves[i]);
	}printf("\n");
	if (depth == 0 || gameResult(board) != 0) return boardEval(board) * isXPlayer ? 1 : -1;
	if (isXPlayer) {
		int maxEval = -10000;
		for (int i = 0; i < 81; i++) {
			int move = board->legalMoves[i];
			makeMove(board, move, board->XToPlay ? 1 : -1, true);
			printf("making move %d at depth %d\n", move, depth);break;
			int moveEval = minimax(board, depth - 1, false);
			maxEval = max(maxEval, moveEval);
			makeMove(board, move, 0, true);
			printf("unmaking move %d at depth %d\n", move, depth);
		}
		printf("returning eval %d\n", maxEval);
		return maxEval;
	} else {
		int minEval = 10000;
		for (int i = 0; i < 81; i++) {
			int move = board->legalMoves[i];
			makeMove(board, move, board->XToPlay ? 1 : -1, true);
			printf("making move %d at depth %d\n", move, depth);break;
			int moveEval = minimax(board, depth - 1, true);
			minEval = min(minEval, moveEval);
			makeMove(board, move, 0, true);
			printf("unmaking move %d at depth %d\n", move, depth);
		}
		printf("returning eval %d\n", minEval);
		return minEval;
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

#endif
