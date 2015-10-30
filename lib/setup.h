#ifndef ECEMAN_SETUP_H
#define ECEMAN_SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "case.h"
#include "eceman.h"
#include "tool.h"
#include "game.h"

/*
 * Prototypes
 */

// display.c
void displayTitle();
void displayMenu();
void displaySettings();
void displayRules();
void displayGameOver();
void displayRanking();
void displayAbout();

// menu.c
void displayMenu();
char getChoice();
void launchAction(const char choice);

// map.c
FILE* loadMap(const short level);
void closeMap(FILE* map);

// saving.c
void save(int level, int score);
void saveRanking(const int score);
void clearSaving();
FILE* loadSaving();
void closeSaving(FILE* saving);
int getNbLevels();
int getLevel();
int getScore();

// case.c
char convertCase(char elem);
int getCaseColor(char elem);
void changeCaseType(GameState* game, char board[ROWS][COLS], Eceman* hero);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem);
void drawEceman(char board[ROWS][COLS], Eceman* hero);
Eceman* moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero);

// board.c
void drawToolbar(GameState* game);
void drawBoard(FILE* map, GameState* game, char board[ROWS][COLS]);

// game.c
void initGame(const int isNew);
void loadNextLevel();
void reloadLevel(GameState* game, char board[ROWS][COLS], Eceman* hero);
void pauseGame(GameState* game);
void gameOver(GameState* game);
void backToMenu(GameState* game);

// functions.c
void goBack();
void goToXY(const unsigned short x, const unsigned short y);

#endif // ECEMAN_SETUP_H
