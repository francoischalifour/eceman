#include "../lib/setup.h"
#include <conio.h>
#include <windows.h>
#include <string.h>

/**
 * Attend l'appui d'une touche pour revenir au menu.
 */
void goBack() {
    printf("\n\n\tAppuyez sur une touche pour continuer...\n");

    getch();
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

/**
 * Convertit un caractère en entier.
 * @param c Caractère à convertir
 * @return Le caractère converti en entier
 */
int convertToInt(const char c) {
 char string[2];

 string[0] = c;
 string[1] = '\0';

 return (int) strtol(string, NULL, 10);
}

/**
 * Initialise une couleur à afficher à l'écran.
 * @param color La couleur
 */
void setColor(const int color) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

/**
 * Réinitialise la couleur à afficher.
 */
void resetColor() {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}
