# Scio

Scio is an _Ultimate Tic-Tac-Toe_ engine coded in C.  
To install, run the `Makefile` or the command `gcc src/main.c src/uttt.c src/scio.c -o uttt`.

The program consists of a command-line interface that accepts one of the following commands:
* `pos`
  * Accepts a [UPN string](#UPN) (after a newline) and sets the board position to the input. Starting position is set by default.  
* `d`
  * Prints a representation of the current board state to the console.  
* `i` or `info`
  * Prints information about the bot.  
* `e` or `eval`
  * Returns the evaluation of the position after given depth (depth must be inputed with 2 digits).  
* * `bm` or `bestmove`
  * Returns the best move after given depth (depth must be inputed with 2 digits).
  * Returns the best move after given depth (depth must be inputed with 2 digits).    
* `p` or `play`
  * Plays the indicated move.  
* `pb` or `playbest`
  * Finds and plays the best move after given depth (depth must be inputed with 2 digits).  
  Merely combines the commands `bm depth` and `p move`.  
* `upn`
  * Returns the [UPN](#UPN) notation of the current position.  
* `lm`
  * Prints the list of legal moves.  
* `r` or `reset`
  * Resets the board to its initial state.  
* `t` or `turn`
  * Returns the current turn (0 - 80) and the player currently in turn (X or O).  
* `q`
  * Exits the program.

#### UPN
A _UPN string_ (UTTT Position Notation) represents a position with a 30-character string.  
Each of the first 27 characters represents a row of the board: 1 is added to the value of each cell and the result is multiplied by 3 raised to the power of _i_, where _i_ is the index from 0 to 2 of the cell in the row.
The following 2 characters indicate the last move played, and the last one indicates the current turn (X or O).  
See the function `sprintUPN` in `src/uttt.c`.
