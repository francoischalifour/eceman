#include <assert.h>
#include "../lib/setup.h"
#include "../lib/eceman.h"

/**
 * Créé un nouveau Eceman.
 * Initialise son état et sa position.
 * @return Le Eceman initialisé
 */
Eceman* newEceman() {
    Position* pos = malloc(sizeof(Position));
    Eceman* hero = malloc(sizeof(Eceman));

    pos->x = 0;
    pos->y = 0;

    hero->state = NORMAL;
    hero->pos = pos;

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
 * @return 1 si l'endroit du spawn a été trouvé, 0 sinon
 */
int goToSpawn(char board[ROWS][COLS], Eceman* hero) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == SPAWN_CHAR) {
                hero->pos->x = x;
                hero->pos->y = y;

                return 1;
            }
        }
    }

    return 0;
}

/**
 * Déplace le Eceman sur le plateau de jeu.
 * @param key La touche appuyée
 * @param board Le plateau de jeu
 * @param hero Le Eceman à déplacer
 * @return Le Eceman avec sa nouvelle position
 */
Eceman* moveEceman(const char key, char board[ROWS][COLS], Eceman* hero) {
    switch (key) {
        case UP_KEY:
            /*if (board[hero->pos->x][hero->pos->y - 1] == WALL_CHAR)
                return NULL;*/

            hero->pos->y -= 1;
            break;

        case DOWN_KEY:
/*            if (board[hero->pos->x][hero->pos->y + 1] == WALL_CHAR)
                return NULL;*/

            hero->pos->y += 1;
            break;

        case LEFT_KEY:
/*            if (board[hero->pos->x - 1][hero->pos->y] == WALL_CHAR)
                return NULL;*/

            hero->pos->x -= 1;
            break;

        case RIGHT_KEY:
/*            if (board[hero->pos->x + 1][hero->pos->y] == WALL_CHAR)
                return NULL;*/

            hero->pos->x += 1;
            break;
    }

    //runCaseAction(board, hero->pos);

    return hero;
}

/**
 * Dessine le Eceman sur le plateau de jeu.
 * @param board Le plateau sur lequel le Eceman est ajouté
 * @param hero Le Eceman à ajouter
 */
void drawEceman(char board[ROWS][COLS], Eceman* hero) {
    board[hero->pos->x][hero->pos->y] = HERO_CHAR;
    goToXY(hero->pos);
    putchar(HERO_CHAR);
}
