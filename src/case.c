#include "../lib/setup.h"
#include "../lib/case.h"

/**
 * Convertit la case de la map en élément à afficher.
 * @param elem Le caractère initial
 * @return La case à afficher
 */
char convertCase(char elem) {
    switch (elem) {
        case WALL_CHAR:
            elem = 254;
            break;
        case THIN_CHAR:
            elem = 176;
            break;
        case THICK_CHAR:
            elem = 177;
            break;
        case MELT_CHAR:
            elem = 247;
            break;
        case UNDEFINED_CHAR:
            elem = 178;
            break;
        case DOOR_CHAR:
            elem = 233;
            break;
    }

    return elem;
}

/**
 * Change le type de la case de Eceman avant son déplacement.
 * Cette fonction est appelée avant le déplacement du joueur.
 * @param board Le plateau de jeu
 * @param pos La position actuelle du héro
 * @return Le contenu de la case effective avant son déplacement
 */
void changeCaseType(char board[ROWS][COLS], Position* pos) {
    char currentCase = board[pos->x][pos->y];
    char elem = MELT_CHAR;

    switch (currentCase) {
        case THICK_CHAR:
            elem = THIN_CHAR;
            break;
    }

    goToXY(pos);
    board[pos->x][pos->y] = elem;
    putchar(convertCase(elem));
}

/**
 * Change le comportement du jeu en fonction de l'arrivée sur une case.
 * Cette fonction est appelée après le déplacement du joueur.
 * @param board Le plateau de jeu
 * @param pos La position du héro
 * @return La case effective après son déplacement
 */
void runCaseAction(char board[ROWS][COLS], Position* pos) {
    unsigned char actualCase = board[pos->x][pos->y];

    switch(actualCase) {
        case DOOR:
            loadNextLevel();
            break;

        case MELT:
            gameOver();
            break;
    }
}
