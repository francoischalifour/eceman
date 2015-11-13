#ifndef ECEMAN_GAME_H
#define ECEMAN_GAME_H

#include "game.h"
#include "direction.h"
#include "eceman.h"

#define SAVE_FILE "../data/saving/game.sav"
#define SCORE_FILE "../data/saving/scores.sav"
#define SCORE_FILE_TMP "../data/saving/scores.tmp"
#define MAP_DIR "../data/map/"
#define RULES_FILE "../data/info/rules.txt"
#define ABOUT_FILE "../data/info/about.txt"

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
#define BONUS_MAX 500

#define NAME_LENGTH 35

/**
 * Enumération des différents types de parties.
 */
enum GameType {
    CAMPAIGN,
    PARTIAL
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
    float timeStart;
    float timePlayed;
    float timeTmp;
    unsigned short level;
    unsigned short pause;
    unsigned short playing;
    enum GameType type;
} GameState;

/*
 * Prototypes
 */

void initGame(const int isNew);
void loadNextLevel(GameState* game, char board[ROWS][COLS], Eceman* hero);
void loadPreviousLevel(GameState* game, char board[ROWS][COLS], Eceman* hero);
void reloadLevel(GameState* game, char board[ROWS][COLS], Eceman* hero);
void pauseGame(GameState* game);
void gameOver(GameState* game);

#endif // ECEMAN_GAME_H
