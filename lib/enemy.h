#ifndef ECEMAN_ENEMY_H
#define ECEMAN_ENEMY_H

#include "position.h"

#define ENEMY_FOREACH(enemyList, nbEnemies, next, curr) Enemy* enemy = NULL;\
    Enemy* curr = NULL;\
    for(curr = enemy = enemyList->nbEnemies; enemy != NULL; curr = enemy = enemy->next)

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * Structure d'un ennemi.
 */
typedef struct Enemy Enemy;
struct Enemy {
    Enemy* prev;
    Enemy* next;
    Position* pos;
    enum Direction direction;
    unsigned char caseBelow;
};

/**
 * Structure d'une liste d'ennemis.
 */
typedef struct EnemyList {
    Enemy* first;
    Enemy* last;
    unsigned short nbEnemies;
} EnemyList;

#endif // ECEMAN_ENEMY_H
