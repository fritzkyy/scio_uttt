#pragma once
#include <stdbool.h>

typedef struct {
	int cells[81];
	int movesPlayed[81];
	int legalMoves[81];
	int turn;
	bool xToPlay;
} Board;

Board* createBoard();
void freeBoard(Board* board);

bool isPlayerFree(Board* board, int lastMovePlayed);
bool isMoveLegal(Board* board, int move);

int cellToIndex(int cell);
int indexToCell(int index);
int parseMove(char str[]);

void drawBoard(Board* board);
void setLegalMoves(Board* board, int lastMovePlayed);
void playMove(Board* board, int move);
