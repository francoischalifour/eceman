#include "../lib/setup.h"
#include <string.h>

/**
 * Récupère le score de la dernière partie.
 * @param saving La dernière sauvegarde
 * @return Le score de la dernière sauvegarde
 */
int getLastScore(FILE* saving) {
    unsigned int score;

    fscanf(saving, "\n%d", &score);

    if (score < 0 || score > SCORE_MAX)
        score = 0;

    return score;
}

/**
 * Récupère le nombre de scores enregistrés.
 * @param scoreFile Le fichier contenant les scores
 * @return Le nombre de scores enregistrés
 */
int getNbScores(FILE* scoreFile) {
    unsigned short nbLines = 0;
    unsigned char c;

    while (!feof(scoreFile)) {
        c = fgetc(scoreFile);

        if (c == '\n')
            nbLines++;
    }

    rewind(scoreFile);

    return nbLines;
}

/**
 * Supprimer la ligne correspondant au score passé en paramètres.
 * @param scoreFile Le fichier contenant les scores
 * @param score Le score à supprimer
 * @return Le score supprimé (-1 sinon)
 */
int deleteScore(FILE* scoreFile, const int score) {
    unsigned int currentScore;
    char name[NAME_LENGTH];

    if (scoreFile == NULL)
        return -1;

    while (!feof(scoreFile)) {
        fscanf(scoreFile, "%d %s\n", &currentScore, name);

        if (currentScore == score) {
            break;
            // TODO : supprimer la ligne
        }
    }

    return score;
}

/**
 * Récupère le minimum des meilleurs scores.
 * @param scoreFile Le fichier contenant les scores
 * @return Le meilleur score le plus faible (-1 si fichier non trouvé)
 */
int getMinHighScore(FILE* scoreFile) {
    unsigned int score, minScore;
    char name[NAME_LENGTH];

    if (scoreFile == NULL)
        return -1;

    minScore = SCORE_MAX;

    while (!feof(scoreFile)) {
        fscanf(scoreFile, "%d %s\n", &score, name);

        if (score < minScore)
            minScore = score;
    }

    // TODO : retourner la ligne pour la supprimer ensuite dans deleteScore()

    return minScore;
}

/**
 * Trie le tableau des scores.
 * @param arrayScores Le tableau des scores
 * @param arrayNames Le tableau des noms
 */
static void sortScores(const int nbScores, int arrayScores[nbScores], char arrayNames[nbScores][NAME_LENGTH + 1]) {
    unsigned short i, j;
    int tmpScore;
    char tmpName[NAME_LENGTH];

    for (i = nbScores - 1; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            if (arrayScores[j] < arrayScores[j+1]) {
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
    int arrayScores[RANKING_MAX];
    char arrayNames[RANKING_MAX][NAME_LENGTH + 1];

    if (scoreFile == NULL) {
        printf("\tAucun score n'a ete enregistre jusqu'a present.\n");
        return;
    }

    count = getNbScores(scoreFile);

    for (i = 0; i < count; i++) {
        fscanf(scoreFile, "%d %s\n", &score, name);
        arrayScores[i] = score;
        strcpy(arrayNames[i], name);
    }

    fclose(scoreFile);

    sortScores(count, arrayScores, arrayNames);

    for (i = 0; i < count; i++) {
        printf("\t%d\t%s\n", arrayScores[i], arrayNames[i]);
    }
}
