#include "../lib/setup.h"
#include <string.h>
#include <dirent.h>

/**
 * Sauvegarde la partie.
 * @param level Le numéro du niveau à sauvegarder
 * @param score Le score à sauvegarder
 */
void save(const int level, const int score) {
    FILE* saveFile = NULL;

    saveFile = fopen("../data/saving/game.sav", "w+");
    fprintf(saveFile, "%d\n%d", level, score);

    fclose(saveFile);
}

/**
 * Sauvegarde du score pour le fichier classement
 * @param score score final du joueur
 */
void saveRanking(const int score) {
    FILE* scoreFile = NULL;
    char name[15];

    printf("Entrez votre prenom, puis validez avec ENTRER :\n");
    gets(name);

    scoreFile = fopen("../data/saving/scores.sav", "a");
    fprintf(scoreFile, "%d    %s\n", score, name);

    fclose(scoreFile);

}

/**
 * Nettoie le fichier de sauvegarde de partie.
 */
void clearSaving() {
    FILE* saveFile = NULL;

    saveFile = fopen("../data/saving/game.sav", "w");

    fclose(saveFile);
}

/**
 * Charge le fichier correspondant à la dernière sauvegarde.
 * @return La dernière sauvegarde (NULL si aucune)
 */
FILE* loadSaving() {
    FILE* saving = NULL;

    saving = fopen("../data/saving/game.sav", "r");

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
 * Récupère le nombre de niveaux.
 * Compte le nombre de fichiers
 * dans le répertoire des maps.
 * @return Le nombre de niveaux
 */
int getNbLevels() {
    unsigned int count = 0;
    DIR *dir;
    struct dirent *file;

    if ((dir = opendir("../data/map/")) != NULL) {
        while ((file = readdir(dir)) != NULL) {
            if (!strcmp(file->d_name, ".") || !strcmp(file->d_name, ".."))
                continue;

            count++;
        }

        closedir(dir);
    }

    return count;
}

/**
 * Récupère le niveau de la dernière partie.
 * @param saving La dernière sauvegarde
 * @return Le niveau de la dernière sauvegarde
 */
int getLevel(FILE* saving) {
    unsigned int level;

    fscanf(saving, "%d", &level);

    if (level < 0 || level > getNbLevels())
        level = 1;

    return level;
}

/**
 * Récupère le score de la dernière partie.
 * @param saving La dernière sauvegarde
 * @return Le score de la dernière sauvegarde
 */
int getScore(FILE* saving) {
    unsigned int score;

    fscanf(saving, "\n%d", &score);

    if (score < 0 || score > SCORE_MAX)
        score = 0;

    return score;
}
