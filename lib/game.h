#ifndef GAME_H
#define GAME_H

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

#define ROWS 15
#define COLS 19

#define DELAY 50

#define SCORE_MAX 9999

#define HERO_CHAR '*'
#define SPAWN_CHAR '$'
#define WALL_CHAR 'W'
#define DOOR_CHAR 'D'
#define THIN_CHAR 'o'
#define THICK_CHAR 'O'
#define MELT_CHAR '~'
#define UNDEFINED_CHAR '#'

/**
 * Structure de l'état du jeu.
 *     score : score total du jeu
 *     levelScore : score du niveau courant
 *     level : numéro du niveau courant
 *     pause : 0 pour non, 1 pour oui
 */
typedef struct GameState {
    unsigned short score;
    unsigned short levelScore;
    unsigned short level;
    unsigned short pause;
} GameState;

#endif
