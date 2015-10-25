#include <assert.h>
#include "../lib/setup.h"
#include "../lib/eceman.h"

/**
 * Créé un nouveau Eceman.
 * Initialise son état et sa position.
 * @return Le Eceman initialisé
 */
Eceman* newEceman() {
    Eceman* hero = malloc(sizeof(hero));
    Position* pos = malloc(sizeof(pos));

    assert(hero != NULL);
    assert(pos != NULL);

    hero->state = NORMAL;
    hero->pos->x = 0;
    hero->pos->y = 0;

    return hero;
}

/**
 * Détruit le Eceman passé en paramètre.
 * Libère la mémoire du Eceman.
 * @param hero Le Eceman à détruire
 */
void destroyEceman(Eceman* hero) {
    free(hero->pos);
    free(hero);
}

/**
 * Place le héro à l'endroit de spawn de la map.
 * @param board Le plateau du niveau
 * @param hero Le Eceman à placer
 */
void goToSpawn(char board[ROWS][COLS], Eceman* hero) {
    unsigned short i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == SPAWN_CHAR) {
                hero->pos->x = i;
                hero->pos->y = j;

                return;
            }
        }
    }
}

/**
 * Déplace le Eceman sur le plateau de jeu.
 * @param hero Le Eceman à déplacer
 * @return La nouvelle position du Eceman
 */
Eceman* moveEceman(char board[ROWS][COLS], const char key, Eceman* hero) {
    assert(hero != NULL);

    switch (key) {
        case UP_KEY:
            if (board[hero->pos->x][hero->pos->y -1] == WALL_CHAR)
                return NULL;

            changeCaseType(board, hero->pos);

            hero->pos->y -= 1;
            break;

        case DOWN_KEY:
            if (board[hero->pos->x][hero->pos->y +1] == WALL_CHAR)
                return NULL;

            changeCaseType(board, hero->pos);

            hero->pos->y += 1;
            break;

        case LEFT_KEY:
            if (board[hero->pos->x][hero->pos->x+1] == WALL_CHAR)
                return NULL;

            changeCaseType(board, hero->pos);

            hero->pos->x += 1;
            break;

        case RIGHT_KEY:
            if (board[hero->pos->x][hero->pos->x-1] == WALL_CHAR)
                return NULL;

            changeCaseType(board, hero->pos);

            hero->pos->x -= 1;
            break;
    }

    runCaseAction(board, hero->pos);

    return hero;
}
