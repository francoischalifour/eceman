/*
 * display.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent l'affichage et l'interface.
 *
 * Objectifs :
 *     -    Afficher le titre du jeu
 *     -    Afficher le menu
 *     -    Afficher les réglages
 *     -    Afficher les niveaux
 *     -    Afficher l'éditeur de niveaux
 *     -    Afficher les règles
 *     -    Afficher le game over
 *     -    Afficher le classement
 *     -    Afficher les informations à propos du jeu
 */

#include "../lib/setup.h"
#include <windows.h>
#include <string.h>
#include <conio.h>

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

    displayTitle();

    goToXY(10, 10);
    printf("(1) Commencer une nouvelle partie\n");

    if ((saving = loadSaving())) {
        goToXY(10, 12);
        printf("(2) Continuer la partie precedente\n");

        setColor(GRAY_COLOR);
        goToXY(20, 14);
        printf("Niveau %2d", getLastLevel(saving));
        goToXY(20, 15);
        printf("Score %3d\n\n", getLastScore(saving));
        resetColor();

        closeSaving(saving);
    }

    goToXY(2, 19);
    printf("(l) Niveaux\n");
    goToXY(2, 20);
    printf("(e) Editeur");
    goToXY(2, 21);
    printf("(c) Classement");

    goToXY(20, 19);
    printf("(r) Regles");
    goToXY(20, 20);
    printf("(a) A propos");
    goToXY(20, 21);
    printf("(o) Options");

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
 * Affiche les niveaux.
 * @param mode 0 pour jeu, 1 pour éditeur
 */
void displayLevels(const int mode) {
    unsigned short i, choixPos;
    unsigned short level;
    char key;

    displayTitle();

    printf("\tChoisir un niveau\n\n");

    for (i = 0; i < getNbLevels(); i++) {
        printf("\tNiveau %d\n", i + 1);
    }

    printf("\n\t(r) Retour\n");

    // Position initiale de la flèche.
    choixPos = 9;
    level = 1;

    goToXY(5, choixPos);
    printf("->");

    key = '0';

    while (key != '\r') {
        key = getch();

        switch (key) {
            case UP_KEY:
                if (level > 1) {
                    level--;
                    goToXY(5, choixPos);
                    printf("  ");
                    choixPos--;
                    goToXY(5, choixPos);
                    printf("->");
                }
                break;
            case DOWN_KEY:
                if (level < getNbLevels()) {
                    level++;
                    goToXY(5, choixPos);
                    printf("  ");
                    choixPos++;
                    goToXY(5, choixPos);
                    printf("->");
                }
                break;
            case '\r':
                if (mode != 0)
                    editMap(level);
                else
                    launchLevel(level);
                break;
            case 'r':
                return;
        }
    }
}

/**
 * Affiche l'éditeur de niveaux.
 */
void displayEditor() {
    displayTitle();

    printf("\tEditeur de niveau\n\n");

    printf("\t(1) Modifier un niveau existant\n");
    printf("\t(2) Creer un nouveau niveau\n");

        switch (getch()) {
            case '1':
                displayLevels(1);
                break;
            case '2':
                editMap(0);
                break;
        }
}

/**
 * Affiche les règles du jeu.
 */
void displayRules() {
    FILE* rules = NULL;
    char c;

    rules = fopen("../data/info/rules.txt", "r");

    displayTitle();

    printf("\tRegles\n\n");

    while ((c = fgetc(rules)) != EOF) {
        putchar(c);
    }

    fclose(rules);

    goBack();
}

/**
 * Affiche le message de fin de jeu.
 * @param score Le score final
 */
void displayGameOver(const int scoreFinal) {
    displayTitle();

    printf("\tGame Over\n\n");
    printf("\tScore %4d\n", scoreFinal);
}

/**
 * Affiche le classement des scores du fichier des scores.
 */
void displayRanking() {
    FILE* scoreFile = NULL;

    scoreFile = fopen(SCORE_FILE, "r");

    displayTitle();

    printf("\tClassement des meilleurs scores\n\n");

    getRanking(scoreFile);

    fclose(scoreFile);

    goBack();
}

/**
 * Affiche les crédits du jeu.
 */
void displayAbout() {
    FILE* about = NULL;
    char c;

    about = fopen("../data/info/about.txt", "r");

    displayTitle();

    printf("\tA propos\n\n");

    while ((c = fgetc(about)) != EOF) {
        putchar(c);
    }

    fclose(about);

    printf("\n");

    goBack();
}
