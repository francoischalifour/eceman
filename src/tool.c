#include "../lib/setup.h"
#include "../lib/game.h"
#include "../lib/tool.h"
#include <windows.h>
#include <assert.h>

/**
 * Créé un nouvel outil.
 * @return L'outil initialisé
 */
Tool* newTool(Position* caseTool, enum ToolType type, enum Direction direction) {
    Position* pos = malloc(sizeof(Position));
    Tool* tool = malloc(sizeof(Tool));

    assert(pos != NULL);
    assert(tool != NULL);

    pos->x = caseTool->x;
    pos->y = caseTool->y;

    tool->pos = pos;
    tool->type = type;
    tool->state = ACTIVE;
    tool->direction = direction;

    return tool;
}

/**
 * Détruit l'outil passé en paramètre.
 * Libère la mémoire de l'outil.
 * @param tool L'outil à détruire
 */
void destroyTool(Tool* tool) {
    free(tool->pos);
    free(tool);
}

/**
 * Dessine l'outil passé en paramètre sur le plateau de jeu.
 * @param board Le plateau sur lequel l'outil est ajouté
 * @param tool L'outil à ajouter
 */
static void drawTool(char board[ROWS][COLS], Tool* tool) {
    board[tool->pos->x][tool->pos->y] = MOWER_CHAR;
    goToXY(tool->pos->y, tool->pos->x);

    setColor(MOWER_CHAR_COLOR);
    putchar(convertCase(MOWER_CHAR));
    resetColor();
}

/**
 * Nettoie la case de l'ancienne position de l'outil.
 * @param board Le plateau de jeu
 * @param tool L'outil à nettoyer
 */
static void clearTool(char board[ROWS][COLS], Tool* tool) {
    board[tool->pos->x][tool->pos->y] = MELT_CHAR;
    goToXY(tool->pos->y, tool->pos->x);

    setColor(MELT_CHAR_COLOR);
    putchar(convertCase(MELT_CHAR));
    resetColor();
}

/**
 * Déplace l'outil sur le plateau de jeu.
 * @param game L'état du jeu
 * @param board La plateau de jeu
 * @param tool L'outil à déplacer
 * @param hero Le Eceman à vérifier pour la collision
 * @return L'outil avec sa nouvelle position
 */
static Tool* moveTool(GameState* game, char board[ROWS][COLS], Tool* tool, Eceman* hero) {
    switch (tool->direction) {
        case UP:
            if (board[tool->pos->x-2][tool->pos->y] == WALL_CHAR)
                tool->state = FINAL;

            tool->pos->x -= 1;
            break;

        case DOWN:
            if (board[tool->pos->x+2][tool->pos->y] == WALL_CHAR)
                tool->state = FINAL;

            tool->pos->x += 1;
            break;

        case LEFT:
            if (board[tool->pos->x][tool->pos->y-2] == WALL_CHAR)
                tool->state = FINAL;

            tool->pos->y -= 1;
            break;

        case RIGHT:
            if (board[tool->pos->x][tool->pos->y+2] == WALL_CHAR)
                tool->state = FINAL;

            tool->pos->y += 1;
            break;
    }

    tool->caseBelow = board[tool->pos->x][tool->pos->y];

    game->levelScore++;

    drawTool(board, tool);
    drawToolbar(game);

    return tool;
}

/**
 * Lance l'action liée à l'objet
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 * @param tool L'outil à lancer
 */
void runToolAction(GameState* game, char board[ROWS][COLS], Eceman* hero, enum ToolType toolType) {
    unsigned short i;
    Tool* tool = NULL;

    switch (toolType) {
        case MOWER:
            tool = newTool(getToolPosition(board, MOWER_CHAR), MOWER, RIGHT);

            i = 0;

            while (tool->state != FINAL) {
                clearTool(board, tool);
                moveTool(game, board, tool, hero);
                i++;
            }

            break;
        default:
            break;
    }
}
