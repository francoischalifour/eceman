/*
 * eceman.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent le personnage principal.
 *
 * Le héros est le personnage que le joueur manipule, une seule instance doit
 * être créée. Il se déplacera lors de l'appui des touches UP_KEY, DOWN_KEY,
 * LEFT_KEY et RIGHT_KEY définies dans game.h.
 *
 * Objectifs :
 *     -    Créer et détruire un personnage
 *     -    Téléporter un personnage
 *     -    Vérifier s'il est encerclé
 *     -    Vérifier s'il est attaqué
 *     -    Bouger un personnage
 *     -    Dessiner et nettoyer l'affichage un personnage
 */

#include "../lib/setup.h"
#include <windows.h>
#include <conio.h>

/**
 * Créé un nouveau héros.
 * Initialise son état, sa position et la case sur laquelle il se situe.
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
 * Libère la mémoire liée au héros.
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
 * Récupère la case après le héros suivant sa direction.
 * @param hero Le héros
 * @param board Le plateau de jeu
 * @return La case après le héros
 */
static char getNextCase(Eceman* hero, char board[ROWS][COLS]) {
    switch (hero->direction) {
        case UP:
            return board[hero->pos->x-1][hero->pos->y];
            break;
        case DOWN:
            return board[hero->pos->x+1][hero->pos->y];
            break;
        case LEFT:
            return board[hero->pos->x][hero->pos->y-1];
            break;
        case RIGHT:
            return board[hero->pos->x][hero->pos->y+1];
            break;
    }

    return WALL_CHAR;
}

/**
 * Vérifie la case de l'autre côté de la tondeuse par rapport au joueur.
 * @param  hero   Le héro
 * @param  board  Le plateau de jeu
 * @param  xMower La position de la tondeuse en X
 * @param  yMower La position de la tondeuse en Y
 * @return        Le caractère derrière la tondeuse
 */
char getNextCaseMower(Eceman* hero, char board[ROWS][COLS], unsigned short xMower, unsigned short yMower) {
    short x, y;
    if(board[xMower][yMower] == MOWER_CHAR){
            x = hero->pos->x - xMower;
            y = hero->pos->y - yMower;
            return board[xMower - x][yMower - y];
    }
    return OUTSIDE_CHAR;

}

/**
 * Vérifie si le héros est entouré de murs ou d'eau.
 * @param board Le plateau sur lequel le joueur joue
 * @param hero Le héros à tester
 * @return 1 si le héros est encerclé, 0 sinon
 */
static int isSurrounded(char board[ROWS][COLS], Eceman* hero) {
    if (hero->caseBelow == DOOR_CHAR || hero->caseBelow == TUNNEL_CHAR)
        return 0;

    if ((board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR || (board[hero->pos->x][hero->pos->y-1] == MOWER_CHAR && (getNextCaseMower(hero, board, hero->pos->x, hero->pos->y-1) == WALL_CHAR || getNextCaseMower(hero, board, hero->pos->x, hero->pos->y-1) == MELT_CHAR)))
        && (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR || (board[hero->pos->x][hero->pos->y+1] == MOWER_CHAR && (getNextCaseMower(hero, board, hero->pos->x, hero->pos->y+1) == WALL_CHAR || getNextCaseMower(hero, board, hero->pos->x, hero->pos->y+1) == MELT_CHAR)))
        && (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR || (board[hero->pos->x-1][hero->pos->y] == MOWER_CHAR && (getNextCaseMower(hero, board, hero->pos->x-1, hero->pos->y) == WALL_CHAR || getNextCaseMower(hero, board, hero->pos->x-1, hero->pos->y) == MELT_CHAR)))
        && (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR || (board[hero->pos->x+1][hero->pos->y] == MOWER_CHAR && (getNextCaseMower(hero, board, hero->pos->x+1, hero->pos->y) == WALL_CHAR || getNextCaseMower(hero, board, hero->pos->x+1, hero->pos->y) == MELT_CHAR))))
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
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le héros à déplacer
 * @param entityList La liste des entités
 */
void moveEceman(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]) {
    unsigned short prevPosX = hero->pos->x;
    unsigned short prevPosY = hero->pos->y;
    unsigned short i;

    switch (hero->direction) {
        case UP:
            if (getNextCase(hero, board) == WALL_CHAR || getNextCase(hero, board) == MELT_CHAR || getNextCase(hero, board) == MOWER_CHAR) {
                if (getNextCase(hero, board) == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        entityList[i]->state = ACTIVE;
                        if (entityList[i]->pos->x == hero->pos->x-1 && entityList[i]->pos->y == hero->pos->y) {
                            entityList[i]->direction = UP;
                            throwEntity(game, hero, entityList[i], board);
                            return;
                        }
                    }
                }
                return;
            }

            hero->pos->x -= 1;
            break;

        case DOWN:
            if (getNextCase(hero, board) == WALL_CHAR || getNextCase(hero, board) == MELT_CHAR || getNextCase(hero, board) == MOWER_CHAR) {
                if (getNextCase(hero, board) == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        entityList[i]->state = ACTIVE;
                        if (entityList[i]->pos->x == hero->pos->x+1 && entityList[i]->pos->y == hero->pos->y) {
                            entityList[i]->direction = DOWN;
                            throwEntity(game, hero, entityList[i], board);
                            return;
                        }
                    }
                }
                return;
            }

            hero->pos->x += 1;
            break;

        case LEFT:
            if (getNextCase(hero, board) == WALL_CHAR || getNextCase(hero, board) == MELT_CHAR || getNextCase(hero, board) == MOWER_CHAR) {
                if (getNextCase(hero, board) == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        entityList[i]->state = ACTIVE;
                        if (entityList[i]->pos->x == hero->pos->x && entityList[i]->pos->y == hero->pos->y-1) {
                            entityList[i]->direction = LEFT;
                            throwEntity(game, hero, entityList[i], board);
                            return;
                        }
                    }
                }
                return;
            }

            hero->pos->y -= 1;
            break;

        case RIGHT:
            if (getNextCase(hero, board) == WALL_CHAR || getNextCase(hero, board) == MELT_CHAR || getNextCase(hero, board) == MOWER_CHAR) {
                if (getNextCase(hero, board) == MOWER_CHAR) {
                    for (i = 0; i < ENTITY_MAX; i++) {
                        entityList[i]->state = ACTIVE;
                        if (entityList[i]->pos->x == hero->pos->x && entityList[i]->pos->y == hero->pos->y+1) {
                            entityList[i]->direction = RIGHT;
                            throwEntity(game, hero, entityList[i], board);
                            return;
                        }
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
        printf("Vous etes encercle\nESPACE pour continuer\n");
        while (getch() != ' ');
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
void drawEceman(char board[ROWS][COLS], const Eceman* hero) {
    board[hero->pos->x][hero->pos->y] = HERO_CHAR;
    goToXY(hero->pos->y, hero->pos->x);

    setColor(HERO_CHAR_COLOR);
    putchar(convertCase(HERO_CHAR));
    resetColor();
}
