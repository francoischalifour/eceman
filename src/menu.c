#include <conio.h>
#include "../lib/setup.h"

/**
 * Enregistre le choix de l'utilisateur.
 * @return choice Le choix de l'utilisateur
 */
char getChoice() {
    while (1) {
        if (kbhit())
            return getch();
    }
}

/**
 * Quitte le programme.
 */
static void exitGame() {
    exit(EXIT_SUCCESS);
}

/**
 * Execute l'option sélectionnée dans le menu.
 * @param choice Le choix saisi par l'utilisateur
 */
void launchAction(const char choice) {
    switch (choice) {
        case '1':
            initGame(1);
        case '2':
            initGame(0);
        case 'o':
            displaySettings();
            break;
        case 'r':
            displayRules();
            break;
        case 'q':
            exitGame();
            break;
    }
}
