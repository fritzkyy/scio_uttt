#include <stdio.h>
#include "uttt.h"
//fix lastMovePlayed
int main() {
    Board gameBoard = {{0}, {0}, {0}, 0};

	turn = 0;

	while (1) {
		printf("turn %d\n", turn);
		{
			int i = 0;
			printf("moves played: ");
			while (gameBoard.movesPlayed[i] != 0) {
				printf("%d ", gameBoard.movesPlayed[i]);
				i++;
			}
		}
		printf("\n");
		if (isPlayerFree(&gameBoard)) printf("player free\n");
		else {
			printf("player not free\n");
			printf("legal moves: ");
			for (int i = 0; i < 9; i++) {
				printf("%d ", gameBoard.legalMoves[i]);
			}
		}
		printf("\n");
		inputMove(&gameBoard);
		printf("last move played is %d\n", gameBoard.lastMovePlayed);
		if (!isMoveLegal(&gameBoard, gameBoard.lastMovePlayed, gameBoard.legalMoves)) {
			printf("illegal\n");
			gameBoard.lastMovePlayed = gameBoard.movesPlayed[turn - 1];
			printf("last move played is %d\n", gameBoard.movesPlayed[turn - 1]);
			continue;
		}
		makeMove(&gameBoard, gameBoard.lastMovePlayed);
		drawBoard(&gameBoard);
	}

    return 0;
}
