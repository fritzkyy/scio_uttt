#include <stdio.h>
#include "uttt.h"
//#include "scio.h"

Board* createBoard() {
    Board* board = (Board*)malloc(sizeof(Board));
    if (board == NULL) return NULL;

    for (int i = 0; i < 81; i++) {
        board->cells[i] = 0;
    }
    for (int i = 0; i < 9; i++) {
        board->gridValues[i] = 0;
    }

    board->lastMovePlayed = 0;
    board->XToPlay = true;

    determineLegalMoves(board);
    return board;
}

void freeBoard(Board* board) {
	if (board) {
        free(board);
    }
}

bool isPlayerFree(Board* board) {
	if (turn == 0) return true;
    return board->gridValues[board->lastMovePlayed % 10 - 1] != 0;
}

bool isMoveLegal(Board* board, int move) {
	if (turn == 0) return true;
	for (int i = 0; i < 81; i++) {
		if (board->legalMoves[i] == 0) return false;
		if (board->legalMoves[i] == move) return true;
	}
	return false;
}

bool isGridDraw(Board* board, int grid) {
	if (board->gridValues[grid - 1] != 0) return false;

    int gridIndex = gridToIndex(grid);
    for (int i = 0; i < 9; i++) {
        if (board->cells[gridIndex + i] == 0) return false;
    }
    return true;
}

int cellToIndex(int cell) {
	return cell / 10 * 9 + cell % 10 - 10;
}

//return first cell of grid
int gridToIndex(int grid) {
	return (grid - 1) * 9;
}

int indexToCell(int index) {
	return (index / 9 + 1) * 10 + index % 9 + 1;
}

int gameResult(Board* board) {
	for (int i = 0; i < 8; i++) {
        int a = board->gridValues[winConditions[i][0]];
        int b = board->gridValues[winConditions[i][1]];
        int c = board->gridValues[winConditions[i][2]];

        if (a == b && b == c && a != 0 && a != 2) return a;
	}

    int activeGrids = 0;
    for (int i = 0; i < 9; i++) {
        if (board->gridValues[i] == 0) activeGrids++;
    }

    if (activeGrids == 0) return 2;

	return 0;
}

void drawBoard(Board* board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					if (board->cells[i * 27 + j * 3 + k * 9 + l] == 1) printf("X");
					else if (board->cells[i * 27 + j * 3 + k * 9 + l] == -1) printf("O");
					else printf(".");
					//printf("%d", board->cells[i * 27 + j * 3 + k * 9 + l]);
				}
				if (k != 2) printf("|");
			}
			printf("\n");
		}
		if (i != 2) printf("-----------\n");
	}
	printf("\n");
}

void determineLegalMoves(Board* board) {
	int k = 0;
	for (int i = 0; i < 81; i++) board->legalMoves[i] = 0;

	if (isPlayerFree(board)) {
		for (int i = 0; i < 81; i++) {
			if (board->cells[i] != 0) continue;
			board->legalMoves[k] = indexToCell(i);
			k++;
		}
	} else for (int i = board->lastMovePlayed % 10 * 10 + 1; i < board->lastMovePlayed % 10 * 10 + 10; i++) {
		if (board->cells[cellToIndex(board->lastMovePlayed % 10 * 10 + 1) + i] == 0) {
			//printf("adding %d to legal moves\n", board->lastMovePlayed % 10 * 10 + i + 1);
			board->legalMoves[k] = board->lastMovePlayed % 10 * 10 + i + 1;
			k++;
		}
	}
}

void inputMove(Board* board) {
	int move = 0;
    char inputBuffer[100];

	do {
        printf("Legal Moves: ");
        for (int i = 0; i < 81 && board->legalMoves[i] != 0; i++) {
            printf("%d ", board->legalMoves[i]);
        }
        printf("\n");

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) continue;
        if (sscanf(inputBuffer, "%d", &move) != 1 || move < 11 || move > 99 || move % 10 == 0 || !isMoveLegal(board, move)) {
            move = 0;
            continue;
        }
	} while (move == 0);

    board->lastMovePlayed = move;
}

void makeMove(Board* board, int move) {
	if (!isMoveLegal(board, move)) {
        printf("illegal\n");
        return;
    }

    board->cells[cellToIndex(move)] = board->XToPlay ? 1 : -1;
    board->lastMovePlayed = move;
	updateGrid(board, move / 10);
    determineLegalMoves(board);
	board->XToPlay = !board->XToPlay;
    turn++;
}

void updateGrid(Board* board, int grid) {
	if (board->gridValues[grid - 1] != 0) return;
	if (isGridDraw(board, grid)) board->gridValues[grid - 1] = 2;

	int gridIndex = gridToIndex(grid);

	for (int i = 0; i < 8; i++) {
        int a = board->cells[gridIndex + winConditions[i][0]];
        int b = board->cells[gridIndex + winConditions[i][1]];
        int c = board->cells[gridIndex + winConditions[i][2]];

        if (a == b && b == c && a != 0) {
            board->gridValues[grid - 1] = a;
            return;
        }
    }
}

int main() {
    Board* gameBoard = createBoard();
	if (gameBoard == NULL) {
        printf("Failed to allocate memory for board\n");
        return 1;
    }

	turn = 0;
	int result = 0;

	while ((result = gameResult(gameBoard)) == 0) {
        drawBoard(gameBoard);

        if (gameBoard->legalMoves[0] == 0) {
             result = 2;
             break;
        }

        inputMove(gameBoard);
        makeMove(gameBoard, gameBoard->lastMovePlayed);
    }

	/*while (1) {
		/*printf("best move %d\n", bestMove(&gameBoard, 10, turn % 2 == 0));
		printf("eval %d\n", boardEval(&gameBoard));*/
		/*printf("turn %d\n", turn);
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
			printf("legal moves: ");
			for (int i = 0; i < 9; i++) {
				printf("%d ", gameBoard.legalMoves[i]);
			}
		}
		printf("\n");

		inputMove(&gameBoard);
		//printf("last move played is %d\n", gameBoard.lastMovePlayed);
		if (!isMoveLegal(&gameBoard, gameBoard.lastMovePlayed)) {
			printf("illegal\n");
			gameBoard.lastMovePlayed = gameBoard.movesPlayed[turn - 1];
		} else {
			makeMove(&gameBoard, gameBoard.lastMovePlayed);
			drawBoard(&gameBoard);
		}
	}*/

	freeBoard(gameBoard);
    return 0;
}
