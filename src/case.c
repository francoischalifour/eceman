/*
 * case.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent les cases du plateau de jeu.
 *
 * Tous les types de cases sont répertoriés dans le fichier case.h.
 *
 * Objectifs :
 *     -    Convertir le symboles des cases en
 *           éléments semi-graphiques
 *     -    Récupérer la couleur d'une case en
 *           fonction de son symbole
 *     -    Changer le type d'une case
 *     -    Lancer l'action d'une case
 */

#include "../lib/setup.h"
#include <windows.h>
#include <conio.h>

/**
 * Convertit la case de la map en élément à afficher.
 * @param elem Le caractère initial
 * @return La case à afficher
 */
char convertCase(char elem) {
    switch (elem) {
        case HERO_CHAR:
            elem = 1;
            break;
        case THIN_CHAR:
            elem = 176;
            break;
        case THICK_CHAR:
            elem = 177;
            break;
        case SLIP_CHAR:
            elem = 178;
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
            elem = 223;
            break;
        case HOLE_CHAR:
            elem = 219;
            break;
        case MOWER_CHAR:
            elem = 202;
            break;
        case ENEMY_CHAR:
            elem = 2;
            break;
    }

    return elem;
}

/**
 * Récupère la couleur associée à la case.
 * @param elem La case
 * @return La couleur de la case
 */
int getCaseColor(const char elem) {
    unsigned short color;

    switch (elem) {
        case HERO_CHAR:
            color = HERO_CHAR_COLOR;
            break;
        case SPAWN_CHAR:
            color = SPAWN_CHAR_COLOR;
            break;
        case THIN_CHAR:
            color = THIN_CHAR_COLOR;
            break;
        case THICK_CHAR:
            color = THICK_CHAR_COLOR;
            break;
        case SLIP_CHAR:
            color = SLIP_CHAR_COLOR;
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
        case MOWER_CHAR:
            color = MOWER_CHAR_COLOR;
            break;
        case ENEMY_CHAR:
            color = ENEMY_CHAR_COLOR;
            break;
        default:
            color = 8;
    }

    return color;
}

/**
 * Change le type de la case du héros avant son déplacement.
 * Cette fonction est appelée avant le déplacement du joueur.
 * @param game L'état du jeu pour incrémenter le score
 * @param board Le plateau de jeu
 * @param hero Le héros pour verifier s'il a l'état de légèreté
 */
void changeCaseType(GameState* game, char board[ROWS][COLS], const Eceman* hero) {
    const unsigned char currentCase = hero->caseBelow;
    char elem;
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

        case SLIP_CHAR:
            elem = SLIP_CHAR;
            color = SLIP_CHAR_COLOR;
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
        if (hero->caseBelow != SLIP_CHAR)
            game->levelScore++;
    }

    goToXY(hero->pos->y, hero->pos->x);
    board[hero->pos->x][hero->pos->y] = elem;
    setColor(color);
    putchar(convertCase(elem));
    resetColor();
}

/**
 * Change le comportement du jeu en fonction de l'arrivée du héros sur une case.
 * Cette fonction est appelée après le déplacement du joueur.
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le héros
 * @param entityList La liste des entités
 */
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]) {
    const unsigned char currentCase = board[hero->pos->x][hero->pos->y];

    switch (currentCase) {
        case DOOR_CHAR:
            if (game->type == CAMPAIGN) {
                if (game->level < getNbLevels())
                    loadNextLevel(game, board, hero);
                else
                    gameOver(game);
                break;
            } else {
                gameOver(game);
            }

        case SLIP_CHAR:
            changeCaseType(game, board, hero);
            moveEceman(game, board, hero, entityList);
            drawEceman(board, hero);
            break;

        case LIGHTNESS_POTION_CHAR:
            hero->state = LIGHTNESS;
            break;

        case TUNNEL_CHAR:
            goToCase(board, hero, TUNNEL_EXIT_CHAR);
            break;

        case HOLE_CHAR:
            goToXY(1, 20);
            printf("Vous etes tombe dans un trou\n");
            getch();
            loadPreviousLevel(game, board, hero);
            printf("                            \n");
            break;

        case ENEMY_CHAR:
            gotAttacked(game, board, hero);
            break;
    }
}
