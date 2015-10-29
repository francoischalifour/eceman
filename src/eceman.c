#include "../lib/setup.h"
#include "../lib/eceman.h"
#include <assert.h>
#include <windows.h>

/**
 * Créé un nouveau Eceman.
 * Initialise son état et sa position.
 * @return Le Eceman initialisé
 */
Eceman* newEceman() {
    Position* pos = malloc(sizeof(Position));
    Eceman* hero = malloc(sizeof(Eceman));

    pos->x = 0;
    pos->y = 0;

    hero->pos = pos;
    hero->state = NORMAL;
    hero->caseBelow = SPAWN_CHAR;

    return hero;
}

/**
 * Détruit le Eceman passé en paramètre.
 * Libère la mémoire du Eceman.
 * @param hero Le Eceman à détruire
 */
void destroyEceman(Eceman* hero) {
    free(hero->pos);
    free(hero);
}

/**
 * Place le héro au nom de la case passé en paramètre.
 * @param board Le plateau du niveau
 * @param hero Le Eceman à placer
 * @return 0 si la case a été trouvée, -1 sinon
 */
int goToCase(char board[ROWS][COLS], Eceman* hero, const char elem) {
    unsigned short x, y;

    for (x = 0; x < ROWS; x++) {
        for (y = 0; y < COLS; y++) {
            if (board[x][y] == elem) {
                hero->pos->x = x;
                hero->pos->y = y;
                hero->caseBelow = board[x][y];

                return 0;
            }
        }
    }

    return -1;
}

/**
 * Vérifie si le Eceman est entouré de murs ou d'eau.
 * @param board Le plateau sur lequel le joueur joue
 * @param hero Le Eceman à tester
 * @return 1 si le Eceman est encerclé, 0 sinon
 */
static int isSurrounded(char board[ROWS][COLS], Eceman* hero) {
    if (board[hero->pos->x][hero->pos->y] == DOOR_CHAR || board[hero->pos->x][hero->pos->y] == TUNNEL_CHAR)
        return 0;

    if ((board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR)
        && (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR)
        && (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR)
        && (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR))
        return 1;

    return 0;
}

/**
 * Dessine le Eceman sur le plateau de jeu.
 * @param board Le plateau sur lequel le Eceman est ajouté
 * @param hero Le Eceman à ajouter
 */
void drawEceman(char board[ROWS][COLS], Eceman* hero) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    board[hero->pos->x][hero->pos->y] = HERO_CHAR;
    goToXY(hero->pos->y, hero->pos->x);

    SetConsoleTextAttribute(hConsole, HERO_CHAR_COLOR);
    putchar(HERO_CHAR);
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

/**
 * Déplace le Eceman sur le plateau de jeu.
 * Cette fonction augmente le score si le héro a avancé,
 * lance l'action de la case actuelle,
 * met à jour la toolbar avec le score,
 * recharge le niveau si le héro est encerclé.
 * @param key La touche appuyée
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman à déplacer
 * @return Le Eceman avec sa nouvelle position
 */
Eceman* moveEceman(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero) {
    unsigned short prevPosX = hero->pos->x;
    unsigned short prevPosY = hero->pos->y;

    switch (key) {
        case UP_KEY:
            if (board[hero->pos->x-1][hero->pos->y] == WALL_CHAR || board[hero->pos->x-1][hero->pos->y] == MELT_CHAR)
                return NULL;

            hero->pos->x -= 1;
            break;

        case DOWN_KEY:
            if (board[hero->pos->x+1][hero->pos->y] == WALL_CHAR || board[hero->pos->x+1][hero->pos->y] == MELT_CHAR)
                return NULL;

            hero->pos->x += 1;
            break;

        case LEFT_KEY:
            if (board[hero->pos->x][hero->pos->y-1] == WALL_CHAR || board[hero->pos->x][hero->pos->y-1] == MELT_CHAR)
                return NULL;

            hero->pos->y -= 1;
            break;

        case RIGHT_KEY:
            if (board[hero->pos->x][hero->pos->y+1] == WALL_CHAR || board[hero->pos->x][hero->pos->y+1] == MELT_CHAR)
                return NULL;

            hero->pos->y += 1;
            break;
    }

    hero->caseBelow = board[hero->pos->x][hero->pos->y];

    if (prevPosX != hero->pos->x || prevPosY != hero->pos->y) {
        runCaseAction(game, board, hero);
        drawToolbar(game);
    }

    if (isSurrounded(board, hero))
        reloadLevel(game, board, hero);

    return hero;
}
