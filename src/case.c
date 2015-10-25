#include "../lib/setup.h"
#include "../lib/case.h"

/**
 * Change le type de la case de Eceman avant son déplacement.
 * Cette fonction est appelée avant le déplacement du joueur.
 * @param board Le plateau de jeu
 * @param pos La position actuelle du héro
 * @return Le contenu de la case effective avant son déplacement
 */
char changeCaseType(char board[ROWS][COLS], Position* pos) {
    unsigned char actualCase = board[pos->x][pos->y];

    switch (actualCase) {
        case THIN:
            board[pos->x][pos->y] = MELT;
            break;

        case THICK:
            board[pos->x][pos->y] = THIN;
            break;
    }

    return actualCase;
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
