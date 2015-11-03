#include "../lib/setup.h"
#include "../lib/eceman.h"
#include <windows.h>

/**
 * Compte le nombre d'ennemis sur le plateau
 * passé en paramètre.
 * @param board Le plateau de jeu
 * @return Le nombre d'ennemis sur le plateau
 */
int hasEnnemies(char board[ROWS][COLS]) {
    unsigned short x, y;
    unsigned short nbEnemies;

    nbEnemies = 0;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == ENEMY_CHAR)
                nbEnemies++;
        }
    }

    return nbEnemies;
}

/**
 * Compte le nombre tondeuses sur le plateau
 * passé en paramètre.
 * @param board Le plateau de jeu
 * @return Le nombre de tondeuse sur le plateau
 */
int hasMowers(char board[ROWS][COLS]) {
    unsigned short x, y;
    unsigned short nbMowers;

    nbMowers = 0;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == MOWER_CHAR)
                nbMowers++;
        }
    }

    return nbMowers;
}

/**
 * Récupère la position de l'ennemi sur la map.
 * @param board Le plateau de jeu
 * @return La position de l'ennemi
 */
Position* getEnemyPosition(char board[ROWS][COLS]) {
    Position* pos = malloc(sizeof(Position));
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == ENEMY_CHAR) {
                pos->x = x;
                pos->y = y;

                return pos;
            }
        }
    }

    return NULL;
}

/**
 * Récupère la position de l'outil passé en paramètre sur la map.
 * @param board Le plateau de jeu
 * @return La position de l'outil
 */
Position* getToolPosition(char board[ROWS][COLS], const char elem) {
    Position* pos = malloc(sizeof(Position));
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == elem) {
                pos->x = x;
                pos->y = y;

                return pos;
            }
        }
    }

    return NULL;
}

/**
 * Affiche les informations du jeu.
 * @param game L'état actuel du jeu
 */
void drawToolbar(GameState* game) {
    goToXY(26, 0);
    printf("Niveau %2d", game->level);
    goToXY(26, 1);
    printf("Score %3d\n\n", game->score + game->levelScore);
}

/**
 * Affiche la légende du jeu.
 */
static void drawPanel() {
    setColor(8);

    goToXY(26, 4);
    printf("%c %s\n", HERO_CHAR, "Personnage");
    goToXY(26, 5);
    printf("%c %s\n", convertCase(WALL_CHAR), "Mur");
    goToXY(26, 6);
    printf("%c %s\n", convertCase(DOOR_CHAR), "Porte de sortie");
    goToXY(26, 7);
    printf("%c %s\n", convertCase(THIN_CHAR), "Glace fine");
    goToXY(26, 8);
    printf("%c %s\n", convertCase(THICK_CHAR), "Glace epaisse");
    goToXY(26, 9);
    printf("%c %s\n", convertCase(MELT_CHAR), "Eau");
    goToXY(26, 10);
    printf("%c %s\n", convertCase(LIGHTNESS_POTION_CHAR), "Potion de legerete");
    goToXY(26, 11);
    printf("%c %s\n", convertCase(TUNNEL_CHAR), "Tunnel");

    goToXY(26, 15);
    printf("%s %4s\n", "Pause", "(p)");
    goToXY(26, 16);
    printf("%s %4s\n", "Recommencer le niveau", "(r)");
    goToXY(26, 17);
    printf("%s %2s\n", "Quitter", "(q)");

    resetColor();
}

/**
 * Dessine le plateau de jeu.
 * @param map Le fichier correspondant à la map
 * @param game L'état du jeu
 * @param board Le plateau à afficher
 */
void drawBoard(FILE* map, GameState* game, char board[ROWS][COLS]) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y <= COLS; y++) {
            board[x][y] = fgetc(map);

            setColor(getCaseColor(board[x][y]));
            putchar(convertCase(board[x][y]));
        }
    }

    resetColor();

    drawToolbar(game);
    drawPanel();

    printf("\n");

    closeMap(map);
}
