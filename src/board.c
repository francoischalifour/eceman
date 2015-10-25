#include "../lib/setup.h"
#include "../lib/eceman.h"

/**
 * Affiche les informations du jeu.
 * @param game L'état actuel du jeu
 */
void drawToolbar(GameState* game) {
    goToXY(0, 0);
    printf("Niveau %d \tScore : %d\n\n", game->level, game->score + game->levelScore);
}

/**
 * Dessine le plateau de jeu.
 * @param map Le fichier correspondant à la map
 * @param board Le plateau à afficher
 */
void drawBoard(FILE* map, char board[ROWS][COLS], GameState* game) {
    unsigned short x, y;
    char elem;

    drawToolbar(game);

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS ; y++) {
            elem = fgetc(map);
            putchar(convertCase(elem));
            board[x][y] = elem;
        }
    }

    printf("\n");

    closeMap(map);
}
