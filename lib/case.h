#ifndef ECEMAN_CASE_H
#define ECEMAN_CASE_H

#include "game.h"
#include "board.h"
#include "eceman.h"
#include "entity.h"

#define HERO_CHAR '*'
#define SPAWN_CHAR '$'
#define SLIP_CHAR 'i'
#define THIN_CHAR 'o'
#define THICK_CHAR 'O'
#define MELT_CHAR 'w'
#define OUTSIDE_CHAR '#'
#define WALL_CHAR 'W'
#define DOOR_CHAR 'D'
#define LIGHTNESS_POTION_CHAR 'L'
#define SCORE_BONUS_CHAR 'S'
#define TUNNEL_CHAR 'T'
#define TUNNEL_EXIT_CHAR 'E'
#define HOLE_CHAR 'Z'
#define MOWER_CHAR 'R'
#define ENEMY_CHAR 'N'

#define HERO_CHAR_COLOR 176
#define SPAWN_CHAR_COLOR 232
#define THIN_CHAR_COLOR 191
#define THICK_CHAR_COLOR 176
#define SLIP_CHAR_COLOR 191
#define MELT_CHAR_COLOR 151
#define OUTSIDE_CHAR_COLOR 128
#define WALL_CHAR_COLOR 63
#define DOOR_CHAR_COLOR 232
#define LIGHTNESS_POTION_CHAR_COLOR 191
#define SCORE_BONUS_CHAR_COLOR 175
#define TUNNEL_CHAR_COLOR 8
#define HOLE_CHAR_COLOR 1
#define MOWER_CHAR_COLOR 232
#define ENEMY_CHAR_COLOR 178
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
int getCaseColor(const char elem);
void changeCaseType(GameState* game, char board[ROWS][COLS], const Eceman* hero);
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]);
Position* getEnemyPosition(char board[ROWS][COLS]);
Position* getToolPosition(char board[ROWS][COLS], const char elem);

#endif // ECEMAN_CASE_H
