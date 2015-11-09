#include "../lib/setup.h"
#include "../lib/game.h"
#include "../lib/entity.h"
#include <windows.h>
#include <assert.h>

/**
 * Créé une nouvelle entité
 * @param x L'abscisse
 * @param y L'ordonnée
 * @param direction La direction
 * @param symbol Le symbol sur la map
 * @param symbolColor La couleur du symbol
 * @param nextSymbol Le symbol après passage
 * @param nextSymbolColor La couleur du symbol après passage
 * @param nextCaseStrategy Le comportement de collision avec la case suivante
 * @param collidePropertyStrategy La condition de collision
 * @param collideStrategy L'action après collision
 * @param finalActionStrategy L'action après le déplacement
 * @return L'entité initialisée
 */
static Entity* createEntity(unsigned int x, unsigned int y, enum Direction direction, const char symbol, const char symbolColor, const char nextSymbol, const char nextSymbolColor, NextCaseStrategy nextCaseStrategy, CollidePropertyStrategy collidePropertyStrategy, CollideStrategy collideStrategy, FinalActionStrategy finalActionStrategy) {
    Position* pos = malloc(sizeof(Position));
    Entity* entity = malloc(sizeof(Entity));

    assert(pos != NULL);
    assert(entity != NULL);

    pos->x = x;
    pos->y = y;

    entity->pos = pos;
    entity->state = ACTIVE;
    entity->direction = direction;
    entity->caseBelow = THIN_CHAR;
    entity->symbol = symbol;
    entity->symbolColor = symbolColor;
    entity->nextSymbol = nextSymbol;
    entity->nextSymbolColor = nextSymbolColor;

    entity->nextCaseStrategy = nextCaseStrategy;
    entity->collidePropertyStrategy = collidePropertyStrategy;
    entity->collideStrategy = collideStrategy;
    entity->finalActionStrategy = finalActionStrategy;

    return entity;
}

/**
 * Détruit l'entité passée en paramètre.
 * Libère la mémoire de l'entité.
 * @param entity L'entité à détruire
 */
void destroyEntity(Entity* entity) {
    free(entity->pos);
    free(entity);
}

/**
 * Crée un nouvel ennemi.
 * @param x L'abscisse de l'ennemi
 * @param y L'ordonnée de l'ennemi
 * @param direction La direction de l'ennemi
 * @return Un nouvel ennemi
 */
Entity* createEnemy(unsigned int x, unsigned int y, enum Direction direction) {
    return createEntity(x, y, direction, ENEMY_CHAR, ENEMY_CHAR_COLOR, THIN_CHAR, THIN_CHAR_COLOR, enemyNextCaseStrategy, enemyCollidePropertyStrategy, enemyCollideStrategy, enemyFinalActionStrategy);
}

/**
 * Crée une nouvelle tondeuse.
 * @param x L'abscisse de la tondeuse
 * @param y L'abscisse de la tondeuse
 * @param direction La direction de la tondeuse
 * @return Une nouvelle tondeuse
 */
Entity* createMower(unsigned int x, unsigned int y, enum Direction direction) {
    return createEntity(x, y, direction, MOWER_CHAR, MOWER_CHAR_COLOR, MELT_CHAR, MELT_CHAR_COLOR, mowerNextCaseStrategy, mowerCollidePropertyStrategy, mowerCollideStrategy, mowerFinalActionStrategy);
}

/**
 * Renvoie la case suivante à percuter en tant qu'ennemi.
 * @param pos La position de l'ennemi
 * @param board Le plateau de jeu
 * @return Le case à percuter
 */
char enemyNextCaseStrategy(Position* pos, enum Direction direction, char board[ROWS][COLS]) {
    switch (direction) {
        case UP:
            return (board[pos->x-1][pos->y]);
            break;
        case DOWN:
            return (board[pos->x+1][pos->y]);
            break;
        case LEFT:
            return (board[pos->x][pos->y-1]);
            break;
        case RIGHT:
            return (board[pos->x][pos->y+1]);
            break;
        default:
            return WALL_CHAR;
    }
}

/**
 * Renvoie la case suivante à percuter en tant que tondeuse.
 * @param pos La position de la tondeuse
 * @param board Le plateau de jeu
 * @return Le case à percuter
 */
// TODO : supprimer les fonctions nextCaseStrategy si elles ne changent pas en fonction de l'entité
char mowerNextCaseStrategy(Position* pos, enum Direction direction, char board[ROWS][COLS]) {
    switch (direction) {
        case UP:
            return (board[pos->x-1][pos->y]);
            break;
        case DOWN:
            return (board[pos->x+1][pos->y]);
            break;
        case LEFT:
            return (board[pos->x][pos->y-1]);
            break;
        case RIGHT:
            return (board[pos->x][pos->y+1]);
            break;
        default:
            return WALL_CHAR;
    }
}

