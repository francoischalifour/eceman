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
        case LIGHT_POTION:
            elem = 80;
            break;
    }

    return elem;
}

/**
 * Change le type de la case de Eceman avant son déplacement.
 * Cette fonction est appelée avant le déplacement du joueur.
 * @param board Le plateau de jeu
 * @param pos La position actuelle du héro
 * @param game Etat du jeu pour incrémenter le score
 * @param hero Héro pour verifier si il est léger
 * @return Le contenu de la case effective avant son déplacement
 */
void changeCaseType(char board[ROWS][COLS], Position* pos, GameState* game, Eceman* hero) {
    unsigned char currentCase = board[pos->x][pos->y];
    unsigned char elem = MELT_CHAR;
    unsigned short int color = MELT_CHAR_COLOR;
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hero->state == NORMAL) {
        switch (currentCase) {
            case THICK_CHAR:
                elem = THIN_CHAR;
                color = THIN_CHAR_COLOR;
                break;
        }
        game->levelScore++;
    } else {
        color = THIN_CHAR_COLOR;
        switch (currentCase) {
            case LIGHT_POTION:
                elem = THIN_CHAR;
                break;
            default:
                elem = currentCase;
        }
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
    unsigned char actualCase = board[hero->pos->x][hero->pos->y];

    switch (actualCase) {
        case DOOR_CHAR:
            if (game->level < getNbLevels())
                loadNextLevel(game, board, hero);
            break;
        case LIGHT_POTION:
            onDrinkPotion(hero);
            break;
    }
}
