#include "../lib/setup.h"

/**
 * Affiche le titre du jeu.
 */
void displayTitle() {
  system("cls");

    printf("\t ______   ______   ______   __    __   ______   __   __\n\
\t/\\  ___\\ /\\  ___\\ /\\  ___\\ /\\ \"-./  \\ /\\  __ \\ /\\ \"-.\\ \\  \n\
\t\\ \\  __\\ \\ \\ \\____\\ \\  __\\ \\ \\ \\-./\\ \\\\ \\  __ \\\\ \\ \\-.  \\ \n\
\t \\ \\_____\\\\ \\_____\\\\ \\_____\\\\ \\_\\ \\ \\_\\\\ \\_\\ \\_\\\\ \\_\\\\\"\\_\\\n\
\t  \\/_____/ \\/_____/ \\/_____/ \\/_/  \\/_/ \\/_/\\/_/ \\/_/ \\/_/\n\n");
}


/**
 * Affiche le menu.
 */
void displayMenu() {
    displayTitle();

    printf("\t1. Jouer\n");
    printf("\t2. Options\n");
    printf("\t3. Regles\n");
    printf("\t%c. Quitter\n", QUIT_CHOICE);

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
    displayTitle();

    printf("\tRegles\n\n");

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
