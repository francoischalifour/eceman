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
#include <time.h>
#include <sys/stat.h>
#include <conio.h>

/**
 * Affiche le titre du jeu.
 */
static void displayTitle() {
    system("cls");

    setColor(11);
    printf("\n\t ______   ______   ______   __    __   ______   __   __\n\
\t/\\  ___\\ /\\  ___\\ /\\  ___\\ /\\ \"-./  \\ /\\  __ \\ /\\ \"-.\\ \\  \n\
\t\\ \\  __\\ \\ \\ \\____\\ \\  __\\ \\ \\ \\-./\\ \\\\ \\  __ \\\\ \\ \\-.  \\ \n\
\t \\ \\_____\\\\ \\_____\\\\ \\_____\\\\ \\_\\ \\ \\_\\\\ \\_\\ \\_\\\\ \\_\\\\\"\\_\\\n\
\t  \\/_____/ \\/_____/ \\/_____/ \\/_/  \\/_/ \\/_/\\/_/ \\/_/ \\/_/\n\n");
    resetColor();
}

/**
 * Affiche le sous-titre passé en paramètre.
 * @param subtitle Le sous-titre
 */
static void displaySubtitle(char* subtitle) {
    setColor(59);
    printf("\t\t%s \n\n", subtitle);
    resetColor();
}

/**
 * Affiche le message passé en paramètre
 * en dessous du plateau de jeu.
 * @param message Le message à afficher
 */
void displayMessage(char* message) {
    unsigned int i, j;
    unsigned countLines;

    countLines = 2;

    goToXY(0, 17);

    setColor(RED_COLOR);

    for (i = 0; message[i] != '\0'; i++) {
        putchar(message[i]);

        if (i % (COLS + 2) == 0 && i != 0) {
            putchar('\n');
            countLines++;
        }
    }

    putchar('\n');

    setColor(GRAY_COLOR);

    printf("ESPACE pour continuer\n");

    resetColor();

    while (getch() != ' ');

    goToXY(0, 17);

    for (i = 0; i < countLines; i++) {
        for (j = 0; j < COLS + 2; j++) {
            putchar(' ');
        }

        putchar('\n');
    }
}

/**
 * Affiche le menu.
 */
void displayMenu() {
    struct stat attr;
    FILE* saving = NULL;

    displayTitle();

    displaySubtitle("Lancer une partie");

    goToXY(10, 10);
    printf("(1) Commencer une nouvelle partie");

    if ((saving = loadSaving())) {
        stat(SAVE_FILE, &attr);

        goToXY(10, 12);
        printf("(2) Continuer la partie precedente");

        setColor(GRAY_COLOR);
        goToXY(20, 14);
        printf("Niveau %2d", getLastLevel(saving));
        goToXY(20, 15);
        printf("Score %3d", getLastScore(saving));
        goToXY(20, 16);
        printf("%s", ctime(&attr.st_mtime));
        resetColor();

        closeSaving(saving);
    }

    setColor(LINK_COLOR);

    goToXY(2, 20);
    printf("(p) Partie rapide");
    goToXY(2, 21);
    printf("(e) Editeur");

    goToXY(28, 20);
    printf("(c) Classement");
    goToXY(28, 21);
    printf("(r) Regles");

    goToXY(50, 20);
    printf("(a) A propos");
    goToXY(50, 21);
    printf("(q) Quitter");

    resetColor();
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

    displaySubtitle("Liste des niveaux");

    for (i = 0; i < getNbLevels(); i++) {
        printf("\tNiveau %d\n", i + 1);
    }

    printf("\n\t(r) Retour\n");

    // Position initiale de la flèche.
    choixPos = 9;
    level = 1;

    goToXY(5, choixPos);
    printf("->");

    do {
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
    } while (key != 'r');
}

/**
 * Affiche l'éditeur de niveaux.
 */
void displayEditor() {
    char key;

    displayTitle();

    displaySubtitle("Editeur de niveau");

    printf("\t(1) Modifier un niveau existant\n");
    printf("\t(2) Creer un nouveau niveau\n\n");

    printf("\t(r) Retour\n");

    do {
        key = getch();

        switch (key) {
            case '1':
                displayLevels(1);
                break;
            case '2':
                editMap(0);
                break;
        }
    } while (key != 'r');
}

/**
 * Affiche les règles du jeu.
 */
void displayRules() {
    FILE* rules = NULL;
    char c;

    rules = fopen(RULES_FILE, "r");

    displayTitle();

    displaySubtitle("Regles");

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
void displayGameOver(const int scoreFinal, const float timePlayed) {
    displayTitle();

    displaySubtitle("Game over");

    setColor(GRAY_COLOR);
    printf("\tScore %4d\n", scoreFinal);
    printf("\tTemps %4.0f\n\n", timePlayed);
    resetColor();
}

/**
 * Affiche le classement des scores du fichier des scores.
 */
void displayRanking() {
    FILE* scoreFile = NULL;

    scoreFile = fopen(SCORE_FILE, "r");

    displayTitle();

    displaySubtitle("Classement des scores");

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

    about = fopen(ABOUT_FILE, "r");

    displayTitle();

    displaySubtitle("A propos");

    while ((c = fgetc(about)) != EOF) {
        putchar(c);
    }

    fclose(about);

    printf("\n");

    goBack();
}
