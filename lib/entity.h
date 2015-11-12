#ifndef ECEMAN_ENTITY_H
#define ECEMAN_ENTITY_H

#include "game.h"
#include "position.h"
#include "direction.h"
#include "eceman.h"

typedef struct Entity Entity;

/**
 * Détermine la condition de collision de l'entité avec un autre objet.
 * @param symbol La case du plateau à tester
 * @param La position de l'entité
 * @return 1 si collision, 0 sinon
 */
typedef int (*CollidePropertyStrategy) (const char symbol, const Position* pos);

/**
 * Détermine la stratégie de l'entité lorsqu'il percute un objet de la map.
 * @param entity L'entité dont on veut modifier le comportement
 * @param direction La nouvelle direction de l'entité
 */
typedef void (*CollideStrategy) (Entity* entity, const enum Direction direction);

/**
 * Lance l'action de l'entité une fois déplacée.
 * @param game L'état du jeu
 * @hero Le héros
 * @param entity L'entité pour laquelle on lance l'action
 * @param board Le plateau de jeu
 */
typedef void (*FinalActionStrategy) (GameState* game, Eceman* hero, Entity* entity, char board[ROWS][COLS]);

/**
 * Enumération des états des entités.
 */
enum EntityState {
    ACTIVE,
    FINAL
};

/**
 * Structure d'une entité.
 */
struct Entity {
    Position* pos;
    enum EntityState state;
    enum Direction direction;
    unsigned char caseBelow;
    unsigned char symbol;
    unsigned char symbolColor;
    unsigned char nextSymbol;
    unsigned char nextSymbolColor;
    CollidePropertyStrategy collidePropertyStrategy;
    CollideStrategy collideStrategy;
    FinalActionStrategy finalActionStrategy;
};

/*
 * Prototypes
 */

void destroyEntity(Entity* entity);
Entity* createEnemy(const unsigned int x, const unsigned int y, const enum Direction direction);
Entity* createMower(const unsigned int x, const unsigned int y);
char enemyNextCaseStrategy(const Position* pos, const enum Direction direction, char board[ROWS][COLS]);
char mowerNextCaseStrategy(const Position* pos, const enum Direction direction, char board[ROWS][COLS]);
int enemyCollidePropertyStrategy(const char symbol, const Position* pos);
int mowerCollidePropertyStrategy(const char symbol, const Position* pos);
void enemyCollideStrategy(Entity* enemy, const enum Direction direction);
void mowerCollideStrategy(Entity* mower, const enum Direction direction);
void enemyFinalActionStrategy(GameState* game, Eceman* hero, Entity* enemy, char board[ROWS][COLS]);
void mowerFinalActionStrategy(GameState* game, Eceman* hero, Entity* mower, char board[ROWS][COLS]);
void moveEntity(GameState* game, Eceman* hero, Entity* entity, char board[ROWS][COLS]);
void drawEntity(char board[ROWS][COLS], const Entity* entity);
void clearEntity(char board[ROWS][COLS], const Entity* entity);
void throwEntity(GameState* game, Eceman* hero, Entity* entity, char board[ROWS][COLS]);

#endif // ECEMAN_ENTITY_H
