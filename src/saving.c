#include "../lib/setup.h"
#include <ctype.h>

/**
 * Sauvegarde la partie.
 * @param level Le numéro du niveau à sauvegarder
 * @param score Le score à sauvegarder
 */
void save(const int level, const int score) {
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

    if (!isdigit(level))
        level = 1;

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

    if (!isdigit(score))
        score = 0;

    return score;
}
