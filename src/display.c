#include "../lib/setup.h"
#include <windows.h>

/**
 * Affiche le titre du jeu.
 */
void displayTitle() {
  system("cls");

    printf("\n\t ______   ______   ______   __    __   ______   __   __\n\
\t/\\  ___\\ /\\  ___\\ /\\  ___\\ /\\ \"-./  \\ /\\  __ \\ /\\ \"-.\\ \\  \n\
\t\\ \\  __\\ \\ \\ \\____\\ \\  __\\ \\ \\ \\-./\\ \\\\ \\  __ \\\\ \\ \\-.  \\ \n\
\t \\ \\_____\\\\ \\_____\\\\ \\_____\\\\ \\_\\ \\ \\_\\\\ \\_\\ \\_\\\\ \\_\\\\\"\\_\\\n\
\t  \\/_____/ \\/_____/ \\/_____/ \\/_/  \\/_/ \\/_/\\/_/ \\/_/ \\/_/\n\n");
}

/**
 * Affiche le menu.
 */
void displayMenu() {
    FILE* saving = NULL;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    displayTitle();

    goToXY(10, 10);
    printf("(1) Commencer une nouvelle partie\n");

    if ((saving = loadSaving())) {
        goToXY(10, 12);
        printf("(2) Continuer la partie precedente\n");

        SetConsoleTextAttribute(hConsole, 8);
        goToXY(20, 14);
        printf("Niveau %2d", getLevel(saving));
        goToXY(20, 15);
        printf("Score %3d\n\n", getScore(saving));
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    }

    goToXY(2, 20);
    printf("(o) Options");
    goToXY(2, 21);
    printf("(r) Regles");

    goToXY(50, 21);
    printf("(q) Quitter");

    printf("\n");
}

/**
 * Affiche les options.
 */
void displaySettings() {
    displayTitle();

    printf("\tOptions\n\n");

    goBack();
}

/**
 * Affiche les règles du jeu.
 */
void displayRules() {
    FILE* rules = NULL;
    char c;

    rules = fopen("../data/rules.txt", "r");

    displayTitle();

    printf("\tRegles\n\n");

    while ((c = fgetc(rules)) != EOF) {
        putchar(c);
    }

    printf("\n");

    goBack();
}

/**
 * Affiche le message de fin de jeu.
 */
void displayGameOver() {
    printf("                        _______                            _______                    \n\
                       |     __|.---.-.--------.-----.    |       |.--.--.-----.----. \n\
                       |    |  ||  _  |        |  -__|    |   -   ||  |  |  -__|   _| \n\
                       |_______||___._|__|__|__|_____|    |_______| \\___/|_____|__|\n\n");
}
