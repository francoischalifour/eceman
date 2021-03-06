/*
 * map.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent les maps du jeu.
 *
 * Le chemin des maps est stocké dans la constante MAP_DIR du fichier game.h.
 * Il existe un certain nombre de maps existantes, mais l'utilisateur peut les
 * modifier ou en créer de nouvelles via l'éditeur de niveaux.
 *
 * Objectifs :
 *     -    Charger et fermer une map existante
 *     -    Dessiner la légende
 *     -    Initialiser une map nouvelle map
 *     -    Dessiner une map (par l'éditeur)
 *     -    Editer une map existante (par l'éditeur)
 *     -    Sauvegarder une map (par l'éditeur)
 *     -    Vérifier si le plateau créé est jouable
 */

#include "../lib/setup.h"
#include <string.h>
#include <conio.h>
#include <assert.h>

/**
 * Charge le fichier correspondant à la map du niveau
 * passé en paramètre.
 * @param level Le niveau correspondant à la map
 * @return La map
 */
FILE* loadMap(short level) {
    char filepath[18];
    char filedir[18];
    FILE* map = NULL;

    if (level < 1 || level > getNbLevels())
        level = 1;

    strcpy(filedir, MAP_DIR);
    sprintf(filepath, "%d.map", level);
    strcat(filedir, filepath);

    strcpy(filepath, filedir);

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

/**
 * Dessine la légende des maps.
 */
static void drawLegend() {
    setColor(GRAY_COLOR);

    goToXY(INFOPANEL_X, 1);
    printf("%c %s\n", OUTSIDE_CHAR, "Exterieur");

    goToXY(INFOPANEL_X, 2);
    printf("%c %s\n", WALL_CHAR, "Mur");

    goToXY(INFOPANEL_X, 3);
    printf("%c %s\n", THIN_CHAR, "Glace fine");

    goToXY(INFOPANEL_X, 4);
    printf("%c %s\n", THICK_CHAR, "Glace epaisse");

    goToXY(INFOPANEL_X, 5);
    printf("%c %s\n", SLIP_CHAR, "Glace glissante");

    goToXY(INFOPANEL_X, 6);
    printf("%c %s\n", MELT_CHAR, "Eau");

    goToXY(INFOPANEL_X, 7);
    printf("%c %s\n", LIGHTNESS_POTION_CHAR, "Potion de legerete");

    goToXY(INFOPANEL_X, 8);
    printf("%c %s\n", SCORE_BONUS_CHAR, "Bonus de score");

    goToXY(INFOPANEL_X, 9);
    printf("%c %s\n", MOWER_CHAR, "Tondeuse");

    goToXY(INFOPANEL_X, 10);
    printf("%c %s\n", ENEMY_CHAR, "Ennemi");

    goToXY(INFOPANEL_X, 11);
    printf("%c %s\n", TUNNEL_CHAR, "Tunnel");

    goToXY(INFOPANEL_X, 12);
    printf("%c %s\n", TUNNEL_EXIT_CHAR, "Sortie du tunnel");

    goToXY(INFOPANEL_X, 13);
    printf("%c %s\n", HOLE_CHAR, "Trou");

    goToXY(INFOPANEL_X, 14);
    printf("%c %s\n", SPAWN_CHAR, "Lieu d'apparition");

    goToXY(INFOPANEL_X, 15);
    printf("%c %s\n", DOOR_CHAR, "Porte de sortie");

    resetColor();

    goToXY(INFOPANEL_X, 17);
    printf("%s %s\n", "(s)", "Enregistrer le niveau");

    goToXY(INFOPANEL_X, 18);
    printf("%s %s\n", "(q)", "Quitter l'editeur");
}

/**
 * Initialise la map.
 * @param board Le plateau
 */
static void initMap(FILE* map, char board[ROWS][COLS]) {
    unsigned short x, y;

    if (!map) {
        for (x = 0; x < ROWS; x++) {
            for (y = 0; y <= COLS; y++) {
                board[x][y] = OUTSIDE_CHAR;
            }
        }
    } else {
        for (x = 0; x < ROWS; x++) {
            for (y = 0; y <= COLS; y++) {
                board[x][y] = fgetc(map);
            }
        }
    }
}

/**
 * Dessine la map passée en paramètre.
 * @param board Le plateau
 */
static void drawMap(char board[ROWS][COLS]) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            setColor(getCaseColor(board[x][y]));
            putchar(convertCase(board[x][y]));
            resetColor();
        }

        printf("\n");
    }
}

/**
 * Enregistre le tableau de map dans un fichier.
 * @param board Le plateau fraîchement créé
 * @param level Le niveau de la map (0 pour nouveau)
 */
