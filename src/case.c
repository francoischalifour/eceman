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
        case WALL_CHAR:
            elem = 254;
            break;
        case DOOR_CHAR:
            elem = 233;
            break;
        case LIGHTNESS_POTION_CHAR:
            elem = 236;
            break;
        case TUNNEL_CHAR:
            elem = 220;
            break;
        case TUNNEL_EXIT_CHAR:
            elem = 220;
            break;
        case ENEMY_CHAR:
            elem = '&';
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
        case MELT_CHAR:
            color = MELT_CHAR_COLOR;
            break;
        case OUTSIDE_CHAR:
            color = OUTSIDE_CHAR_COLOR;
            break;
        case WALL_CHAR:
            color = WALL_CHAR_COLOR;
            break;
        case DOOR_CHAR:
            color = DOOR_CHAR_COLOR;
            break;
        case LIGHTNESS_POTION_CHAR:
            color = LIGHTNESS_POTION_CHAR_COLOR;
            break;
        case TUNNEL_CHAR:
            color = TUNNEL_CHAR_COLOR;
            break;
        case TUNNEL_EXIT_CHAR:
            color = TUNNEL_CHAR_COLOR;
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
    const unsigned char currentCase = hero->caseBelow;
    unsigned char elem;
    unsigned short int color;

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

        case LIGHTNESS_POTION_CHAR:
            elem = THIN_CHAR;
            color = THIN_CHAR_COLOR;
            break;

        case TUNNEL_EXIT_CHAR:
            elem = TUNNEL_EXIT_CHAR;
            color = TUNNEL_CHAR_COLOR;
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
    setColor(color);
    putchar(convertCase(elem));
    resetColor();
}

/**
 * Change le comportement du jeu en fonction de l'arrivée sur une case.
 * Cette fonction est appelée après le déplacement du joueur.
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 */
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    const unsigned char currentCase = board[hero->pos->x][hero->pos->y];

    switch (currentCase) {
        case DOOR_CHAR:
            if (game->level < getNbLevels())
                loadNextLevel(game, board, hero);
            else
                gameOver(game);
            break;

        case LIGHTNESS_POTION_CHAR:
            hero->state = LIGHTNESS;
            break;

        case TUNNEL_CHAR:
            goToCase(board, hero, TUNNEL_EXIT_CHAR);
            break;

        case MOWER_CHAR:
            runToolAction(game, board, hero, MOWER);
            break;

        case ENEMY_CHAR:
            gotAttacked(game, board, hero);
            break;
    }
}
