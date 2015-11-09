#ifndef ECEMAN_ENTITY_H
#define ECEMAN_ENTITY_H

#include "game.h"
#include "position.h"
#include "eceman.h"

typedef struct Entity Entity;

/**
 * Détermine la case suivante à percuter en fonction de l'entité.
 * @param pos La position de l'entité
 * @param direction La direction de l'entité
 * @return L'élément du plateau à percuter
 */
typedef char (*NextCaseStrategy) (Position* pos, enum Direction direction, char board[ROWS][COLS]);

/**
 * Détermine la condition de collision de l'entité avec un autre objet.
 * @param symbol La case du plateau à tester
 * @param La position de l'entité
 * @return 1 si collision, 0 sinon
 */
typedef int (*CollidePropertyStrategy) (char symbol, Position* pos);

/**
 * Détermine la stratégie de l'entité lorsqu'il percute un objet de la map.
 * @param entity L'entité dont on veut modifier le comportement
 * @param direction La nouvelle direction de l'entité
 */
typedef void (*CollideStrategy) (Entity* entity, enum Direction direction);

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
    NextCaseStrategy nextCaseStrategy;
    CollidePropertyStrategy collidePropertyStrategy;
    CollideStrategy collideStrategy;
    FinalActionStrategy finalActionStrategy;
};

/*
 * Prototypes
 */

void destroyEntity(Entity* entity);
Entity* createEnemy(unsigned int x, unsigned int y, enum Direction direction);
Entity* createMower(unsigned int x, unsigned int y, enum Direction direction);
char enemyNextCaseStrategy(Position* pos, enum Direction direction, char board[ROWS][COLS]);
char mowerNextCaseStrategy(Position* pos, enum Direction direction, char board[ROWS][COLS]);
int enemyCollidePropertyStrategy(char symbol, Position* pos);
int mowerCollidePropertyStrategy(char symbol, Position* pos);
void enemyCollideStrategy(Entity* enemy, enum Direction direction);
void mowerCollideStrategy(Entity* mower, enum Direction direction);
void enemyFinalActionStrategy(GameState* game, Eceman* hero, Entity* enemy, char board[ROWS][COLS]);
void mowerFinalActionStrategy(GameState* game, Eceman* hero, Entity* mower, char board[ROWS][COLS]);
void moveEntity(GameState* game, Eceman* hero, Entity* entity, char board[ROWS][COLS]);
void drawEntity(char board[ROWS][COLS], Entity* entity);
void clearEntity(char board[ROWS][COLS], Entity* entity);

#endif // ECEMAN_ENTITY_H
