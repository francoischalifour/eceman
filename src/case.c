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
 * @param game L'état du jeu pour incrémenter le score
 * @param board Le plateau de jeu
 * @param hero Le Eceman pour verifier s'il a l'état de légèreté
 * @return Le contenu de la case effective avant son déplacement
 */
void changeCaseType(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    const unsigned char currentCase = board[hero->pos->x][hero->pos->y];
    unsigned char elem;
    unsigned short int color;
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (currentCase) {
        case THIN_CHAR:
            if (hero->state == LIGHTNESS) {
                elem = currentCase;
                color = THIN_CHAR_COLOR;
            } else {
                elem = MELT_CHAR;
                color = MELT_CHAR_COLOR;
            }
            break;

        case THICK_CHAR:
            if (hero->state == LIGHTNESS) {
                elem = THICK_CHAR;
                color = THICK_CHAR_COLOR;
            } else {
                elem = THIN_CHAR;
                color = THIN_CHAR_COLOR;
            }
            break;

        case LIGHT_POTION:
            elem = THIN_CHAR;
            color = THIN_CHAR_COLOR;
            break;

        default:
            elem = MELT_CHAR;
            color = MELT_CHAR_COLOR;
    }

    if (hero->state != LIGHTNESS) {
        game->levelScore++;
    }

    goToXY(hero->pos->y, hero->pos->x);
    board[hero->pos->x][hero->pos->y] = elem;
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

        case LIGHT_POTION:
            hero->state = LIGHTNESS;
            break;
    }
}
