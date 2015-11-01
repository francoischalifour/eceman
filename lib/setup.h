#ifndef ECEMAN_SETUP_H
#define ECEMAN_SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "case.h"
#include "eceman.h"
#include "enemy.h"
#include "game.h"

/*
 * Prototypes
 */

// display.c
void displayTitle();
void displayMenu();
void displaySettings();
void displayRules();
void displayGameOver(const int score);
void displayRanking();
void displayAbout();

// menu.c
void displayMenu();
char getChoice();
void launchAction(const char choice);

// map.c
FILE* loadMap(const short level);
void closeMap(FILE* map);

// score.c
int getLastScore(FILE* scoreFile);
int getMinHighScore(FILE* scoreFile);
int getNbScores(FILE* scoreFile);
int deleteScore(FILE* scoreFile, const int score);

// level.c
int getLastLevel();
int getNbLevels();
void getRanking();

// saving.c
void save(int level, int score);
void saveRanking(const int score);
void clearSaving();
FILE* loadSaving();
void closeSaving(FILE* saving);

// case.c
char convertCase(char elem);
int getCaseColor(char elem);
void changeCaseType(GameState* game, char board[ROWS][COLS], Eceman* hero);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero);
Position* getEnemyCase(char board[ROWS][COLS]);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem);
Eceman* moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero);
void drawEceman(char board[ROWS][COLS], Eceman* hero);

// enemy.c
EnemyList* newEnemyList();
void destroyEnemyList(EnemyList* enemyList);
Enemy* newEnemy(Position* caseEnemy, enum Direction direction);
void destroyEnemy(Enemy* enemy);
Enemy* addEnemy(EnemyList* enemyList, Enemy* enemy);
Enemy* moveEnemy(GameState* game, char board[ROWS][COLS], Enemy* enemy, Eceman* hero);
void clearEnemy(char board[ROWS][COLS], Enemy* enemy);
void drawEnemy(char board[ROWS][COLS], Enemy* enemy);

// board.c
int hasEnnemies(char board[ROWS][COLS]);
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
