#ifndef uttt
#define uttt

#include <stdlib.h>
#include <stdbool.h>

typedef struct Board {
	int cells[81]; //0 empty, 1 full, + for x and - for o
	int gridValues[9];
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

Board* createBoard();
void freeBoard();

bool isPlayerFree(Board* board);
bool isMoveLegal(Board* board, int move);
bool isGridDraw(Board* board, int grid);

inline int cellToIndex(int cell);
inline int gridToIndex(int grid);
inline int indexToCell(int index);
int gameResult(Board* board);

void drawBoard(Board* board);
void determineLegalMoves(Board* board);
void inputMove(Board* board);
void makeMove(Board* board, int move);
//void testMove(Board* board, int move, bool isX, bool make);
void updateGrid(Board* board, int grid);

#endif
