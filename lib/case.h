#ifndef ECEMAN_CASE_H
#define ECEMAN_CASE_H

#include "game.h"
#include "board.h"
#include "eceman.h"
#include "entity.h"

#define HERO_CHAR '*'
#define SPAWN_CHAR '$'
#define THIN_CHAR 'o'
#define THICK_CHAR 'O'
#define MELT_CHAR 'w'
#define OUTSIDE_CHAR '#'
#define WALL_CHAR 'W'
#define DOOR_CHAR 'D'
#define LIGHTNESS_POTION_CHAR 'L'
#define TUNNEL_CHAR 'T'
#define TUNNEL_EXIT_CHAR 'E'
#define ENEMY_CHAR 'N'
#define MOWER_CHAR 'R'

#define HERO_CHAR_COLOR 176
#define SPAWN_CHAR_COLOR 232
#define THIN_CHAR_COLOR 191
#define THICK_CHAR_COLOR 176
#define MELT_CHAR_COLOR 151
#define OUTSIDE_CHAR_COLOR 128
#define WALL_CHAR_COLOR 63
#define DOOR_CHAR_COLOR 232
#define LIGHTNESS_POTION_CHAR_COLOR 191
#define TUNNEL_CHAR_COLOR 8
#define ENEMY_CHAR_COLOR 178
#define MOWER_CHAR_COLOR 232
#define GRAY_COLOR 8
#define DEFAULT_COLOR 15

/**
 * Enumération des types de case.
 */
enum CaseType {
    MELT,
    THIN,
    THICK,
    WALL,
    OUTSIDE,
    LIGHTNESS_POTION,
    TUNNEL,
    TUNNEL_EXIT,
    DOOR,
    SPAWN
};

/**
 * Enumération des natures de case.
 */
enum CaseNature {
    OPAQUE,
    TRANSPARENT
};

/**
 * Structure de la case.
 */
typedef struct Case {
    unsigned char symbol;
    unsigned char symbolColor;
    enum CaseType type;
    enum CaseNature nature;
} Case;

/*
 * Prototypes
 */

char convertCase(char elem);
int getCaseColor(char elem);
void changeCaseType(GameState* game, char board[ROWS][COLS], Eceman* hero);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]);
Position* getEnemyPosition(char board[ROWS][COLS]);
Position* getToolPosition(char board[ROWS][COLS], const char elem);

#endif // ECEMAN_CASE_H
