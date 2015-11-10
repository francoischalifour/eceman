#include "../lib/setup.h"
#include "../lib/eceman.h"
#include <windows.h>
#include <conio.h>

/**
 * Créé un nouveau Eceman.
 * Initialise son état et sa position.
 * @return Le héros initialisé
 */
Eceman* newEceman() {
    Position* pos = malloc(sizeof(Position));
    Eceman* hero = malloc(sizeof(Eceman));

    pos->x = 0;
    pos->y = 0;

    hero->pos = pos;
    hero->state = NORMAL;
    hero->caseBelow = SPAWN_CHAR;

    return hero;
}

/**
 * Détruit le héros passé en paramètre.
 * Libère la mémoire du héros.
 * @param hero Le héros à détruire
 */
void destroyEceman(Eceman* hero) {
    free(hero->pos);
    free(hero);
}

/**
 * Place le héros à la case passée en paramètre.
 * @param board Le plateau du niveau
 * @param hero Le héros à placer
 * @return 0 si la case a été trouvée, -1 sinon
 */
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == elem) {
                hero->pos->x = x;
                hero->pos->y = y;
                hero->caseBelow = board[x][y];

                return 0;
            }
        }
    }

    return -1;
}

/**
 * Vérifie si le héros est entouré de murs ou d'eau.
 * @param board Le plateau sur lequel le joueur joue
 * @param hero Le héros à tester
 * @return 1 si le héros est encerclé, 0 sinon
 */
static int isSurrounded(char board[ROWS][COLS], Eceman* hero) {
    if (board[hero->pos->x][hero->pos->y] == DOOR_CHAR || board[hero->pos->x][hero->pos->y] == TUNNEL_CHAR)
        return 0;

    if ((board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR)
        && (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR)
        && (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR)
        && (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR))
        return 1;

    return 0;
}

/**
 * Affiche le message d'attaque et relance le jeu.
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman attaqué
 */
void gotAttacked(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    goToXY(1, 17);
    printf("Vous etes mort.\n");

    getch();

    goToXY(1, 17);
    printf("               \n");

    reloadLevel(game, board, hero);
}

/**
 * Déplace le Eceman sur le plateau de jeu.
 * Cette fonction augmente le score si le héro a avancé,
 * lance l'action de la case actuelle,
 * met à jour la toolbar avec le score,
 * recharge le niveau si le héro est encerclé.
 * @param key La touche appuyée
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le héros à déplacer
 * @param entityList La liste des entités
 */
void moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]) {
    unsigned short prevPosX = hero->pos->x;
    unsigned short prevPosY = hero->pos->y;
    unsigned short i;

    switch (key) {
        case UP_KEY:
            if (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR || board[hero->pos->x-1][hero->pos->y] == MOWER_CHAR) {
                if (board[hero->pos->x+1][hero->pos->y] == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        if (entityList[i]->pos->x == hero->pos->x && entityList[i]->pos->y == hero->pos->y)
                            moveEntity(game, hero, entityList[i], board);
                    }
                }

                return;
            }

            hero->pos->x -= 1;
            break;

        case DOWN_KEY:
            if (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR || board[hero->pos->x+1][hero->pos->y] == MOWER_CHAR) {
                if (board[hero->pos->x+1][hero->pos->y] == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        if (entityList[i]->pos->x == hero->pos->x && entityList[i]->pos->y == hero->pos->y)
                            moveEntity(game, hero, entityList[i], board);
                    }
                }

                return;
            }

            hero->pos->x += 1;
            break;

        case LEFT_KEY:
            if (board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR || board[hero->pos->x][hero->pos->y-1] == MOWER_CHAR) {
                if (board[hero->pos->x][hero->pos->y-1] == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        if (entityList[i]->pos->x == hero->pos->x && entityList[i]->pos->y == hero->pos->y)
                            moveEntity(game, hero, entityList[i], board);
                    }
                }

                return;
            }

            hero->pos->y -= 1;
            break;

        case RIGHT_KEY:
            if (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR || board[hero->pos->x][hero->pos->y+1] == MOWER_CHAR) {
                if (board[hero->pos->x][hero->pos->y+1] == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        if (entityList[i]->pos->x == hero->pos->x && entityList[i]->pos->y == hero->pos->y)
                            moveEntity(game, hero, entityList[i], board);
                    }
                }

                return;
            }

            hero->pos->y += 1;
            break;
    }

    hero->caseBelow = board[hero->pos->x][hero->pos->y];

    if (prevPosX != hero->pos->x || prevPosY != hero->pos->y) {
        runCaseAction(game, board, hero, entityList);
        drawToolbar(game);
    }

    if (isSurrounded(board, hero)) {
        goToXY(1, 17);
        printf("Vous etes encercle\n");

        getch();

        goToXY(1, 17);
        printf("                    \n");

        reloadLevel(game, board, hero);
    }
}

/**
 * Dessine le Eceman sur le plateau de jeu.
 * @param board Le plateau sur lequel le Eceman est ajouté
 * @param hero Le Eceman à ajouter
 */
void drawEceman(char board[ROWS][COLS], Eceman* hero) {
    goToXY(5, 22);
    printf("(%d, %d)\n", hero->pos->y, hero->pos->x);

    board[hero->pos->x][hero->pos->y] = HERO_CHAR;
    goToXY(hero->pos->y, hero->pos->x);

    setColor(HERO_CHAR_COLOR);
    putchar(convertCase(HERO_CHAR));
    resetColor();
}
