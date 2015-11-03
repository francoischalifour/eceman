#include "../lib/setup.h"
#include <string.h>
#include <dirent.h>

/**
 * Récupère le niveau de la dernière partie.
 * @param saving La dernière sauvegarde
 * @return Le niveau de la dernière sauvegarde
 */
int getLastLevel(FILE* saving) {
    unsigned int level;

    fscanf(saving, "%d", &level);

    if (level < 0 || level > getNbLevels())
        level = 1;

    return level;
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