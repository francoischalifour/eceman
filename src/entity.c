/*
 * entity.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent les entités du jeu.
 *
 * Le concept de poymorphisme a été appliqué pour les entités.
 * Chaque entité possède un comporte spécifique lié à l'appel
 * d'une fonction en rapport avec son type. Les fichiers extérieurs
 * n'ont pas à savoir de quel type est l'entité.
 *
 * Objectifs :
 *     -    Créer et détruire une entité
 *     -    Créer un type spécifique d'entité en fonction de cette première
 *           fonction
 *     -    Créer les stratégies en fonction du type de l'entité
 *     -    Déplacer l'entité
 *     -    Dessiner et nettoyer l'affichage de l'entité
 */

#include "../lib/setup.h"
#include "../lib/game.h"
#include "../lib/entity.h"
#include <windows.h>
#include <assert.h>

/**
 * Créé une nouvelle entité.
 * @param x L'abscisse
 * @param y L'ordonnée
 * @param direction La direction
 * @param caseBelow La case en dessous de l'entité
 * @param symbol Le symbol sur la map
 * @param symbolColor La couleur du symbol
 * @param nextSymbol Le symbol après passage
 * @param nextSymbolColor La couleur du symbol après passage
 * @param collidePropertyStrategy La condition de collision
 * @param collideStrategy L'action après collision
 * @param finalActionStrategy L'action après le déplacement
 * @return L'entité initialisée
 */
static Entity* createEntity(const unsigned int x, const unsigned int y, const enum Direction direction, const char caseBelow, const char symbol, const char symbolColor, const char nextSymbol, const char nextSymbolColor, CollidePropertyStrategy collidePropertyStrategy, CollideStrategy collideStrategy, FinalActionStrategy finalActionStrategy) {
    Position* pos = malloc(sizeof(Position));
    Entity* entity = malloc(sizeof(Entity));

    assert(pos != NULL);
    assert(entity != NULL);

    pos->x = x;
    pos->y = y;

    entity->pos = pos;
    entity->state = ACTIVE;
    entity->direction = direction;
    entity->caseBelow = caseBelow;
    entity->symbol = symbol;
    entity->symbolColor = symbolColor;
    entity->nextSymbol = nextSymbol;
    entity->nextSymbolColor = nextSymbolColor;

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
Entity* createEnemy(const unsigned int x, const unsigned int y, const enum Direction direction) {
    return createEntity(x, y, direction, THIN_CHAR, ENEMY_CHAR, ENEMY_CHAR_COLOR, THIN_CHAR, THIN_CHAR_COLOR, enemyCollidePropertyStrategy, enemyCollideStrategy, enemyFinalActionStrategy);
}

/**
 * Crée une nouvelle tondeuse.
 * @param x L'abscisse de la tondeuse
 * @param y L'abscisse de la tondeuse
 * @param direction La direction de la tondeuse
 * @return Une nouvelle tondeuse
 */
Entity* createMower(const unsigned int x, const unsigned int y) {
    return createEntity(x, y, UP, THICK_CHAR, MOWER_CHAR, MOWER_CHAR_COLOR, MELT_CHAR, MELT_CHAR_COLOR, mowerCollidePropertyStrategy, mowerCollideStrategy, mowerFinalActionStrategy);
}

/**
 * Renvoie la condition de changement d'état pour un ennemi.
 * @param symbol La case actuelle
 * @param pos La position de l'ennemi
 * @return 1 si collision, 0 sinon
 */
int enemyCollidePropertyStrategy(const char symbol, const Position* pos) {
    return (symbol != THIN_CHAR && symbol != SLIP_CHAR && symbol != HERO_CHAR);
}

/**
 * Renvoie la condition de changement d'état pour une tondeuse.
 * @param symbol La case actuelle
 * @param pos La position de la tondeuse
 * @return 1 si collision, 0 sinon
 */
int mowerCollidePropertyStrategy(const char symbol, const Position* pos) {
    return (symbol != THIN_CHAR && symbol != THICK_CHAR && symbol != SLIP_CHAR);
}

/**
 * Change l'état d'un ennemi après la collision.
 * @param enemy L'ennemi à modifier
 * @param direction La direction dans laquelle l'ennemi doit aller
 */
void enemyCollideStrategy(Entity* enemy, const enum Direction direction) {
    enemy->direction = direction;
}

/**
 * Change l'état d'une tondeuse après la collision.
 * @param mower La tondeuse à modifier
 * @param direction La direction dans laquelle la tondeuse doit aller
 */
void mowerCollideStrategy(Entity* mower, const enum Direction direction) {
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
            if (entity->collidePropertyStrategy(board[entity->pos->x-1][entity->pos->y], entity->pos)) {
                entity->collideStrategy(entity, DOWN);
                return;
            }

            entity->pos->x -= 1;
            break;

        case DOWN:
            if (entity->collidePropertyStrategy(board[entity->pos->x+1][entity->pos->y], entity->pos)) {
                entity->collideStrategy(entity, UP);
                return;
            }

            entity->pos->x += 1;
            break;

        case LEFT:
            if (entity->collidePropertyStrategy(board[entity->pos->x][entity->pos->y-1], entity->pos)) {
                entity->collideStrategy(entity, RIGHT);
                return;
            }

            entity->pos->y -= 1;
            break;

        case RIGHT:
            if (entity->collidePropertyStrategy(board[entity->pos->x][entity->pos->y+1], entity->pos)) {
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
void drawEntity(char board[ROWS][COLS], const Entity* entity) {
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
void clearEntity(char board[ROWS][COLS], const Entity* entity) {
    goToXY(entity->pos->y, entity->pos->x);

    if (entity->caseBelow == THICK_CHAR) {
        setColor(THIN_CHAR_COLOR);
        board[entity->pos->x][entity->pos->y] = THIN_CHAR;
        putchar(convertCase(THIN_CHAR));
    } else if (entity->caseBelow == SLIP_CHAR) {
        setColor(SLIP_CHAR_COLOR);
        board[entity->pos->x][entity->pos->y] = SLIP_CHAR;
        putchar(convertCase(SLIP_CHAR));
    } else {
        setColor(entity->nextSymbolColor);
        board[entity->pos->x][entity->pos->y] = entity->nextSymbol;
        putchar(convertCase(entity->nextSymbol));
    }

    resetColor();
}

/**
 * Envoie une entité tant que sont état n'est pas final.
 * @param game L'état du jeu
 * @param hero Le héros
 * @param entity L'entité à envoyer
 * @param board Le plateau de jeu
 */
void throwEntity(GameState* game, Eceman* hero, Entity* entity, char board[ROWS][COLS]) {
    while (entity->state != FINAL) {
        clearEntity(board, entity);
        moveEntity(game, hero, entity, board);
        drawEntity(board, entity);

        Sleep(100);
    }
}
