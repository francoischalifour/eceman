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

    if (level < 1 || level > getNbLevels()) {
        level = 1;
    }

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
    goToXY(26, 1);
    printf("%c %s\n", OUTSIDE_CHAR, "Exterieur");

    goToXY(26, 2);
    printf("%c %s\n", WALL_CHAR, "Mur");

    goToXY(26, 3);
    printf("%c %s\n", THIN_CHAR, "Glace fine");

    goToXY(26, 4);
    printf("%c %s\n", THICK_CHAR, "Glace epaisse");

    goToXY(26, 5);
    printf("%c %s\n", MELT_CHAR, "Eau");

    goToXY(26, 6);
    printf("%c %s\n", LIGHTNESS_POTION_CHAR, "Potion de legerete");

    goToXY(26, 7);
    printf("%c %s\n", MOWER_CHAR, "Tondeuse");

    goToXY(26, 8);
    printf("%c %s\n", ENEMY_CHAR, "Ennemi");

    goToXY(26, 9);
    printf("%c %s\n", TUNNEL_CHAR, "Tunnel");

    goToXY(26, 10);
    printf("%c %s\n", TUNNEL_EXIT_CHAR, "Sortie du tunnel");

    goToXY(26, 11);
    printf("%c %s\n", SPAWN_CHAR, "Lieu d'apparition");

    goToXY(26, 12);
    printf("%c %s\n", DOOR_CHAR, "Porte de sortie");

    goToXY(26, 14);
    printf("%s %s\n", "(s)", "Enregistrer le niveau");

    goToXY(26, 15);
    printf("%s %s\n", "(q)", "Quitter l'editeur");

    goToXY(26, 16);
    printf("%s %s\n", "Backspace", "Effacer");
}

/**
 * Dessine la map créée par le joueur.
 * @param board Le plateau
 */
static void drawInitMap(char board[ROWS][COLS]) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            board[x][y] = OUTSIDE_CHAR;
            setColor(getCaseColor(board[x][y]));
            putchar(convertCase(board[x][y]));
            resetColor();
        }

        goToXY(0, x);
    }
}

/**
 * Enregistre le tableau de map dans un fichier.
 * @param board Le plateau fraîchement créé
 */
static void saveMap(char board[ROWS][COLS]) {
    unsigned int i, j;
    char filepath[18];
    char filename[18];
    FILE* mapFile = NULL;

    strcpy(filepath, MAP_DIR);
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
 * Vérifie si le plateau de jeu est jouable.
 * @param board Le plateau de jeu à vérifier
 * @return  -1 si pas de point d'apparition,
 *                    -2 si pas de porte de sortie
 *                    0 sinon
 */
static int checkBoard(char board[ROWS][COLS]) {
    unsigned int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (hasCase(board, SPAWN_CHAR) != 0)
                return -1;
            else if (hasCase(board, DOOR_CHAR) != 0)
                return -2;
        }
    }

    return 0;
}

/**
 * Créer une map dynamiquement.
 */
void createMap() {
    unsigned int posx, posy;
    unsigned char elem;
    char board[ROWS][COLS];
    int checkStatus;

    system("cls");

    posx = posy = 0;

    drawInitMap(board);
    drawLegend();

    while (1) {
        if (kbhit()) {
            // Nettoyer éventuellement la ligne des erreurs
            goToXY(1, 17);
            printf("                                                                                                                \n");

            elem = getch();

            switch (elem) {
                case UP_KEY:
                    goToXY(posx - 1, posy);
                    break;
                case DOWN_KEY:
                    goToXY(posx + 1, posy);
                    break;
                case LEFT_KEY:
                    goToXY(posx, posy - 1);
                    break;
                case RIGHT_KEY:
                    goToXY(posx, posy + 1);
                    break;
                case 'q':
                    return;
                    break;
                case 's':
                    checkStatus = checkBoard(board);

                    if (checkStatus != 0) {
                        goToXY(1, 17);
                        switch (checkStatus) {
                            case -1:
                                printf("Votre niveau de contient pas de point d'apparition.\n");
                                break;
                            case -2:
                                printf("Votre niveau de contient pas de porte de sortie.\n");
                                break;
                            default:
                                printf("Votre niveau contient des erreurs.\n");
                        }
                    } else {
                        saveMap(board);
                        return;
                    }
                    break;
                case OUTSIDE_CHAR:
                case WALL_CHAR:
                case THIN_CHAR:
                case THICK_CHAR:
                case MELT_CHAR:
                case LIGHTNESS_POTION_CHAR:
                case MOWER_CHAR:
                case ENEMY_CHAR:
                case TUNNEL_CHAR:
                case TUNNEL_EXIT_CHAR:
                case SPAWN_CHAR:
                case DOOR_CHAR:
                    if (posy >= ROWS - 1 || posx >= COLS)
                        continue;

                    board[posy][posx] = elem;
                    setColor(getCaseColor(elem));
                    goToXY(posx, posy);
                    putchar(convertCase(elem));
                    resetColor();

                    posx++;
                    break;
            }

            if (posx % COLS == 0) {
                posx = 0;
                posy++;
            }
        }
    }
}
