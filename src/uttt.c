#include "uttt.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int winConditions[8][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 8},
	{2, 4, 6}
};

const char rowValueChars[27] = {'0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

Board* createBoard() {
	Board* board = malloc(sizeof(Board));
	if (board == NULL) return NULL;

	memset(board->cells, 0, sizeof(int) * 81);
	memset(board->movesPlayed, 0, sizeof(int) * 81);
	memset(board->legalMoves, 0, sizeof(int) * 9);
	strcpy(board->upn,"0000000000000000000000000000X");
	board->lastMovePlayed = 0;
	board->turn = 0;
	board->xToPlay = true;
	board->isPlayerFree = true;

	return board;
}

void freeBoard(Board* board) {
	if (board) free(board);
}

bool isPlayerFree(Board* board) {
	if (board->turn == 0) return true;
	int g = targetGridIndex(board->lastMovePlayed);
	for (int i = 0; i < 9; i++) {
		if (board->cells[g + i] == 0) return false;
	}
	return true;
}

bool isMoveLegal(Board* board, int move) {
	if (board->isPlayerFree && board->cells[cellToIndex(move)] == 0) return true;
	for (int i = 0; i < 9; i++) {
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

inline int targetGridIndex(int lastMovePlayed) {
	return cellToIndex(lastMovePlayed % 10 * 10 + 1);
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

int evaluateGrid(Board* board, int gridStartIndex) {
	for (int i = 0; i < 8; i++) {
		if (board->cells[gridStartIndex + winConditions[i][0]] == 0) continue;
		if (board->cells[gridStartIndex + winConditions[i][0]] == board->cells[gridStartIndex + winConditions[i][1]] &&
			board->cells[gridStartIndex + winConditions[i][1]] == board->cells[gridStartIndex + winConditions[i][2]]) {
				return board->cells[gridStartIndex + winConditions[i][0]];
		}
	}
	return 0;
}

int evaluateBoard(Board* board) {
	return 0;
}

char rowValue(Board* board, int grid, int row) {
	int v = 0;
	for (int i = 0; i < 3; i++) {
		v += board->cells[grid * 9 + row * 3 + i] * pow(i, 3) + 1;
	}
	return rowValueChars[v];
}

char* positionString(Board* board) {
	char* str = malloc(UPNLENGTH + 1);
	for (int grid = 0; grid < 9; grid++) {
		for (int row = 0; row < 3; row++) {
			str[grid * 3 + row] = rowValue(board, grid, row);
		}
	}
	str[27] = board->lastMovePlayed % 10 - 1;
	str[28] = board->xToPlay ? 'X' : 'O';
	return str;
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

void setLegalMoves(Board* board) {
	if (board->isPlayerFree) return;

	int i = 0;
	while (board->legalMoves[i] != 0 && i < 9) board->legalMoves[i++] = 0;

	int g = targetGridIndex(board->lastMovePlayed);
	int k = 0;
	for (i = 0; i < 9; i++) {
		if (board->cells[g + i] == 0) {
			board->legalMoves[k++] = indexToCell(g + i);
		}
	}
}

void playMove(Board* board, int move) {
	if (!isMoveLegal(board, move)) {
		printf("illegal move\n");
		return;
	}

	board->cells[cellToIndex(move)] = board->xToPlay ? 1 : -1;
	board->movesPlayed[board->turn] = move;
	board->lastMovePlayed = move;
	board->turn++;
	board->xToPlay = !board->xToPlay;
	board->isPlayerFree = isPlayerFree(board);
	setLegalMoves(board);
}
