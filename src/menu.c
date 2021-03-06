/*
 * menu.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent le menu du jeu.
 *
 * Le choix de l'utilisateur est lancé directement à sa saisie, il n'y a pas
 * besoin de confirmation avec la touche 'entrée'.
 *
 * Objectifs :
 *     -    Récupérer le choix de l'utilisateur
 *     -    Lancer l'action de l'utilisateur
 */

#include "../lib/setup.h"
#include <conio.h>

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
            initGame(-1);
            break;
        case '2':
            initGame(0);
            break;
        case 'p':
            displayLevels(0);
            break;
        case 'r':
            displayRules();
            break;
        case 'c':
            displayRanking();
            break;
        case 'a':
            displayAbout();
            break;
        case 'e':
            displayEditor();
            break;
        case 'q':
            exitGame();
            break;
    }
}
