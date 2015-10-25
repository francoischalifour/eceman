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
 * Affiche un message d'erreur suite à un mauvais choix.
 */
static void wrongChoice() {
    printf("\aVous avez saisi un mauvais choix.\n\n");
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
            startGame();
            break;
        case '2':
            displaySettings();
            break;
        case '3':
            displayRules();
            break;
        case QUIT_CHOICE:
            exitGame();
            break;
        default:
            wrongChoice();
    }
}
