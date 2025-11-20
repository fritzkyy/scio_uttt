#include <stdio.h>
#include "uttt.h"
//fix lastMovePlayed
int main() {
    Board gameBoard = {{0}, {0}, {0}, 0}, analysisBoard = {{0}, {0}, {0}, 0};

	turn = 0;

	while (1) {
		if (isPlayerFree(&gameBoard)) printf("player free\n");
		else {
			printf("player not free\n");
			for (int i = 0; i < 9; i++) {
				printf("%d ", gameBoard.legalMoves[i]);
			}
		}
		printf("\n");
		inputMove(&gameBoard);
		if (!isMoveLegal(&gameBoard, gameBoard.lastMovePlayed, gameBoard.legalMoves)) {
			printf("illegal\n");
			continue;
		}
		makeMove(&gameBoard, gameBoard.lastMovePlayed);
		drawBoard(&gameBoard);
	}

    return 0;
}
