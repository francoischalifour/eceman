#include "../lib/setup.h"
#include "../lib/case.h"
#include <windows.h>

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
        case OUTSIDE_CHAR:
            elem = 178;
            break;
        case DOOR_CHAR:
            elem = 233;
            break;
    }

    return elem;
}

/**
 * Récupère la couleur associée à la case.
 * @param elem La case
 * @return La couleur de la case
 */
int getCaseColor(char elem) {
    unsigned short color;

    switch (elem) {
        case THIN_CHAR:
            color = THIN_CHAR_COLOR;
            break;
        case THICK_CHAR:
            color = THICK_CHAR_COLOR;
            break;
        case DOOR_CHAR:
            color = DOOR_CHAR_COLOR;
            break;
        case WALL_CHAR:
            color = WALL_CHAR_COLOR;
            break;
        case MELT_CHAR:
            color = MELT_CHAR_COLOR;
            break;
        case OUTSIDE_CHAR:
            color = OUTSIDE_CHAR_COLOR;
            break;
        default:
            color = 8;
    }

    return color;
}

/**
 * Change le type de la case de Eceman avant son déplacement.
 * Cette fonction est appelée avant le déplacement du joueur.
 * @param board Le plateau de jeu
 * @param pos La position actuelle du héro
 * @return Le contenu de la case effective avant son déplacement
 */
void changeCaseType(char board[ROWS][COLS], Position* pos) {
    unsigned char currentCase = board[pos->x][pos->y];
    unsigned char elem = MELT_CHAR;
    unsigned short int color = MELT_CHAR_COLOR;
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (currentCase) {
        case THICK_CHAR:
            elem = THIN_CHAR;
            color = THIN_CHAR_COLOR;
            break;
    }

    goToXY(pos->y, pos->x);
    board[pos->x][pos->y] = elem;
    SetConsoleTextAttribute(hConsole, color);
    putchar(convertCase(elem));
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

/**
 * Change le comportement du jeu en fonction de l'arrivée sur une case.
 * Cette fonction est appelée après le déplacement du joueur.
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 */
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    const unsigned char actualCase = board[hero->pos->x][hero->pos->y];

    switch (actualCase) {
        case DOOR_CHAR:
            if (game->level < getNbLevels())
                loadNextLevel(game, board, hero);
            else
                gameOver(game);
            break;
    }
}
