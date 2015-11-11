/*
 * game.c
 * Ce fichier regroupe l'ensemble des fonctions
 * qui gèrent le jeu et son état.
 *
 * Objectifs :
 *     -    Créer, modifier et détruire un état de jeu
 *     -    Mettre le jeu en pause
 *     -    Quitter le jeu
 *     -    Lancer l'action de l'utilisateur
 *     -    Lancer l'action d'une entité
 *     -    Charger le niveau suivant
 *     -    Recharger le niveau actuel
 *     -    Initialiser le jeu
 */

#include "../lib/setup.h"
#include <conio.h>
#include <assert.h>
#include <windows.h>
#include <math.h>
#include <time.h>

/**
 * Initialise l'état du jeu.
 * @return L'état de jeu initialisé
 */
static GameState* newGameState() {
    GameState* game = malloc(sizeof(GameState));

    game->score = 0;
    game->levelScore = 0;
    game->level = 1;
    game->pause = 1;
    game->playing = 0;
    game->timeStart = 0;
    game->timePlayed = 0;

    return game;
}

/**
 * Met à jour l'état du jeu.
 * @param game L'état du jeu
 * @param level Le niveau actuel
 * @param score Le score total
 * @param levelScore Le score du niveau
 * @param time Le temps de jeu
 * @param pause Etat de pause
 * @return Le nouvel état du jeu
 */
void setGameState(GameState* game, const unsigned short level, const unsigned short score, const unsigned short levelScore, const float timePlayed, const unsigned short pause) {
    game->level = level;
    game->score = score;
    game->levelScore = levelScore;
    game->timePlayed = timePlayed;
    game->pause = pause;
    game->playing = 0;
}

/**
 * Détruit l'état du jeu.
 * Libère la mémoire en le libérant.
 * @param game L'état de jeu à supprimer
 */
static void destroyGameState(GameState* game) {
    free(game);
}

/**
 * Ferme la partie en cours.
 * @param game L'état du jeu à stopper
 */
static void closeGame(GameState* game) {
    game->playing = 0;
}

/**
 * Met le jeu en pause.
 * Bloque le timer et toutes les interactions.
 * @param game L'état du jeu
 */
void pauseGame(GameState* game) {
    float pauseTime;

    pauseTime = clock();

    game->pause = 1;

    goToXY(7, 17);
    printf("Pause\n");

    getch();

    pauseTime = clock() - pauseTime;

    game->pause = 0;
    game->timeStart += pauseTime;

    goToXY(7, 17);
    printf("     \n");
}

/**
 * Met fin au jeu.
 * @param game L'état du jeu
 */
void gameOver(GameState* game) {
    int timeBonus;

    timeBonus = BONUS_MAX - game->timePlayed;

    if (timeBonus < 0)
        timeBonus = 0;

    game->playing = 0;
    game->score += game->levelScore;
    game->score += timeBonus;

    if (game->score > SCORE_MAX)
        game->score = SCORE_MAX;

    displayGameOver(game->score);
    saveRanking(game->score);
    closeGame(game);
}

/**
 * Lance une action liée à l'appui d'une touche
 * de la par de l'utilisateur.
 * @param key La touche
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 */
static void launchUserAction(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]) {
    switch (key) {
        case 'p':
            pauseGame(game);
            break;

        case 'r':
            reloadLevel(game, board, hero);
            break;

        case 'q':
            save(game);
            closeGame(game);
            break;

        case UP_KEY:
        case DOWN_KEY:
        case LEFT_KEY:
        case RIGHT_KEY:
            changeCaseType(game, board, hero);
            moveEceman(key, game, board, hero, entityList);
            drawEceman(board, hero);
            break;
    }
}

/**
 * Lance une action externe à l'utilisateur.
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 * @param enemyList La liste des ennemis
 */
static void launchEntityAction(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]) {
    unsigned int i;

    i = 0;

    while (entityList[i] != NULL) {
        if (entityList[i]->symbol == ENEMY_CHAR) {
            clearEntity(board, entityList[i]);
            moveEntity(game, hero, entityList[i], board);
            drawEntity(board, entityList[i]);
        }

        i++;
    }
}

/**
 * Commence une partie.
 * @param game L'état du jeu
 * @param hero Le Eceman
 * @param board Le plateau de jeu
 */
static void playGame(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    unsigned short i;
    FILE* map = loadMap(game->level);
    Entity* entityList[ENTITY_MAX] = {NULL};

    game->playing = 1;
    game->pause = 0;

    system("cls");

    drawBoard(map, game, board);

    goToCase(board, hero, SPAWN_CHAR);

    extractEntities(board, entityList);

    drawEceman(board, hero);

    i = 0;

    while (game->playing != 0) {
        if (kbhit())
            launchUserAction(getch(), game, board, hero, entityList);

        if (i % 10 == 0)
            launchEntityAction(game, board, hero, entityList);

        i++;

        game->timePlayed = (clock() - game->timeStart) / 1000;
        drawTime(game);

        Sleep(DELAY);
    }

    i = 0;

    while (entityList[i] != NULL) {
        destroyEntity(entityList[i]);
        i++;
    }
}

/**
 * Charge le niveau suivant.
 * @param game L'état actuel du jeu
 * @param hero Le héro
 */
void loadNextLevel(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    game->level += 1;
    game->score += game->levelScore;
    game->levelScore = 0;
    hero->state = NORMAL;

    playGame(game, board, hero);
}

/**
 * Redémarre le niveau
 * @param game La partie à redémarrer
 * @param board Le plateau à reinitialiser
 * @param hero Le héro
 */
void reloadLevel(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    game->levelScore = 0;
    hero->state = NORMAL;

    playGame(game, board, hero);
}

/**
 * Initialise une partie de jeu.
 * @param specificLevel Le niveau à commencer
 */
void initGame(const int specificLevel) {
    GameState* game = NULL;
    Eceman* hero = NULL;
    FILE* saving = NULL;
    char board[ROWS][COLS];
    unsigned int level, score;
    float timePlayed, timeStop;

    game = newGameState();
    hero = newEceman();


    if (specificLevel != 0) {
        saving = loadSaving();

        if (specificLevel == 1) {
            level = getLastLevel(saving);
            score = getLastScore(saving);
            timePlayed = getLastTime(saving);
            timeStop = getLastTimeStop(saving);
            game->timeStart = clock() - timeStop; // TODO : corriger le calcul.
        } else {
            level = specificLevel;
            score = 0;
            timePlayed = 0;
            game->timeStart = clock();
        }

        setGameState(game, level, score, 0, timePlayed, 1);
        closeSaving(saving);
    }

    playGame(game, board, hero);

    destroyEceman(hero);
    destroyGameState(game);
}
