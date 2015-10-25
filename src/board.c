#include "../lib/setup.h"
#include "../lib/eceman.h"

/**
 * Retourne l'endroit de spawn de la map.
 * @param board Le plateau du niveau
 */
/*Position* getSpawnPosition(char board[ROWS][COLS]) {
    Position* pos = NULL;
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == SPAWN_CHAR) {
                pos->x = x;
                pos->y = y;

                break;
            }
        }
    }

    return pos;
}*/

/**
 * Dessine le plateau de jeu.
 * @param map Le fichier correspondant à la map
 * @param board Le plateau à afficher
 */
void drawBoard(FILE* map, char board[ROWS][COLS]) {
    unsigned short x, y;
    char elem;

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
