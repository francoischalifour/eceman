#include "../lib/setup.h"


/**
 * Sauvegarde la partie
 * @param level Numéro du niveau à sauvegarder
 * @param score Score à sauvegarder
 */
void save(int level, int score) {
    char filepath[23];
    FILE* save = NULL;

    sprintf(filepath, "../data/saving/game.sav");

    save = fopen(filepath, "w");

    fprintf(save, "%d\n%d", level, score);

    fclose(save);

}

/**
 * Charge le fichier correspondant à la dernière sauvegarde.
 * @return La dernière sauvegarde (NULL si aucune)
 */
FILE* loadSaving() {
    char filepath[23];
    FILE* saving = NULL;

    sprintf(filepath, "../data/saving/game.sav");

    saving = fopen(filepath, "r");

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

/**
 * Récupère le niveau de la dernière partie.
 * @param saving La dernière sauvegarde
 * @return Le niveau de la dernière sauvegarde
 */
int getLevel(FILE* saving) {
    int level;

    fscanf(saving, "%d", &level);

    return level;
}

/**
 * Récupère le score de la dernière partie.
 * @param saving La dernière sauvegarde
 * @return Le score de la dernière sauvegarde
 */
int getScore(FILE* saving) {
    int score;

    fscanf(saving, "\n%d", &score);

    return score;
}
