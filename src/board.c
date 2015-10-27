#include "../lib/setup.h"
#include "../lib/eceman.h"
#include <windows.h>

/**
 * Affiche les informations du jeu.
 * @param game L'état actuel du jeu
 */
void drawToolbar(GameState* game) {
    goToXY(0, 16);
    printf("Niveau %d \tScore : %d\n\n", game->level, game->score + game->levelScore);
}

/**
 * Dessine le plateau de jeu.
 * @param map Le fichier correspondant à la map
 * @param game L'état du jeu
 * @param board Le plateau à afficher
 */
void drawBoard(FILE* map, GameState* game, char board[ROWS][COLS]) {
    unsigned short x, y;
    unsigned short color;
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y <= COLS; y++) {
            board[x][y] = fgetc(map);

            switch (board[x][y]) {
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

            SetConsoleTextAttribute(hConsole, color);
            putchar(convertCase(board[x][y]));
        }
    }

    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

    printf("\n");

    drawToolbar(game);

    closeMap(map);
}
