#include <stdio.h>
#include "uttt.h"

int main() {
    Board gameBoard = {{0}, 0, 0, {0}}, analysisBoard = {{0}, 0, 0, {0}};

	turn = 0;

	while (1) {
		do {
			inputMove(&gameBoard);
		} while (!isMoveLegal(&gameBoard, gameBoard.lastMovePlayed, gameBoard.legalMoves));

		makeMove(&gameBoard, gameBoard.lastMovePlayed);
		printf("%d is %d\n", gameBoard.lastMovePlayed, turn % 2 == 0 ? 1 : -1);
		drawBoard(&gameBoard);
	}

    return 0;
}
