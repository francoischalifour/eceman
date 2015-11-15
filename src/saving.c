/*
 * saving.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent la sauvegarde du jeu.
 *
 * Si le joueur fait un nouveau meilleur score, alors il est enregistré dans
 * le fichier SCORE_FILE défini dans le fichier game.h.
 * Ce score est enregistré seulement s'il n'y a pas encore 10 meilleurs
 * scores, ou s'il bat le minimum des meilleurs scores.
 *
 * Objectifs :
 *     -    Sauvegarder et nettoyer l'état du jeu
 *     -    Charger le classement
 *     -    Enregistrer le score dans le classement
 */

#include "../lib/setup.h"
#include <assert.h>
#include <dir.h>

/**
 * Sauvegarde la partie.
 * @param game L'état du jeu à sauvegarder (score, level, temps)
 */
void save(GameState* game) {
    FILE* saveFile = NULL;

    saveFile = fopen(SAVE_FILE, "w+");

    assert(saveFile != NULL);

    fprintf(saveFile, "%u\n%u\n%f", game->level, game->score, game->timePlayed);

    fclose(saveFile);
}

/**
 * Supprime le fichier de sauvegarde de partie.
 */
static void clearSaving() {
    remove(SAVE_FILE);
}

/**
 * Sauvegarde le score dans le fichier classement.
 * @param score Le score final du joueur
 */
void saveRanking(const int score) {
    FILE* scoreFile = NULL;
    char name[NAME_LENGTH];
    unsigned int nbScores, minHighScore;

    nbScores = getNbScores();
    minHighScore = getMinHighScore();

    if (nbScores < RANKING_MAX || score > minHighScore) {
        printf("\tEntrez votre nom : ");
        gets(name);

        scoreFile = fopen(SCORE_FILE, "a");
        assert(scoreFile != NULL);

        fprintf(scoreFile, "%d %s\n", score, name);

        printf("\n\tVotre score a bien ete enregistre.\n");

        fclose(scoreFile);
    } else {
        printf("\tDesole, vous n'avez battu aucun score.\n");
    }

    clearSaving();
}

/**
 * Charge le fichier correspondant à la dernière sauvegarde.
 * @return La dernière sauvegarde (NULL si aucune)
 */
FILE* loadSaving() {
    FILE* savingFile = NULL;

    // On ouvre le fichier s'il y a déjà une partie en cours.
    savingFile = fopen(SAVE_FILE, "r");

    // On créé le dossier de sauvegarde sinon
    if (savingFile == NULL)
        mkdir(SAVE_DIR);

    return savingFile;
}

/**
 * Ferme le fichier correspondant à la sauvegarde
 * passée en paramètre.
 * @param savingFile Le fichier à fermer
 */
void closeSaving(FILE* savingFile) {
    fclose(savingFile);
}
