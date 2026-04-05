#include "uttt.h"
#include <stdio.h>
#include <string.h>

int main() {
	Board* board = createBoard();

	do {
		printf("turn %d ", board->turn);

		if (board->isPlayerFree) printf("player free ");
		else {
			printf("legal moves: ");
			int i = 0;
			while (board->legalMoves[i] != 0 && i < 9) printf("%d ", board->legalMoves[i++]);
		}

		char input[64];
		fgets(input, 64, stdin);
		int moveToPlay = parseMove(input);
		printf("playing move %d\n", moveToPlay);
		playMove(board, moveToPlay);
		drawBoard(board);
		strcpy(board->upn, positionString(board));
		printf("%s\n", board->upn);
	} while (1);

	return 0;
}
