#include "../lib/setup.h"
#include <string.h>

/**
 * Sauvegarde la partie.
 * @param game L'état du jeu à sauvegarder (score, level, temps)
 */
void save(GameState* game) {
    FILE* saveFile = NULL;

    saveFile = fopen(SAVE_FILE, "w+");

    fprintf(saveFile, "%d\n%d\n%f", game->level, game->score, game->timeTotal);

    fclose(saveFile);
}

/**
 * Sauvegarde le score dans le fichier classement.
 * @param score Le score final du joueur
 */
void saveRanking(const int score) {
    FILE* scoreFile = NULL;
    char name[NAME_LENGTH];
    //unsigned int minHighScore;

    printf("\tEntrez votre nom : ");
    gets(name);

    // TODO : enregistrer le nom seulement si mérité.
/*    // Si le joueur a battu un meilleur score, et qu'il y en a moins de 10
    if (getNbScores(scoreFile) < RANKING_MAX) {
        printf("\tEntrez votre nom : ");
        gets(name);
    } else {
        minHighScore = getMinHighScore(scoreFile);

        // Si le joueur a battu le moins bon des meilleurs scores.
        if (score > minHighScore) {
            printf("\tEntrez votre nom : ");
            gets(name);
            //deleteScore(scoreFile, minHighScore);
        }
    }*/

    scoreFile = fopen(SCORE_FILE, "a");

    fprintf(scoreFile, "%d %s\n", score, name);

    fclose(scoreFile);
}

/**
 * Nettoie le fichier de sauvegarde de partie.
 */
void clearSaving() {
    remove(SAVE_FILE);
}

/**
 * Charge le fichier correspondant à la dernière sauvegarde.
 * @return La dernière sauvegarde (NULL si aucune)
 */
FILE* loadSaving() {
    FILE* saving = NULL;

    saving = fopen(SAVE_FILE, "r");

    return saving;
}

/**
 * Ferme le fichier correspondant à la sauvegarde
 * passée en paramètre.
 * @param saving Le fichier à fermer
 */
void closeSaving(FILE* saving) {
    fclose(saving);
}
