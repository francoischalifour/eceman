#ifndef SETUP_H
#define SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "case.h"
#include "eceman.h"
#include "tool.h"
#include "game.h"

#define ROWS 15
#define COLS 19

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

// map.c
FILE* loadMap(const short level);
void closeMap(FILE* map);

// saving.c
FILE* loadSaving();
void closeSaving(FILE* saving);
int getLevel();
int getScore();

// case.c
char convertCase(char elem);
void changeCaseType(char board[ROWS][COLS], Position* pos);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToSpawn(char board[ROWS][COLS], Eceman* hero);
void drawEceman(char board[ROWS][COLS], Eceman* hero);
Eceman* moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero);

// board.c
void drawToolbar(GameState* game);
void drawBoard(FILE* map, GameState* game, char board[ROWS][COLS]);

// game.c
void initGame();
void loadNextLevel();
void gameOver();

// functions.c
void goBack();
void stopGame();
void goToXY(const unsigned short x, const unsigned short y);

#endif
