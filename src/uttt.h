#pragma once
#include <stdbool.h>
#include <stddef.h>

#define UPNLENGTH 30

/*typedef struct {
	size_t nmoves;
	int moves[81];
} MoveArr;*/

typedef enum {
	OWIN = -1,
	NONE,
	XWIN,
	DRAW
} GameState;

typedef struct {
	int cells[81];
	/*MoveArr movesPlayed;
	MoveArr legalMoves;*/
	int movesPlayed[81];
	int legalMoves[81];
	int lastMovePlayed;
	int turn;
	char upn[UPNLENGTH];
	bool xToPlay;
} Board;

Board* createBoard();

bool isMoveLegal(Board* board, int move);

int cellToIndex(int cell);
int indexToCell(int index);
int targetGridIndex(int lastMovePlayed);
int parseMove(char str[]);
int gridValue(Board* board, int gridStartIndex);
int gameState(Board* board);

void sprintUPN(Board* board, char* str);
void drawBoard(Board* board);
void setLegalMoves(Board* board);
void printLegalMoves(Board* board);
void playMove(Board* board, int move);
void resetBoard(Board* board);
int setPosition(Board* board, char* pos);
