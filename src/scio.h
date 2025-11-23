#ifndef scio
#define scio

#include "uttt.h"

/*typedef struct Engine {
        Board board;
        float eval;
} Engine;

Engine scio = {{{0}, {0}, {0}, 0}, 0};*/

int boardEval(Board* board) {
        int cellEval = 0, gridEval = 0;

        for (int i = 0; i < 9; i++) {
		int g = gridValue(board, i);
		printf("grid %d value %d\n", i, g);
		if (g == 0) {
			for (int j = 0; j < 9; j++) {
				int c = board->cells[i * 9 + j];
				printf("cell %d value %d\n", indexToCell(i * 9 + j), c);
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

int bestMove(Board* board) {
        return board->legalMoves[0];
}

#endif
