#ifndef uttt
#define uttt

//typedef long grid; //2 bits per cell (playerX, cellNotEmpty) * 9, 2 bits grid value, 3 free bits

typedef struct Board {
 	//grid grids[9] {0};
	int cells[81];
	int completedCells;
	int lastMovePlayed;
} Board;

//char positionStringChars[] = {'0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

void drawBoard(Board* board);
int numLegalMoves(Board* board);
void determineLegalMoves(Board* board);

void drawBoard(Board* board) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					printf("%d ", board->cells[i * 27 + j * 3 + k * 9 + l]);
				}
				if (k != 2) printf("|");
			}
			printf("\n");
		}
		if (i != 2) printf("--------------------\n");
	}
	printf("\n");
}

int numLegalMoves(Board* board) {
	if (abs(&board->cells[lastMovePlayed / 10 - 1]) == 2) {
		return 81 - &board->completedCells;
	} else {
		n = 0;
		for (int i = 0; i < 9; i++) {
			if (&board->cells[lastMovePlayed / 10 - 1 + i] == 0) n++;
		}
		return n;
	}
}

void determineLegalMoves(Board* board, int legalMoves[]) {
	int legalMoves[numLegalMoves()];
	int i = 0;

	if (abs(&board->cells[lastMovePlayed / 10 - 1]) == 2) {
		for (int c = 0; c < 81; c++) {
			if (&board->cells[c] == 0) legalMoves[i] = c;
			i++;
		}
	} else {
		for (int c = 0; c < 9; c++) {
			if (&board->cells[lastMovePlayed / 10 - 1 + c] == 0) legalMoves[i] = c;
			i++;
		}
		return n;
	}
}

#endif
