#include "../lib/setup.h"
#include "../lib/eceman.h"

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

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y <= COLS; y++) {
            board[x][y] = fgetc(map);
            putchar(convertCase(board[x][y]));
        }
    }

    printf("\n");

    drawToolbar(game);

    closeMap(map);
}
