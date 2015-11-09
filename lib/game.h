#ifndef ECEMAN_GAME_H
#define ECEMAN_GAME_H

#define SAVE_FILE "../data/saving/game.sav"
#define SCORE_FILE "../data/saving/scores.sav"
#define SCORE_FILE_TMP "../data/saving/scores.tmp"

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

#define ROWS 15
#define COLS 19

#define DELAY 50

#define SCORE_MAX 9999
#define RANKING_MAX 10
#define ENTITY_MAX 10

#define NAME_LENGTH 35

/**
 * Enumération des directions.
 */
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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
    float timeTotal;
    float timeStart;
    unsigned short level;
    unsigned short pause;
    unsigned short playing;
} GameState;

#endif // ECEMAN_GAME_H
