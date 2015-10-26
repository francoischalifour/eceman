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
    unsigned short x = 0, y = 0;
    unsigned char elem;

    while (x < ROWS - 1) {
        y = 0;
        while ((elem = getc(map)) != '\n') {
            board[x][y] = elem;
            putchar(convertCase(board[x][y]));
            y++;
        }
        x++;
        printf("\n");
    }

    printf("\n");

    drawToolbar(game);

    printf("\n");

    closeMap(map);
}
