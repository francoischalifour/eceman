/*
 * functions.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui utiles au jeu.
 *
 * Objectifs :
 *     -    Attendre l'appui d'une touche pour continuer
 *           une action
 *     -    Changer l'emplacement du curseur pour afficher un caractère
 *           à un endroit particulier
 *     -    Changer la couleur d'un caractère
 */

#include "../lib/setup.h"
#include <windows.h>
#include <conio.h>

/**
 * Attend l'appui d'une touche pour revenir au menu.
 */
void goBack() {
    setColor(GRAY_COLOR);
    printf("\n\n\tAppuyez sur une touche pour continuer...\n");
    resetColor();

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
