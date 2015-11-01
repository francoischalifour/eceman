#include "../lib/setup.h"
#include "../lib/game.h"
#include "../lib/enemy.h"
#include <windows.h>
#include <conio.h>
#include <assert.h>

/**
 * Créé une nouvelle liste d'ennemis.
 * @return Une nouvelle liste d'ennemis
 */
EnemyList* newEnemyList() {
    EnemyList* enemyList = malloc(sizeof(EnemyList));

    assert(enemyList != NULL);

    enemyList->first = NULL;
    enemyList->last = NULL;
    enemyList->nbEnemies = 0;

    return enemyList;
}

/**
 * Détruit la liste d'ennemi passée en paramètre.
 * Libère la mémoire de la liste d'ennemis.
 * @param enemyList La liste d'ennemis à détruire
 */
void destroyEnemyList(EnemyList* enemyList) {
    ENEMY_FOREACH(enemyList, first, next, curr) {
        if (curr->prev) {
            free(curr->prev);
            free(curr->pos);
        }
    }

    free(enemyList);
}

/**
 * Créé un nouvel ennemi.
 * @return L'ennemi initialisé
 */
Enemy* newEnemy(Position* caseEnemy, enum Direction direction) {
    Position* pos = malloc(sizeof(Position));
    Enemy* enemy = malloc(sizeof(Enemy));

    assert(pos != NULL);
    assert(enemy != NULL);

    pos->x = caseEnemy->x;
    pos->y = caseEnemy->y;

    enemy->prev = NULL;
    enemy->next = NULL;
    enemy->pos = pos;
    enemy->direction = direction;
    enemy->caseBelow = THIN_CHAR;

    return enemy;
}

/**
 * Détruit l'ennemi passé en paramètre.
 * Libère la mémoire de l'ennemi.
 * @param enemy L'ennemi à détruire
 */
void destroyEnemy(Enemy* enemy) {
    free(enemy->pos);
    free(enemy);
}

/**
 * Ajoute un ennemi à la liste des ennemis.
 * @param enemyList La liste d'ennemis
 * @param enemy L'ennemi à ajouter
 * @return L'ennemi ajouté
 */
Enemy* addEnemy(EnemyList* enemyList, Enemy* enemy) {
    // Si c'est le premier ennemi de la liste.
    if (enemyList->nbEnemies) {
        enemy->prev = enemyList->last;
        enemy->next = NULL;
        enemy->pos = (enemy->prev)->pos;

        enemyList->last->next = enemy;
        enemyList->last = enemy;
    } else {
        enemyList->first = enemy;
        enemyList->last = enemy;
    }

    enemyList->nbEnemies++;

    return enemy;
}

/**
 * Déplace l'ennemi sur le plateau de jeu.
 * @param game L'état du jeu
 * @param board La plateau de jeu
 * @param enemy L'ennemi à déplacer
 * @param hero Le Eceman à vérifier pour la collision
 * @return L'ennemi avec sa nouvelle position
 */
Enemy* moveEnemy(GameState* game, char board[ROWS][COLS], Enemy* enemy, Eceman* hero) {
    switch (enemy->direction) {
        case UP:
            if (board[enemy->pos->x-1][enemy->pos->y] != THIN_CHAR && board[enemy->pos->x-1][enemy->pos->y] != HERO_CHAR) {
                enemy->direction = DOWN;
                return NULL;
            }

            enemy->pos->x -= 1;
            break;

        case DOWN:
            if (board[enemy->pos->x+1][enemy->pos->y] != THIN_CHAR && board[enemy->pos->x+1][enemy->pos->y] != HERO_CHAR) {
                enemy->direction = UP;
                return NULL;
            }

            enemy->pos->x += 1;
            break;

        case LEFT:
            if (board[enemy->pos->x][enemy->pos->y-1] != THIN_CHAR && board[enemy->pos->x][enemy->pos->y-1] != HERO_CHAR) {
                enemy->direction = RIGHT;
                return NULL;
            }

            enemy->pos->y -= 1;
            break;

        case RIGHT:
            if (board[enemy->pos->x][enemy->pos->y+1] != THIN_CHAR && board[enemy->pos->x][enemy->pos->y+1] != HERO_CHAR) {
                enemy->direction = LEFT;
                return NULL;
            }

            enemy->pos->y += 1;
            break;
    }

    enemy->caseBelow = board[enemy->pos->x][enemy->pos->y];

    // Si l'ennemi percute le héros.
    if (enemy->caseBelow == HERO_CHAR) {
        gotAttacked(game, board, hero);
    }

    return enemy;
}

/**
 * Dessine l'ennemi passé en paramètre sur le plateau de jeu.
 * @param board Le plateau sur lequel l'ennemi est ajouté
 * @param enemy L'ennemi à ajouter
 */
void drawEnemy(char board[ROWS][COLS], Enemy* enemy) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    board[enemy->pos->x][enemy->pos->y] = ENEMY_CHAR;
    goToXY(enemy->pos->y, enemy->pos->x);

    SetConsoleTextAttribute(hConsole, ENEMY_CHAR_COLOR);
    putchar(convertCase(ENEMY_CHAR));
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

/**
 * Nettoie la case de l'ancienne position de l'ennemi.
 * @param board Le plateau de jeu
 * @param enemy L'ennemi à nettoyer
 */
void clearEnemy(char board[ROWS][COLS], Enemy* enemy) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    board[enemy->pos->x][enemy->pos->y] = enemy->caseBelow;
    goToXY(enemy->pos->y, enemy->pos->x);

    SetConsoleTextAttribute(hConsole, THIN_CHAR_COLOR);
    putchar(convertCase(enemy->caseBelow));
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}