static void saveMap(char board[ROWS][COLS], const int level) {
    unsigned int i, j;
    char filepath[18];
    char filename[18];
    FILE* mapFile = NULL;

    strcpy(filepath, MAP_DIR);

    if (level != 0)
        sprintf(filename, "%d.map", level);
    else
        sprintf(filename, "%d.map", getNbLevels() + 1);

    strcat(filepath, filename);

    mapFile = fopen(filepath, "w");

    assert(mapFile != NULL);

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            fprintf(mapFile, "%c", board[i][j]);
        }

        fprintf(mapFile, "\n");
    }

    fclose(mapFile);
}

/**
 * Vérifie si le plateau contient la case passée en paramètre.
 * @param board Le plateau de jeu à vérifier
 * @return 0 si oui, -1 si non
 */
static int hasCase(char board[ROWS][COLS], const char elem) {
    unsigned int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == elem)
                return 0;
        }
    }

    return -1;
}

/**
 * Compte le nombre d'entités sur le plateau.
 * @param board Le plateau de jeu à vérifier
 * @return Le nombre d'entités
 */
static int countEntities(char board[ROWS][COLS]) {
    unsigned int i, j;
    unsigned nbEntities;

    nbEntities = 0;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == MOWER_CHAR || board[i][j] == ENEMY_CHAR)
                nbEntities++;
        }
    }

    return nbEntities;
}

/**
 * Vérifie si le plateau de jeu est jouable.
 * @param board Le plateau de jeu à vérifier
 * @return  -1 si pas de point d'apparition,
 *                    -2 si pas de porte de sortie
 *                    -3 s'il y a un tunnel sans sortie
 *                    -4 s'il y a trop d'entités
 *                    0 sinon
 */
static int checkBoard(char board[ROWS][COLS]) {
    if (hasCase(board, SPAWN_CHAR) != 0)
        return -1;
    else if (hasCase(board, DOOR_CHAR) != 0)
        return -2;
    else if (hasCase(board, TUNNEL_CHAR) == 0 && hasCase(board, TUNNEL_EXIT_CHAR) != 0)
        return -3;
    else if (countEntities(board) >= ENTITY_MAX)
        return -4;

    return 0;
}

/**
 * Edite une map dynamiquement.
 * @param level Le niveau à modifier (0 si nouveau niveau)
 */
void editMap(const int level) {
    unsigned int posx, posy;
    unsigned char elem;
    FILE* map = NULL;
    char board[ROWS][COLS];
    int checkStatus;

    system("cls");

    if (level != 0) {
        map = loadMap(level);
        initMap(map, board);
    } else {
        initMap(NULL, board);
    }

    drawMap(board);
    drawLegend();

    posx = posy = 0;

    goToXY(posx, posy);

    while (1) {
        if (kbhit()) {
            elem = getch();

            switch (elem) {
                case UP_KEY:
                    if (posy <= 0)
                        continue;
                    posy--;
                    break;
                case DOWN_KEY:
                    if (posy >= ROWS - 1)
                        continue;
                    posy++;
                    break;
                case LEFT_KEY:
                    if (posx <= 0) {
                        posy--;
                        posx = COLS - 1;
                    } else {
                        posx--;
                    }
                    break;
                case RIGHT_KEY:
                    if (posx >= COLS -1) {
                        if (posy >= ROWS - 1)
                            continue;
                        posy++;
                        posx = 0;
                    } else {
                        posx++;
                    }
                    break;
                case 'q':
                    return;
                    break;
                case 's':
                    checkStatus = checkBoard(board);

                    if (checkStatus != 0) {
                        goToXY(1, 19);
                        switch (checkStatus) {
                            case -1:
                                displayMessage("Le niveau de contient pas de point d'apparition.");
                                break;
                            case -2:
                                displayMessage("Le niveau de contient pas de porte de sortie.");
                                break;
                            case -3:
                                displayMessage("Le tunnel n'est pas lie a une sortie.");
                                break;
                            case -4:
                                displayMessage("Le niveau contient trop d'obstacles.");
                                break;
                            default:
                                displayMessage("Le niveau contient des erreurs.");
                        }
                    } else {
                        saveMap(board, level);
                        return;
                    }
                    break;
                case OUTSIDE_CHAR:
                case WALL_CHAR:
                case THIN_CHAR:
                case THICK_CHAR:
                case SLIP_CHAR:
                case MELT_CHAR:
                case LIGHTNESS_POTION_CHAR:
                case SCORE_BONUS_CHAR:
                case MOWER_CHAR:
                case ENEMY_CHAR:
                case TUNNEL_CHAR:
                case TUNNEL_EXIT_CHAR:
                case HOLE_CHAR:
                case SPAWN_CHAR:
                case DOOR_CHAR:
                    if (posy >= ROWS || posx >= COLS)
                        continue;

                    board[posy][posx] = elem;
                    setColor(getCaseColor(elem));
                    goToXY(posx, posy);
                    putchar(convertCase(elem));
                    resetColor();

                    posx++;

                    if (posx != 0 && posx % COLS == 0) {
                        posx = 0;
                        posy++;
                    }

                    break;
            }

            goToXY(posx, posy);
        }
    }
}
