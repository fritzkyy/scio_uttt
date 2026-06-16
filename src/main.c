#define DEBUG
#include "uttt.h"
#include "scio.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	Board* board = createBoard();

	while (1) {
		char input[64];

		if (fgets(input, sizeof(input), stdin) == NULL) {
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		char* arg0 = strtok(input, " ");

		if (!strcmp(input, "q")) {
			break;
		}
		else if (!strcmp(arg0, "pos")) {
			char str[64];
			if (fgets(str, sizeof(str), stdin) == NULL) {
				break;
			}
			str[strcspn(str, "\n")] = '\0';
			switch (setPosition(board, str)) {
				case -1:
					printf("invalid string length\n");
					break;
				case 0:
					printf("position set\n");
					break;
				case 1:
					printf("invalid syntax\n");
					break;
			}
		}
		else if (!strcmp(input, "d")) {
			drawBoard(board);
		}
		else if (!strcmp(input, "i") || !strcmp(input, "info")) {
			printBotInfo();
		}
		else if (!strcmp(arg0, "e") || !strcmp(arg0, "eval")) {
			int len = strlen(arg0);
			char c1 = input[len + 1], c2 = input[len + 2];
			if (!isdigit(c1) && !isdigit(c2)) continue;

			int depth = (c1 - '0') * 10 + (c2 - '0');
			printf("eval %.2f\n", bestValue(board, depth));
		}
		else if (!strcmp(arg0, "bm") || !strcmp(arg0, "bestmove")) {
			int len = strlen(arg0);
			char c1 = input[len + 1], c2 = input[len + 2];
			if (!isdigit(c1) && !isdigit(c2)) continue;

			int depth = (c1 - '0') * 10 + (c2 - '0');
			printf("bestmove %d\n", bestMove(board, depth));
		}
		else if (!strcmp(arg0, "p") || !strcmp(arg0, "play")) {
			int len = strlen(arg0);
			char c1 = input[len + 1], c2 = input[len + 2];
			if (!isdigit(c1) && !isdigit(c2)) continue;

			int move = (c1 - '0') * 10 + (c2 - '0');
			playMove(board, move);
		}
		else if (!strcmp(arg0, "pb") || !strcmp(arg0, "playbest")) {
			int len = strlen(arg0);
			char c1 = input[len + 1], c2 = input[len + 2];
			if (!isdigit(c1) && !isdigit(c2)) continue;

			int depth = (c1 - '0') * 10 + (c2 - '0');
			int move = bestMove(board, depth);
			playMove(board, move);
			printf("played %d\n", move);
			#ifdef DEBUG
				drawBoard(board);
				printf("eval %d\n", bestValue(board, depth));
			#endif
		}
		else if (!strcmp(input, "upn")) {
			sprintUPN(board, board->upn);
			printf("%s\n", board->upn);
		}
		else if (!strcmp(input, "lm")) {
			printLegalMoves(board);
		}
		else if (!strcmp(input, "r") || !strcmp(input, "reset")) {
			resetBoard(board);
		}
		else if (!strcmp(input, "t") || !strcmp(input, "turn")) {
			printf("%d\n", board->turn);
		}
		else {
			printf("invalid command\n");
		}
	}

	free(board);

	return 0;
}
