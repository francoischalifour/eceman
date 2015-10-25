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
 */
void stopGame() {
    // TODO
    printf("\n\n\tPause\n");

    printf("\n\n\tAppuyez sur une touche pour reprendre...\n");

    getch();
}

/**
 * Place le curseur à l'endroit passé en paramètre.
 * @param x La ligne
 * @param y La colonne
 */
void goToXY(Position* pos) {
    COORD coord;

    coord.X = pos->x;
    coord.Y = pos->y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