/**
 * Renvoie la condition de changement d'état pour un ennemi.
 * @param symbol La case actuelle
 * @param pos La position de l'ennemi
 * @return 1 si collision, 0 sinon
 */
int enemyCollidePropertyStrategy(char symbol, Position* pos) {
    return (symbol != THIN_CHAR && symbol != HERO_CHAR);
}

/**
 * Renvoie la condition de changement d'état pour une tondeuse.
 * @param symbol La case actuelle
 * @param pos La position de la tondeuse
 * @return 1 si collision, 0 sinon
 */
int mowerCollidePropertyStrategy(char symbol, Position* pos) {
    return (symbol != THIN_CHAR);
}

/**
 * Change l'état d'un ennemi après la collision.
 * @param enemy L'ennemi à modifier
 * @param direction La direction dans laquelle l'ennemi doit aller
 */
void enemyCollideStrategy(Entity* enemy, enum Direction direction) {
    enemy->direction = direction;
}

/**
 * Change l'état d'une tondeuse après la collision.
 * @param mower La tondeuse à modifier
 * @param direction La direction dans laquelle la tondeuse doit aller
 */
void mowerCollideStrategy(Entity* mower, enum Direction direction) {
    mower->state = FINAL;
}

/**
 * Lance l'action de l'ennemi à la fin de son déplacement.
 * @param game L'état du jeu
 * @param hero Le héros
 * @param enemy L'ennemi
 * @param board Le plateau de jeu
 */
void enemyFinalActionStrategy(GameState* game, Eceman* hero, Entity* enemy, char board[ROWS][COLS]) {
    if (enemy->caseBelow == HERO_CHAR)
        gotAttacked(game, board, hero);
}

/**
 * Lance l'action de la tondeuse à la fin de son déplacement.
 * @param game L'état du jeu
 * @param hero Le héros
 * @param mower La tondeuse
 * @param board Le plateau de jeu
 */
void mowerFinalActionStrategy(GameState* game, Eceman* hero, Entity* mower, char board[ROWS][COLS]) {
    game->levelScore++;

    drawEntity(board, mower);
    drawToolbar(game);
}

/**
 * Déplace l'entité sur le plateau de jeu.
 * @param game L'état du jeu
 * @param hero Le héros
 * @param entity L'entité à déplacer
 * @param board La plateau de jeu
 */
void moveEntity(GameState* game, Eceman* hero, Entity* entity, char board[ROWS][COLS]) {
    switch (entity->direction) {
        case UP:
            if (entity->collidePropertyStrategy(entity->nextCaseStrategy(entity->pos, UP, board), entity->pos)) {
                entity->collideStrategy(entity, DOWN);
                return;
            }

            entity->pos->x -= 1;
            break;

        case DOWN:
            if (entity->collidePropertyStrategy(entity->nextCaseStrategy(entity->pos, DOWN, board), entity->pos)) {
                entity->collideStrategy(entity, UP);
                return;
            }

            entity->pos->x += 1;
            break;

        case LEFT:
            if (entity->collidePropertyStrategy(entity->nextCaseStrategy(entity->pos, LEFT, board), entity->pos)) {
                entity->collideStrategy(entity, RIGHT);
                return;
            }

            entity->pos->y -= 1;
            break;

        case RIGHT:
            if (entity->collidePropertyStrategy(entity->nextCaseStrategy(entity->pos, RIGHT, board), entity->pos)) {
                entity->collideStrategy(entity, LEFT);
                return;
            }

            entity->pos->y += 1;
            break;
    }

    entity->caseBelow = board[entity->pos->x][entity->pos->y];

    entity->finalActionStrategy(game, hero, entity, board);
}

/**
 * Dessine l'entité passée en paramètre sur le plateau de jeu.
 * @param board Le plateau sur lequel l'entité est ajoutée
 * @param entity L'entité à ajouter
 */
void drawEntity(char board[ROWS][COLS], Entity* entity) {
    board[entity->pos->x][entity->pos->y] = entity->symbol;
    goToXY(entity->pos->y, entity->pos->x);

    setColor(entity->symbolColor);
    putchar(convertCase(entity->symbol));
    resetColor();
}

/**
 * Nettoie la case de l'ancienne position de l'entité.
 * @param board Le plateau de jeu sur lequel l'entité est retirée
 * @param entity L'entité à nettoyer
 */
void clearEntity(char board[ROWS][COLS], Entity* entity) {
    board[entity->pos->x][entity->pos->y] = entity->nextSymbol;
    goToXY(entity->pos->y, entity->pos->x);

    setColor(entity->nextSymbolColor);
    putchar(convertCase(entity->nextSymbol));
    resetColor();
}
