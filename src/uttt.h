#ifndef uttt
#define uttt

#include <stdlib.h>
#include <stdbool.h>

typedef struct Board {
	int cells[81]; //0 empty, 1 full, 2 grid won, + for x and - for o
	int completedCells;
	int lastMovePlayed;
	int legalMoves[9];
} Board;

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

int turn;

//char positionStringChars[] = {'0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

void drawBoard(Board* board);
bool isPlayerFree(Board* board);
void determineLegalMoves(Board* board);
void inputMove(Board* board);
void makeMove(Board* board, int move);
//inline int moveToIndex(int move);
bool isMoveLegal(Board* board, int move, int legalMoves[]);
int gridValue(Board* board, int grid);

void drawBoard(Board* board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					if (board->cells[i * 27 + j * 3 + k * 9 + l] == 1) printf("X");
					else if (board->cells[i * 27 + j * 3 + k * 9 + l] == -1) printf("O");
					else printf(".");
				}
				if (k != 2) printf("|");
			}
			printf("\n");
		}
		if (i != 2) printf("-----------\n");
	}
	printf("\n");
}

bool isPlayerFree(Board* board) {
	return abs(board->cells[board->lastMovePlayed / 10 - 1]) == 2 || turn == 0;
}

void determineLegalMoves(Board* board) {
	if (isPlayerFree(board)) return;
	int i = 0;

	for (int c = 0; c < 9; c++) {
		if (board->cells[board->lastMovePlayed / 10 - 1 + c] == 0) board->legalMoves[i] = c;
		i++;
	}
}

void inputMove(Board* board) {
	char input[3];
	do {
		fgets(input, 3, stdin);
	} while (atoi(input) > 99 || atoi(input) < 11);

	board->lastMovePlayed = atoi(input);
}

void makeMove(Board* board, int move) {
	if (!isMoveLegal(board, move, board->legalMoves)) return;
	board->cells[move / 10 * 9 + move % 10 - 10] = turn % 2 == 0 ? 1 : -1;
	turn++;
}

/*inline int moveToIndex(int move) {
	return move / 10 * 9 + move % 10 - 10;
}*/

bool isMoveLegal(Board* board, int move, int legalMoves[]) {
	if (turn == 0 || isPlayerFree(board) && board->cells[move / 10 * 9 + move % 10 - 10] == 0) return true;
	int k = 0;
	for (int i = 0; i < 9; i++) {
		if (legalMoves[i] == 0) break;
		if (legalMoves[i] == move) {
			k = 1;
			break;
		}
	}
	return k == 1;
}

int gridValue(Board* board, int grid) {
	for (int i = 0; i < 8; i++) {
		if (board->cells[grid * 9 - 9 + winConditions[i][0]] == 0) continue;
		if (board->cells[grid * 9 - 9 + winConditions[i][0]] == board->cells[grid * 9 - 9 + winConditions[i][1]] && board->cells[grid * 9 - 9 + winConditions[i][1]] == board->cells[grid * 9 - 9 + winConditions[i][2]]) return board->cells[grid * 9 - 9 + winConditions[i][0]];
	}
}

#endif
