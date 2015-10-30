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

    goToXY(20, 20);
    printf("(c) Classement");
    goToXY(20, 21);
    printf("(a) A propos");

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

    rules = fopen("../data/info/rules.txt", "r");

    displayTitle();

    printf("\tRegles\n\n");

    while ((c = fgetc(rules)) != EOF) {
        putchar(c);
    }

    fclose(rules);
    printf("\n");

    goBack();
}

/**
 * Affiche le message de fin de jeu.
 */
void displayGameOver() {
    system("cls");
    printf("\tGame Over");
}

/**
 * Affiche le classement des scores du fichier scores.sav.
 */
void displayRanking(){
    FILE* scoreFile = NULL;
    unsigned int score;
    char name[35];

    scoreFile = fopen("../data/saving/scores.sav", "r");

    displayTitle();

    printf("\tClassement des meilleurs scores\n\n");

    // TODO : afficher le classement dans l'ordre

    if (scoreFile == NULL) {
        printf("\tAucun score n'a ete enregistre jusqu'a present.\n");
    } else {
        fscanf(scoreFile, "%d %s\n", &score, name);

        while (!feof(scoreFile)) {
            printf("\t%d\t%s\n", score, name);
            fscanf(scoreFile, "%d %s\n", &score, name);
        }

        fclose(scoreFile);
    }

    printf("\n");

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
