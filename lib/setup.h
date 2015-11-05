#ifndef ECEMAN_SETUP_H
#define ECEMAN_SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "case.h"
#include "eceman.h"
#include "enemy.h"
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

// saving.c
void save(GameState* game);
void saveRanking(const int score);
FILE* loadSaving();
void closeSaving(FILE* saving);

// case.c
char convertCase(char elem);
int getCaseColor(char elem);
void changeCaseType(GameState* game, char board[ROWS][COLS], Eceman* hero);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero);
Position* getEnemyPosition(char board[ROWS][COLS]);
Position* getToolPosition(char board[ROWS][COLS], const char elem);

// eceman.c
Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem);
void gotAttacked(GameState* game, char board[ROWS][COLS], Eceman* hero);
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

// tool.c
Tool* newTool(Position* caseTool, enum ToolType type, enum Direction direction);
void destroyTool(Tool* tool);
void runToolAction(GameState* game, char board[ROWS][COLS], Eceman* hero, enum ToolType toolType);

// board.c
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
void setColor(const int color);
void resetColor();

#endif // ECEMAN_SETUP_H
