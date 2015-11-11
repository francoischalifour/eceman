#ifndef ECEMAN_BOARD_H
#define ECEMAN_BOARD_H

#include "game.h"
#include "entity.h"

void extractEntities(char board[ROWS][COLS], Entity* entityList[ENTITY_MAX]);
int hasEnnemies(char board[ROWS][COLS]);
int hasMowers(char board[ROWS][COLS]);
void drawToolbar(const GameState* game);
void drawBoard(FILE* map, const GameState* game, char board[ROWS][COLS]);

#endif // ECEMAN_BOARD_H
