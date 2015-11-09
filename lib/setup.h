#ifndef ECEMAN_SETUP_H
#define ECEMAN_SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "case.h"
#include "eceman.h"
#include "entity.h"
#include "game.h"

/*
 * Prototypes
 */

// display.c
void displayTitle();
void displayMenu();
void displayLevels();
void displaySettings();
void displayRules();
void displayGameOver(const int scoreFinal);
void displayRanking();
void displayAbout();

// menu.c
void displayMenu();
char getChoice();
void launchAction(const char choice);

// map.c
FILE* loadMap(short level);
void closeMap(FILE* map);

// score.c
int getLastScore(FILE* scoreFile);
int getMinHighScore();
int getScoreLine(FILE* scoreFile, const int score);
int getNbScores();
int deleteScore(const int score);
float getLastTime(FILE* saving);

// level.c
int getLastLevel(FILE* saving);
int getNbLevels();
void getRanking();
void launchLevel(char level);

// saving.c
void save(GameState* game);
void saveRanking(const int score);
FILE* loadSaving();
void closeSaving(FILE* saving);

// case.c
char convertCase(char elem);
int getCaseColor(char elem);
void changeCaseType(GameState* game, char board[ROWS][COLS], Eceman* hero);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]);
Position* getEnemyPosition(char board[ROWS][COLS]);
Position* getToolPosition(char board[ROWS][COLS], const char elem);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem);
void gotAttacked(GameState* game, char board[ROWS][COLS], Eceman* hero);
void moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]);
void drawEceman(char board[ROWS][COLS], Eceman* hero);

// board.c
void extractEntities(char board[ROWS][COLS], Entity* entityList[ENTITY_MAX]);
int hasEnnemies(char board[ROWS][COLS]);
int hasMowers(char board[ROWS][COLS]);
void drawToolbar(GameState* game);
void drawBoard(FILE* map, GameState* game, char board[ROWS][COLS]);

// game.c
void initGame(const int isNew);
void loadNextLevel();
void reloadLevel(GameState* game, char board[ROWS][COLS], Eceman* hero);
void pauseGame(GameState* game);
void gameOver(GameState* game);

// functions.c
void goBack();
void goToXY(const unsigned short x, const unsigned short y);
int convertToInt(const char c);
void setColor(const int color);
void resetColor();

#endif // ECEMAN_SETUP_H
