#include "../lib/setup.h"
#include <assert.h>

/**
 * Charge le fichier correspondant à la map du niveau
 * passé en paramètre.
 * @param level Le niveau correspondant à la map
 * @return La map
 */
FILE* loadMap(short level) {
    char filepath[18];
    FILE* map = NULL;

    if (level < 1 || level > getNbLevels()) {
        level = 1;
    }

    sprintf(filepath, "../data/map/%d.map", level);

    map = fopen(filepath, "r");

    assert(map);

    return map;
}

/**
 * Ferme le fichier correspondant à la map du niveau
 * passé en paramètre.
 * @param map Le fichier map à fermer
 */
void closeMap(FILE* map) {
    fclose(map);
}
