#include "uttt.h"
#include <stdio.h>
#include <string.h>

int main() {
	Board* board = createBoard();

	do {
		printf("turn %d ", board->turn);

		if (isPlayerFree(board, board->movesPlayed[board->turn])) printf("player free\n");
		else {
			printf("legal moves: ");
			for (int i = 0; i < 81; i++) {
				if (board->legalMoves[i] == 0) break;
				printf("%d ", board->legalMoves[i]);
			}
		}

		char input[64];
		fgets(input, 64, stdin);
		int moveToPlay = parseMove(input);
		printf("playing move %d\n", moveToPlay);
		playMove(board, moveToPlay);
		drawBoard(board);
	} while (1);

	return 0;
}
