#ifndef SETUP_H
#define SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "case.h"
#include "eceman.h"
#include "tool.h"
#include "game.h"

#define ROWS 19
#define COLS 15

#define QUIT_CHOICE '4'

#define DELAY 200

#define HERO_CHAR 'P'
#define SPAWN_CHAR '$'
#define WALL_CHAR '_'
#define MELT_CHAR '~'

/*
 * Prototypes
 */

// display.c
void displayTitle();
void displayMenu();
void displaySettings();
void displayRules();
void displayGameOver();

// menu.c
void displayMenu();
char getChoice();
void launchAction(const char choice);

// case.c
char changeCaseType(char board[ROWS][COLS], Position* pos);
void runCaseAction(char board[ROWS][COLS], Position* pos);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);

// board.c
void initBoard(char board[ROWS][COLS]);
void clearEceman(char board[ROWS][COLS], Eceman* hero);
void drawEceman(char board[ROWS][COLS], Eceman* hero);
void drawBoard(char board[ROWS][COLS], Eceman* hero);
Eceman* moveEceman(char board[ROWS][COLS], const char key, Eceman* hero);

// game.c
void startGame();
void loadNextLevel();
void gameOver();

// functions.c
void goBack();
void stopGame();
void goToXY(Position* pos);

#endif
