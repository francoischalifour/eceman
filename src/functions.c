#include <conio.h>
#include <windows.h>
#include "../lib/setup.h"

/**
 * Attend l'appui d'une touche pour revenir au menu.
 */
void goBack() {
    printf("\n\n\tAppuyez sur une touche pour continuer...\n");

    getch();
    displayMenu();
}

/**
 * Met le jeu en pause.
 * Bloque le timer et toutes les interactions.
 * @param game L'état du jeu
 */
void stopGame(GameState* game) {
    game->pause = 1;
    goToXY(22, 0);
    printf("Pause\n");

    getch();

    game->pause = 0;
    goToXY(22, 0);
    printf("     \n");
}

/**
 * Place le curseur à l'endroit passé en paramètre.
 * @param x La ligne
 * @param y La colonne
 */
void goToXY(const unsigned short x, const unsigned short y) {
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
