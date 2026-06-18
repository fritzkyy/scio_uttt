#include "uttt.h"
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

	memset(board, 0, sizeof(Board));
	strcpy(board->upn,"MMMMMMMMMMMMMMMMMMMMMMMMMMM00X");
	board->xToPlay = true;

	setLegalMoves(board);

	return board;
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

int gridValue(Board* board, int grid) {
	int gridStartIndex = grid * 9;
	int v = NONE;
	int completed = 0;

	for (int i = 0; i < 9; i++) {
		if (board->cells[gridStartIndex + i] != 0) {
			completed++;
		}
	}

	for (int i = 0; i < 8; i++) {
		int a = board->cells[gridStartIndex + winConditions[i][0]];
		if (a != NONE && a == board->cells[gridStartIndex + winConditions[i][1]] && a == board->cells[gridStartIndex + winConditions[i][2]]) {
				v = a;
				break;
		}
	}
	if (!v && completed == 9) v = DRAW;
	//printf("grid %d val %d\n", grid, v);
	return v;
}

int gameState(Board* board) {
	int v = NONE;
	int gridValues[9] = {0};
	int completed = 0;

	for (int i = 0; i < 9; i++) {
		int g = gridValue(board, i);
		if (g != NONE) {
			completed++;
			gridValues[i] = g;
		}
	}

	for (int i = 0; i < 8; i++) {
		int a = gridValues[winConditions[i][0]];
		if (a != NONE && a != DRAW && a == gridValues[winConditions[i][1]] && a == gridValues[winConditions[i][2]]) {
				v = a;
				break;
		}
	}
	if (!v && completed == 9) v = DRAW;

	return v;
}

void sprintUPN(Board* board, char* str) {
	char upn[UPNLENGTH];
	for (int grid = 0; grid < 9; grid++) {
		for (int row = 0; row < 3; row++) {
			int v = (board->cells[grid * 9 + row * 3] + 1) + (board->cells[grid * 9 + row * 3 + 1] + 1) * 3 + (board->cells[grid * 9 + row * 3 + 2] + 1) * 9;
			upn[grid * 3 + row] = rowValueChars[v];
		}
	}
	upn[27] = board->lastMovePlayed ? (char) (board->lastMovePlayed / 10) : '0';
	upn[28] = board->lastMovePlayed ? (char) (board->lastMovePlayed % 10) : '0';
	upn[29] = board->xToPlay ? 'X' : 'O';
	strcpy(str, upn);
}

void drawBoard(Board* board) {
	for (int i = 0; i < 3; i++) {
		printf("---------------------------------------\n");
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int cell = 0; cell < 3; cell++) {
					int x = board->cells[i * 27 + k * 9 + j * 3 + cell];
					char c = x == 1 ? 'X' : x == -1 ? 'O' : ' ';
					printf("| %c ", c);
					if (cell == 2) putchar('|');
				}
			}
			putchar('\n');
		}
	}
	printf("---------------------------------------\n");
}

void setLegalMoves(Board* board) {
	memset(board->legalMoves, 0, sizeof(board->legalMoves));

	if (board->turn == 0 || gridValue(board, board->lastMovePlayed % 10 - 1)) {
		//player free
		int k = 0;
		for (int i = 0; i < 81; i++) {
			if (board->cells[i] == 0) {
				board->legalMoves[k++] = indexToCell(i);
			}
		}
	} else {
		int g = targetGridIndex(board->lastMovePlayed);
		int k = 0;
		for (int i = 0; i < 9; i++) {
			if (board->cells[g + i] == 0) {
				board->legalMoves[k++] = indexToCell(g + i);
			}
		}
	}
}

void printLegalMoves(Board* board) {
	printf("legal moves: ");
	int i = 0;
	while (i < 81 && board->legalMoves[i] != 0) printf("%d ", board->legalMoves[i++]);
	printf("\n");
}

int playMove(Board* board, int move) {
	if (!isMoveLegal(board, move) || board->isGameOver) {
		printf("illegal\n");
		return -2;
	}

	switch (gameState(board)) {
		case OWIN:
			board->isGameOver = true;
			printf("gameover\nowin\nmoves played\n");
			for (int i = 0; i < 81 && board->movesPlayed[i] != 0; i++) {
				printf("%d\n", board->movesPlayed[i]);
			}
			break;
		case XWIN:
			board->isGameOver = true;
			printf("gameover\nxwin\nmoves played\n");
			for (int i = 0; i < 81 && board->movesPlayed[i] != 0; i++) {
				printf("%d\n", board->movesPlayed[i]);
			}
			break;
		case DRAW:
			board->isGameOver = true;
			printf("gameover\ndraw\nmoves played\n");
			for (int i = 0; i < 81 && board->movesPlayed[i] != 0; i++) {
				printf("%d\n", board->movesPlayed[i]);
			}
			break;
	}

	board->cells[cellToIndex(move)] = board->xToPlay ? 1 : -1;
	board->movesPlayed[board->turn] = move;
	board->lastMovePlayed = move;
	board->xToPlay = !board->xToPlay;
	board->turn++;
	setLegalMoves(board);

	return 0;
}

void resetBoard(Board* board) {
	memset(board, 0, sizeof(Board));
	strcpy(board->upn,"MMMMMMMMMMMMMMMMMMMMMMMMMMM00X");
	board->xToPlay = true;

	setLegalMoves(board);
}

int setPosition(Board* board, char* pos) {
	if (strlen(pos) != UPNLENGTH) return -1;

	board->lastMovePlayed = (pos[27] - '0') * 10 + (pos[28] - '0');
	if (pos[29] == 'X') {
		board->xToPlay = true;
	} else if (pos[29] == 'O') {
		board->xToPlay = false;
	} else {
		return 1;
	}

	for (int i = 0; i < 27; i++) {
		int v = 0;
		for (int j = 0; j < 27; j++) {
			if (rowValueChars[j] == pos[i]) v = j;
		}

		board->cells[i * 3] = v % 3 - 1;
		board->cells[i * 3 + 1] = v / 3 % 3 - 1;
		board->cells[i * 3 + 2] = v / 9 - 1;
	}

	setLegalMoves(board);

	return 0;
}
