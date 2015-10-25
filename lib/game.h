#ifndef GAME_H
#define GAME_H

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

/**
 * Structure de l'état du jeu.
 *     score : score total du jeu
 *     levelScore : score du niveau courant
 *     level : numéro du niveau courant
 */
typedef struct GameState {
    unsigned short score;
    unsigned short levelScore;
    unsigned short level;
} GameState;

#endif
