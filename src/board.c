/*
 * board.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent le plateau de jeu.
 *
 * Le plateau de jeu se présente comme une matrice de caractères de 15 lignes
 * par 19 colonnes (constantes ROWS et COLS).
 * Cette matrice est créée à partir d'un fichier map composé de caractères
 * correspondant à un certain type de case.
 *
 * Objectifs :
 *     -    Extraire les entités de la map
 *     -    Afficher le panel et le plateau
 */

#include "../lib/setup.h"
#include <windows.h>

/**
 * Extrait les entités de la map.
 * @param board Le plateau de jeu
 * @param entityList La liste des entités extraites
 */
void extractEntities(char board[ROWS][COLS], Entity* entityList[ENTITY_MAX]) {
    unsigned short x, y;
    int count;
    Entity* entity = NULL;

    count = -1;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            entity = NULL;

            switch (board[x][y]) {
                case ENEMY_CHAR:
                    entity = createEnemy(x, y, UP);
                    count++;
                    break;
                case MOWER_CHAR:
                    entity = createMower(x, y, RIGHT);
                    count++;
                    break;
            }

            if (entity != NULL)
                entityList[count] = entity;
        }
    }
}

/**
 * Affiche les informations du jeu.
 * @param game L'état actuel du jeu
 */
void drawToolbar(const GameState* game) {
    goToXY(26, 0);
    printf("Niveau %2u", game->level);
    goToXY(26, 1);
    printf("Score %3u\n\n", game->score + game->levelScore);
}

/**
 * Affiche la légende du jeu.
 */
static void drawPanel() {
    setColor(GRAY_COLOR);

    goToXY(26, 3);
    setColor(getCaseColor(HERO_CHAR));
    printf("%c", convertCase(HERO_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Personnage");

    goToXY(26, 4);
    setColor(getCaseColor(ENEMY_CHAR));
    printf("%c", convertCase(ENEMY_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Ennemi");

    goToXY(26, 5);
    setColor(getCaseColor(WALL_CHAR));
    printf("%c", convertCase(WALL_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Mur");

    goToXY(26, 6);
    setColor(getCaseColor(DOOR_CHAR));
    printf("%c", convertCase(DOOR_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Porte de sortie");

    goToXY(26, 7);
    setColor(getCaseColor(THIN_CHAR));
    printf("%c", convertCase(THIN_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Glace fine");

    goToXY(26, 8);
    setColor(getCaseColor(THICK_CHAR));
    printf("%c", convertCase(THICK_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Glace epaisse");

    goToXY(26, 9);
    setColor(getCaseColor(MELT_CHAR));
    printf("%c", convertCase(MELT_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Eau");

    goToXY(26, 10);
    setColor(getCaseColor(LIGHTNESS_POTION_CHAR));
    printf("%c", convertCase(LIGHTNESS_POTION_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Potion de legerete");

    goToXY(26, 11);
    setColor(getCaseColor(TUNNEL_CHAR));
    printf("%c", convertCase(TUNNEL_CHAR));
    setColor(GRAY_COLOR);
    printf(" %s\n", "Tunnel");

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
void drawBoard(FILE* map, const GameState* game, char board[ROWS][COLS]) {
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
