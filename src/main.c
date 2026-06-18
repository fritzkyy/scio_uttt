#define DEBUG
#include "uttt.h"
#include "scio.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int depth;
	bool log, isBotGame;
} Settings;

int main() {
	Board* board = createBoard();
	Settings settings = {1, false, false};

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
			switch (setPosition(board, input + 4)) {
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
		else if (!strcmp(input, "rs")) {
			settings = (Settings) {1, false, false};
		}
		else if (!strcmp(arg0, "depth")) {
			int len = strlen(arg0);
			char c1 = input[len + 1], c2 = input[len + 2];
			if (!isdigit(c1) && !isdigit(c2)) continue;

			int depth = (c1 - '0') * 10 + (c2 - '0');
			settings.depth = depth;
		}
		else if (!strcmp(arg0, "log")) {
			int len = strlen(arg0);

			switch (input[len + 1]) {
				case '0':
					settings.log = false;
					break;
				default:
					settings.log = true;
					FILE* logfile = fopen("../logs/log.txt", "w");
			}
		}
		else if (!strcmp(input, "i") || !strcmp(input, "info")) {
			printBotInfo();
		}
		else if (!strcmp(arg0, "e") || !strcmp(arg0, "eval")) {
			int len = strlen(arg0), depth;

			if (strlen(input) == len) {
				depth = settings.depth;
			} else {
				char c1 = input[len + 1], c2 = input[len + 2];
				if (!isdigit(c1) && !isdigit(c2)) continue;

				depth = (c1 - '0') * 10 + (c2 - '0');
			}
			printf("eval %.2f\n", bestValue(board, depth));
		}
		else if (!strcmp(arg0, "bm") || !strcmp(arg0, "bestmove")) {
			if (board->isGameOver) {
				printf("game already over\n");
				continue;
			}

			int len = strlen(arg0), depth;

			if (strlen(input) == len) {
				depth = settings.depth;
			} else {
				char c1 = input[len + 1], c2 = input[len + 2];
				if (!isdigit(c1) && !isdigit(c2)) continue;

				depth = (c1 - '0') * 10 + (c2 - '0');
			}
			printf("bestmove %d\n", bestMove(board, depth));
		}
		else if (!strcmp(arg0, "p") || !strcmp(arg0, "play")) {
			if (board->isGameOver) {
				printf("game already over\n");
				continue;
			}

			int len = strlen(arg0);
			char c1 = input[len + 1], c2 = input[len + 2];
			if (!isdigit(c1) && !isdigit(c2)) continue;

			int move = (c1 - '0') * 10 + (c2 - '0');
			if (!playMove(board, move) && (settings.isBotGame)) {
				int move = bestMove(board, settings.depth);
				playMove(board, move);
				printf("played %d\n", move);
			}
			#ifdef DEBUG
				drawBoard(board);
				printf("eval %.2f\n", bestValue(board, settings.depth));
				sprintUPN(board, board->upn);
				printf("%s\n", board->upn);
			#endif
		}
		else if (!strcmp(arg0, "pb") || !strcmp(arg0, "playbest")) {
			if (board->isGameOver) {
				printf("game already over\n");
				continue;
			}

			int len = strlen(arg0), depth;

			if (strlen(input) == len) {
				depth = settings.depth;
			} else {
				char c1 = input[len + 1], c2 = input[len + 2];
				if (!isdigit(c1) && !isdigit(c2)) continue;

				depth = (c1 - '0') * 10 + (c2 - '0');
			}

			int move = bestMove(board, depth);
			playMove(board, move);
			printf("played %d\n", move);
			#ifdef DEBUG
				drawBoard(board);
				printf("eval %.2f\n", bestValue(board, depth));
				sprintUPN(board, board->upn);
				printf("%s\n", board->upn);
			#endif
		}
		else if (!strcmp(arg0, "nbg") || !strcmp(arg0, "newbotgame")) {
			int len = strlen(arg0);
			bool isBotX = input[len + 1] == 'X' || input[len + 1] == 'x';
			settings.isBotGame = true;

			if (isBotX) {
				int move = bestMove(board, settings.depth);
				playMove(board, move);
				printf("played %d\n", move);
				#ifdef DEBUG
					drawBoard(board);
					printf("eval %.2f\n", bestValue(board, settings.depth));
				#endif
			}
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
			printf("%d %c to play\n", board->turn + 1, board->xToPlay ? 'X' : 'O');
		}
		else {
			printf("invalid command\n");
		}
	}

	free(board);

	return 0;
}
