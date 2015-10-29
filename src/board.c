#include "../lib/setup.h"
#include "../lib/eceman.h"
#include <windows.h>

/**
 * Affiche les informations du jeu.
 * @param game L'état actuel du jeu
 */
void drawToolbar(GameState* game) {
    goToXY(26, 0);
    printf("Niveau %2d", game->level);
    goToXY(26, 1);
    printf("Score %3d\n\n", game->score + game->levelScore);
}

/**
 * Affiche la légende du jeu.
 */
static void drawPanel() {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 8);

    goToXY(26, 4);
    printf("%c %s\n", HERO_CHAR, "Personnage");
    goToXY(26, 5);
    printf("%c %s\n", convertCase(WALL_CHAR), "Mur");
    goToXY(26, 6);
    printf("%c %s\n", convertCase(DOOR_CHAR), "Porte de sortie");
    goToXY(26, 7);
    printf("%c %s\n", convertCase(THIN_CHAR), "Glace fine");
    goToXY(26, 8);
    printf("%c %s\n", convertCase(THICK_CHAR), "Glace epaisse");
    goToXY(26, 9);
    printf("%c %s\n", convertCase(MELT_CHAR), "Eau");
    goToXY(26, 10);
    printf("%c %s\n", convertCase(LIGHTNESS_POTION_CHAR), "Potion de legerete");
    goToXY(26, 11);
    printf("%c %s\n", convertCase(TUNNEL_CHAR), "Tunnel");

    goToXY(26, 13);
    printf("%s %4c\n", "Pause", 'p');
    goToXY(26, 14);
    printf("%s %2c\n", "Quitter", 'q');

    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

/**
 * Dessine le plateau de jeu.
 * @param map Le fichier correspondant à la map
 * @param game L'état du jeu
 * @param board Le plateau à afficher
 */
void drawBoard(FILE* map, GameState* game, char board[ROWS][COLS]) {
    unsigned short x, y;
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y <= COLS; y++) {
            board[x][y] = fgetc(map);

            SetConsoleTextAttribute(hConsole, getCaseColor(board[x][y]));
            putchar(convertCase(board[x][y]));
        }
    }

    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

    drawToolbar(game);
    drawPanel();

    printf("\n");

    closeMap(map);
}
