#include <stdio.h>
#include <stdlib.h>
#include "uttt.h"

int main() {
    Board gameBoard = {{0}, 0}, analysisBoard = {{0}, 0};

	gameBoard.cells[0] = 1;
	gameBoard.cells[9] = 1;
	gameBoard.cells[27] = 1;
	drawBoard(&gameBoard);

    return 0;
}
