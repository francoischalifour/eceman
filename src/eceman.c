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
    pos->y = 2;

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
 * @return 0 si l'endroit du spawn a été trouvé, -1 sinon
 */
int goToSpawn(char board[ROWS][COLS], Eceman* hero) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[y][x] == SPAWN_CHAR) {
                hero->pos->x = x;
                hero->pos->y = y;

                return 0;
            }
        }
    }

    return -1;
}

/**
 * Déplace le Eceman sur le plateau de jeu.
 * @param key La touche appuyée
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman à déplacer
 * @return Le Eceman avec sa nouvelle position
 */
Eceman* moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero) {
    unsigned short prevPosX = hero->pos->x;
    unsigned short prevPosY = hero->pos->y;

    goToXY(0, 19);
    printf("                                         \n");
    goToXY(0, 19);

    switch (key) {
        case UP_KEY:
            if (board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR) {
                printf("> Collision\n");
                return NULL;
            }

            hero->pos->y -= 1;
            break;

        case DOWN_KEY:
            if (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR) {
                printf("> Collision\n");
                return NULL;
            }

            hero->pos->y += 1;
            break;

        case LEFT_KEY:
            if (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR) {
                printf("> Collision\n");
                return NULL;
            }

            hero->pos->x -= 1;
            break;

        case RIGHT_KEY:
            if (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR) {
                printf("> Collision\n");
                return NULL;
            }

            hero->pos->x += 1;
            break;
    }

    if (prevPosX != hero->pos->x || prevPosY != hero->pos->y) {
        game->levelScore++;
        runCaseAction(game, board, hero);
        drawToolbar(game);
    }

    // TODO : à supprimer
    goToXY(0, 18);
    printf("(%d, %d) \n", hero->pos->x, hero->pos->y);

    if (isCircle(board, hero) == 1) {
        system("cls");
        gameOver(game);
        goBack();
        backToMenu(game);
    }

    return hero;
}

/**
 * Dessine le Eceman sur le plateau de jeu.
 * @param board Le plateau sur lequel le Eceman est ajouté
 * @param hero Le Eceman à ajouter
 */
void drawEceman(char board[ROWS][COLS], Eceman* hero) {
    board[hero->pos->x][hero->pos->y] = HERO_CHAR;
    goToXY(hero->pos->x, hero->pos->y);
    putchar(HERO_CHAR);
}

/**
 * Vérifie si le Eceman est entouré de murs ou d'eau.
 * Dans ce cas, on recommence le niveau.
 * @param board Le plateau sur lequel le joueur joue
 * @param hero Le Eceman à tester
 * @return 1 si le Eceman est encerclé, 0 sinon
 */
int isCircle(char board[ROWS][COLS], Eceman* hero) {
    if ((board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR)
        && (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR)
        && (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR)
        && (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR)) {
        return 1;
    }

    return 0;
}
