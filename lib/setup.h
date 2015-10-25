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

#define DELAY 50

#define HERO_CHAR '*'
#define SPAWN_CHAR '$'
#define WALL_CHAR 'W'
#define DOOR_CHAR 'D'
#define THIN_CHAR 'o'
#define THICK_CHAR 'O'
#define MELT_CHAR '~'
#define UNDEFINED_CHAR '#'

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

// file.c
FILE* loadMap(const short level);
void closeMap(FILE* map);

// case.c
char convertCase(char elem);
void changeCaseType(char board[ROWS][COLS], Position* pos);
void runCaseAction(char board[ROWS][COLS], Position* pos);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToSpawn(char board[ROWS][COLS], Eceman* hero);
void drawEceman(char board[ROWS][COLS], Eceman* hero);
Eceman* moveEceman(const char key, char board[ROWS][COLS], Eceman* hero);

// board.c
void drawBoard(FILE* map, char board[ROWS][COLS]);

// game.c
void startGame();
void loadNextLevel();
void gameOver();

// functions.c
void goBack();
void stopGame();
void goToXY(Position* pos);

#endif
