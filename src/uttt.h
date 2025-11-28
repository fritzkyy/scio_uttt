#ifndef uttt
#define uttt

#include <stdlib.h>
#include <stdbool.h>

typedef struct Board {
	int cells[81]; //0 empty, 1 full, 2 grid won, + for x and - for o
	int movesPlayed[81];
	int legalMoves[9];
	int lastMovePlayed;
	bool XToPlay;
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

//char positionStringChars[27] = {'0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

bool isPlayerFree(Board* board);
bool isMoveLegal(Board* board, int move);
//bool isCellFree(Board* board, int index);

inline int cellToIndex(int cell);
inline int gridToIndex(int grid);
inline int indexToCell(int index);
int gridValue(Board* board, int grid);
int gameResult(Board* board);
inline int abs(int n);

void drawBoard(Board* board);
void determineLegalMoves(Board* board, int lastMovePlayed);
void inputMove(Board* board);
void makeMove(Board* board, int move, int value, bool isTesting);
//void testMove(Board* board, int move, bool isX, bool make);
void updateGrid(Board* board, int grid);

bool isPlayerFree(Board* board) {
	printf("isplayerfree: grid value %d\n", gridValue(board, board->lastMovePlayed % 10));
	return gridValue(board, board->lastMovePlayed % 10) != 0 || turn == 0;
}

bool isMoveLegal(Board* board, int move) {
	if (turn == 0) return true;
	for (int i = 0; i < 81; i++) {
		if (board->legalMoves[i] == 0) return false;
		if (board->legalMoves[i] == move) return true;
	}
	return false;
}

/*bool isCellFree(Board* board, int cell) {
	return board->cells[cellToIndex(cell)] == 0;
}*/

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

int gridValue(Board* board, int grid) {
	if (abs(board->cells[cellToIndex(grid * 10 + 1)]) != 1) return board->cells[cellToIndex(grid * 10 + 1)] > 0 ? 1 : -1;
	for (int i = 0; i < 8; i++) {
		//if (board->cells[grid * 9 - 9 + winConditions[i][0]] == 0) continue;printf("grid %d value %d\n", grid, board->cells[grid * 9 - 9 + winConditions[i][0]]);
		if (board->cells[cellToIndex(grid * 10 + winConditions[i][0] + 1)] == board->cells[cellToIndex(grid * 10 + winConditions[i][1] + 1)] && board->cells[cellToIndex(grid * 10 + winConditions[i][1] + 1)] == board->cells[cellToIndex(grid * 10 + winConditions[i][2] + 1)]) return board->cells[cellToIndex(grid * 10 + winConditions[i][0] + 1)];
	}
}

int gameResult(Board* board) {
	for (int i = 0; i < 8; i++) {
		/*if (board->cells[gridToIndex(i + 1 + winConditions[i][0])] == 0) continue;
		printf("grid %d value %d", i + 1, board->cells[gridToIndex(i + 1 + winConditions[i][0])]);
		if (board->cells[gridToIndex(i + 1 + winConditions[i][0])] == board->cells[gridToIndex(i + 1 + winConditions[i][1])] && board->cells[gridToIndex(i + 1 + winConditions[i][1])] == board->cells[gridToIndex(i + 1 + winConditions[i][2])]) return board->cells[gridToIndex(i + 1 + winConditions[i][0])] / 2;*/
		if (gridValue(board, i + winConditions[i][0] + 1) == 0) continue;
		if (gridValue(board, i + winConditions[i][0] + 1) == gridValue(board, i + winConditions[i][1] + 1) && gridValue(board, i + winConditions[i][0] + 1) == gridValue(board, i + winConditions[i][2] + 1)) return gridValue(board, i + winConditions[i][0] + 1) / 2;
	}
	return 0;
}

int abs(int n) {
	return n > 0 ? n : -n;
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

void determineLegalMoves(Board* board, int lastMovePlayed) {
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
	char input[3];
	do {
		fgets(input, 3, stdin);
		board->lastMovePlayed = atoi(input);
	} while (board->lastMovePlayed > 99 || board->lastMovePlayed < 11);
}

void makeMove(Board* board, int move, int value, bool isTesting) {
	//if (!isMoveLegal(board, move)) return;
	board->cells[cellToIndex(move)] = value;
	determineLegalMoves(board, board->lastMovePlayed);
	if (isTesting) return;
	board->movesPlayed[turn] = board->lastMovePlayed;
	turn++;
	board->XToPlay = !board->XToPlay;
}

/*void testMove(Board* board, int move, bool isX, bool make) {
	board->cells[cellToIndex(move)] = make ? (isX ? 1 : -1) : 0;
	determineLegalMoves(board, move);
}*/

void updateGrid(Board* board, int grid) {
	int k = gridValue(board, grid);
	for (int i = 0; i < 9; i++) board->cells[gridToIndex(grid) + i] = 2 * k;
}

#endif
