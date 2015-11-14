/*
 * score.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent le score du jeu.
 *
 * Les meilleurs scores sont stockés dans le fichier défini par SCORE_FILE dans
 * le fichier game.h. Ces scores apparaissent par ordre non trié. C'est dans
 * l'affichae des meilleurs scores que l'on triera les scores.
 *
 * Objectifs :
 *     -    Récupérer le score de la partie précédente
 *     -    Récupérer le nombre de scores dans le classement
 *     -    Supprimer un score
 *     -    Trier les meilleurs scores
 *     -    Afficher le classement des meilleurs scores
 */

#include "../lib/setup.h"
#include <string.h>
#include <assert.h>

/**
 * Récupère le score de la dernière partie.
 * @param savingFile La dernière sauvegarde
 * @return Le score de la dernière sauvegarde (0 si fichier non trouvé)
 */
int getLastScore(FILE* savingFile) {
    unsigned int score;

    if (savingFile == NULL)
        return 0;

    fscanf(savingFile, "%u\n", &score);

    if (score < 0 || score > SCORE_MAX)
        score = 0;

    return score;
}

/**
 * Récupère le temps enregistré.
 * @param savingFile Le fichier de sauvegarde
 * @return Le temps enregistré (0 si fichier non trouvé)
 */
float getLastTime(FILE* savingFile) {
    float timePlayed;

    if (savingFile == NULL)
        return 0;

    fscanf(savingFile, "%f\n", &timePlayed);

    return timePlayed;
}

/**
 * Récupère le temps de fin de dernière partie.
 * @param savingFile Le fichier de sauvegarde
 * @return Le temps à la dernière partie enregistré (0 si fichier non trouvé)
 */
float getLastTimeStop(FILE* savingFile) {
    float timeStop;

    if (savingFile == NULL)
        return 0;

    fscanf(savingFile, "%f\n", &timeStop);

    return timeStop;
}

/**
 * Récupère le nombre de scores enregistrés.
 * @return Le nombre de scores enregistrés (0 si fichier non trouvé)
 */
int getNbScores() {
    unsigned short nbLines = 0;
    unsigned char c;
    FILE* scoreFile = NULL;

    scoreFile = fopen(SCORE_FILE, "r");

    if (scoreFile == 0)
        return 0;

    while (!feof(scoreFile)) {
        c = fgetc(scoreFile);

        if (c == '\n')
            nbLines++;
    }

    fclose(scoreFile);

    return nbLines;
}

/**
 * Récupère le minimum des scores enregistrés.
 * Fonction appelée seulement si au moins 10 scores enregistrés.
 * @return Le score minimum enregistré (-1 si fichier non trouvé)
 */
int getMinHighScore() {
    unsigned int score, minScore;
    char name[NAME_LENGTH];
    FILE* scoreFile = NULL;

    scoreFile = fopen(SCORE_FILE, "r");

    if (scoreFile == NULL)
        return -1;

    minScore = SCORE_MAX;

    while (!feof(scoreFile)) {
        fscanf(scoreFile, "%u %s", &score, name);

        if (score < minScore)
            minScore = score;
    }

    fclose(scoreFile);

    return minScore;
}

/**
 * Récupère la ligne du score enregistré.
 * Fonction appelée seulement si au moins 10 scores enregistrés.
 * @param scoreFile Le fichier contenant les scores
 * @param score Le score dont on veut la ligne
 * @return La ligne du score souhaité (-1 si non trouvé)
 */
int getScoreLine(FILE* scoreFile, const int score) {
    unsigned int currentScore;
    char name[NAME_LENGTH];
    int countLines;
    char c;

    assert(scoreFile != NULL);

    countLines = 1;

    while ((c = fgetc(scoreFile)) != EOF) {
        fscanf(scoreFile, "%u %s", &currentScore, name);

        countLines++;

        if (currentScore == score)
            return countLines;
    }

    return -1;
}

/**
 * Trie le tableau des scores.
 * @param arrayScores Le tableau des scores
 * @param arrayNames Le tableau des noms
 */
static void sortScores(const int nbScores, int* arrayScores, char** arrayNames) {
    unsigned short i, j;
    int tmpScore;
    char tmpName[NAME_LENGTH];

    for (i = nbScores - 1; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            if (arrayScores[j] <= arrayScores[j+1]) {
                tmpScore = arrayScores[j];
                arrayScores[j] = arrayScores[j+1];
                arrayScores[j+1] = tmpScore;

                strcpy(tmpName, arrayNames[j]);
                strcpy(arrayNames[j], arrayNames[j+1]);
                strcpy(arrayNames[j+1], tmpName);
            }
        }
    }
}

/**
 * Récupère et affiche le classement des meilleurs scores triés.
 * @param scoreFile Le fichier contenant les scores
 */
void getRanking(FILE* scoreFile) {
    unsigned int i, count;
    unsigned int score;
    char name[NAME_LENGTH];
    int* arrayScores;
    char** arrayNames;

    if (scoreFile == NULL) {
        printf("\tAucun score n'a ete enregistre jusqu'a present.\n");
        return;
    }

    count = getNbScores(scoreFile);

    arrayScores = malloc(count * sizeof(int));
    assert(arrayScores != NULL);

    arrayNames = malloc(count * sizeof(char*));
    assert(arrayNames != NULL);

    for (i = 0; i < count; i++) {
        fscanf(scoreFile, "%u %s\n", &score, name);
        arrayScores[i] = score;
        arrayNames[i] = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(arrayNames[i], name);
    }

    sortScores(count, arrayScores, arrayNames);

    if (count > RANKING_MAX)
        count = RANKING_MAX;

    for (i = 0; i < count; i++) {
        printf("\t%d\t%s\n", arrayScores[i], arrayNames[i]);
    }

    free(arrayScores);
    free(arrayNames);
}
