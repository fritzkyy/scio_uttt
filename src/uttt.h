#pragma once
#include <stdbool.h>

typedef struct {
	int cells[81];
	int movesPlayed[81];
	int legalMoves[9];
	int lastMovePlayed;
	int turn;
	bool xToPlay;
	bool isPlayerFree;
} Board;

Board* createBoard();
void freeBoard(Board* board);

bool isPlayerFree(Board* board);
bool isMoveLegal(Board* board, int move);

int cellToIndex(int cell);
int indexToCell(int index);
int targetGridIndex(int lastMovePlayed);
int parseMove(char str[]);
int evaluateGrid(Board* board, int gridStartIndex);
int evaluateBoard(Board* board);

void drawBoard(Board* board);
void setLegalMoves(Board* board);
void playMove(Board* board, int move);
