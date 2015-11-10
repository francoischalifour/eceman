#ifndef ECEMAN_SETUP_H
#define ECEMAN_SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "functions.h"
#include "level.h"
#include "map.h"
#include "menu.h"
#include "saving.h"
#include "score.h"
#include "case.h"
#include "board.h"
#include "game.h"
#include "entity.h"
#include "eceman.h"
#include "display.h"

/*
 * Prototypes
 */

Eceman* newEceman();
void destroyEceman(Eceman* hero);
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem);
void gotAttacked(GameState* game, char board[ROWS][COLS], Eceman* hero);
void moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]);
void drawEceman(char board[ROWS][COLS], Eceman* hero);

#endif // ECEMAN_SETUP_H
