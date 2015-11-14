/*
 * main.c
 * Point d'entrée du jeu.
 *
 * Objectifs :
 *     -    Afficher le menu
 *     -    Lancer l'action de l'utilisateur
 */

#include "../lib/setup.h"

int main() {
    do {
        displayMenu();

        launchAction(getChoice());
    } while (1);

    return 0;
}
