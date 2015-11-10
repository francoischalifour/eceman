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

    goToXY(2, 20);
    printf("(l) Niveaux\n");
    goToXY(2, 21);
    printf("(c) Classement");

    goToXY(20, 20);
    printf("(r) Regles");
    goToXY(20, 21);
    printf("(a) A propos");

    goToXY(50, 19);
    printf("(m) Creer un niveau");
    goToXY(50, 20);
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
 */
void displayLevels() {
    unsigned short i;
    char key;

    displayTitle();

    printf("\tChoisir un niveau\n\n");

    for (i = 0; i < getNbLevels(); i++) {
        printf("\t(%d) Niveau %d\n", i + 1, i + 1);
    }

    printf("\n\t(r) Retour\n");

    key = getch();

    if (key != 'r')
        launchLevel(key);
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
