#include "uttt.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Board* createBoard() {
	Board* board = malloc(sizeof(Board));
	if (board == NULL) return NULL;

	memset(board->cells, 0, sizeof(int) * 81);
	memset(board->movesPlayed, 0, sizeof(int) * 81);
	memset(board->legalMoves, 0, sizeof(int) * 81);
	board->turn = 0;
	board->xToPlay = true;

	return board;
}

void freeBoard(Board* board) {
	if (board) free(board);
}

bool isPlayerFree(Board* board, int lastMovePlayed) {
	if (board->turn == 0) return true;

	int targetGridIndex = cellToIndex(lastMovePlayed % 10 * 10 + 1);
	for (int i = 0; i < 9; i++) {
		if (board->cells[targetGridIndex + i] == 0) return false;
	}
	return true;
}

bool isMoveLegal(Board* board, int move) {
	for (int i = 0; i < 81; i++) {
		if (board->legalMoves[i] == 0) return false;
		if (board->legalMoves[i] == move) return true;
	}
	return false;
}

inline int cellToIndex(int cell) {
	return cell * 9 / 10 - 9;
}

inline int indexToCell(int index) {
	return index / 9 + index + 11;
}

int parseMove(char str[]) {
	int n = 0, len = strlen(str), k = 0;
	for (int i = 0; i < len; i++) {
		if (k == 2) break;
		if (str[i] <= '0' || str[i] > '9') continue;
		n = 10 * n + str[i] - '0';
		k++;
	}
	return n;
}

void drawBoard(Board* board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int cell = 0; cell < 3; cell++) {
					int x = board->cells[i * 27 + k * 9 + j * 3 + cell];
					printf(x == 1 ? "X" : x == -1 ? "O" : " ");
				}
				if (k != 2) printf("|");
			}
			printf("\n");
		}
		if (i != 2) printf("-----------\n");
	}
}

void setLegalMoves(Board* board, int lastMovePlayed) {
	for (int i = 0; i < 81; i++) {
		if (board->legalMoves[i] == 0) break;
		board->legalMoves[i] = 0;
	}

	if (isPlayerFree(board, lastMovePlayed)) {
		for (int i = 0; i < 81; i++) {
			if (board->cells[i] != 0) board->legalMoves[i] = board->cells[i];
		}
	} else {
		int targetGridIndex = cellToIndex(lastMovePlayed % 10 * 10 + 1);
		for (int i = 0; i < 9; i++) {
			if (board->cells[targetGridIndex + i] != 0) board->legalMoves[i] = board->cells[i];
		}
	}
}

void playMove(Board* board, int move) {
	if (!isPlayerFree(board, board->movesPlayed[board->turn]) || isMoveLegal(board, move)) {
		printf("illegal move\n");
		return;
	}
	board->cells[cellToIndex(move)] = board->xToPlay ? 1 : -1;
	setLegalMoves(board, move);
	board->turn++;
	board->xToPlay = !board->xToPlay;
}
