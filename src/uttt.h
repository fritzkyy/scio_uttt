#pragma once
#include <stdbool.h>

#define UPNLENGTH 28

typedef struct {
	int cells[81];
	int movesPlayed[81];
	int legalMoves[9];
	int lastMovePlayed;
	int turn;
	char upn[UPNLENGTH];
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

char rowValue(Board* board, int grid, int row);
char* positionString(Board* board);

void drawBoard(Board* board);
void setLegalMoves(Board* board);
void playMove(Board* board, int move);
