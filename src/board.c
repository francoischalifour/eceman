#include "../lib/setup.h"
#include "../lib/eceman.h"
#include <windows.h>

/**
 * Convertit le caractère de la map en élément à afficher.
 * @param elem Le caractère initial
 * @return L'élément à afficher
 */
static char convertMap(char elem) {
    switch(elem) {
        case '0':
            elem = ' ';
            break;
    }

    return elem;
}

/**
 * Initialise le plateau de jeu.
 * @return Le plateau de jeu
 */
void initBoard(char board[ROWS][COLS]) {
    unsigned short i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = '0';
        }
    }
}

/**
 * Nettoie l'emplacement du Eceman sur le plateau de jeu.
 * @param board Le plateau sur lequel le Eceman est à enlever
 * @param hero Le Eceman à nettoyer
 */
void clearEceman(char board[ROWS][COLS], Eceman* hero) {
     // TODO : prendre en compte les cases épaisses et les outils
    board[hero->pos->x][hero->pos->y] = MELT_CHAR;
    goToXY(hero->pos);
    putchar(convertMap(MELT_CHAR));
}

/**
 * Dessine le Eceman sur le plateau de jeu.
 * @param board Le plateau sur lequel le Eceman est ajouté
 * @param hero Le Eceman à ajouter
 */
void drawEceman(char board[ROWS][COLS], Eceman* hero) {
    board[hero->pos->x][hero->pos->y] = HERO_CHAR;
    putchar(HERO_CHAR);
    goToXY(hero->pos);
}

/**
 * Dessine le plateau de jeu.
 * @param board Le plateau à afficher
 */
void drawBoard(char board[ROWS][COLS], Eceman* hero) {
    unsigned short i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%c", convertMap(board[i][j]));
        }
    }

    printf("\n");
}
