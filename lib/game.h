#ifndef GAME_H
#define GAME_H

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

/**
 * Structure de l'état du jeu.
 */
typedef struct GameState {
    unsigned short score;
    unsigned short levelScore;
    unsigned char level;
    unsigned int time;
} GameState;

#endif
