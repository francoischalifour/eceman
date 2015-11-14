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
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <assert.h>

/**
 * Initialise l'état du jeu.
 * @return L'état de jeu initialisé
 */
static GameState* newGameState() {
    GameState* game = malloc(sizeof(GameState));
    assert(game != NULL);

    game->score = 0;
    game->levelScore = 0;
    game->level = 1;
    game->pause = 1;
    game->playing = 0;
    game->timeStart = clock();
    game->timePlayed = 0;
    game->timeTmp = 0;
    game->type = CAMPAIGN;

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
    game->timeTmp = 0;
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
static void stopGame(GameState* game) {
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

    displayMessage("Pause");

    pauseTime = clock() - pauseTime;

    game->pause = 0;
    game->timeTmp += pauseTime;
    game->timeStart += pauseTime;
}

/**
 * Met fin au jeu.
 * @param game L'état du jeu
 */
void gameOver(GameState* game) {
    int timeBonus;

    stopGame(game);

    if (game->type == CAMPAIGN) {
        timeBonus = BONUS_MAX - game->timePlayed;

        if (timeBonus < 0)
            timeBonus = 0;

        game->playing = 0;
        game->score += game->levelScore;
        game->score += timeBonus;

        if (game->score > SCORE_MAX)
            game->score = SCORE_MAX;

        displayGameOver(game->score, game->timePlayed);
        saveRanking(game->score);
    } else {
        displayGameOver(game->levelScore, game->timeTmp);
    }

    goBack();
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
            if (game->type == CAMPAIGN)
                save(game);

            stopGame(game);
            break;

        case UP_KEY:
            hero->direction = UP;
            break;

        case DOWN_KEY:
            hero->direction = DOWN;
            break;

        case LEFT_KEY:
            hero->direction = LEFT;
            break;

        case RIGHT_KEY:
            hero->direction = RIGHT;
            break;
    }

    if (key == UP_KEY || key == DOWN_KEY || key == LEFT_KEY || key == RIGHT_KEY) {
            changeCaseType(game, board, hero);
            moveEceman(game, board, hero, entityList);
            drawEceman(board, hero);
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
 * @param backToSpawn 1 pour retourner au point de spawn, 0 sinon
 */
static void playGame(GameState* game, char board[ROWS][COLS], Eceman* hero, const int backToSpawn) {
    unsigned short i;
    FILE* map = loadMap(game->level);
    Entity* entityList[ENTITY_MAX] = {NULL};

    game->playing = 1;
    game->pause = 0;

    system("cls");

    drawBoard(map, game, board);

    if (backToSpawn != 0) {
        goToCase(board, hero, SPAWN_CHAR);
    } else {
        // Si le joueur tombe dans un trou et se retrouve à un endroit non autorisé.
        if (board[hero->pos->x][hero->pos->y] == OUTSIDE_CHAR || board[hero->pos->x][hero->pos->y] == WALL_CHAR) {
            goToCase(board, hero, SPAWN_CHAR);
        }
    }

    extractEntities(board, entityList);

    drawEceman(board, hero);

    i = 0;

    while (game->playing != 0) {
        if (kbhit())
            launchUserAction(getch(), game, board, hero, entityList);

        if (i % 10 == 0)
            launchEntityAction(game, board, hero, entityList);

        i++;

        game->timeTmp = (clock() - game->timeStart) / 1000;
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
    game->timePlayed += game->timeTmp;
    game->timeTmp = 0;
    game->timeStart = clock();

    playGame(game, board, hero, 1);
}

/**
 * Charge le niveau précédent suite à un malus.
 * @param game L'état actuel du jeu
 * @param hero Le héro
 */
void loadPreviousLevel(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    game->level -= 1;
    game->levelScore = 0;
    game->score /= 2;
    game->timePlayed += game->timeTmp;
    game->timeTmp = 0;
    game->timeStart = clock();

    playGame(game, board, hero, 0);
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

    playGame(game, board, hero, 1);
}

/**
 * Initialise une partie de jeu.
 * @param levelType Le type de partie à commencer
 *                  -   -1 : nouvelle partie
 *                  -   0 : chargement d'une partie
 *                  -   autre : partie rapide
 */
void initGame(const int levelType) {
    GameState* game = NULL;
    Eceman* hero = NULL;
    FILE* saving = NULL;
    char board[ROWS][COLS];
    unsigned int level, score;
    float timePlayed;

    game = newGameState();
    hero = newEceman();

    if (levelType != -1) {
        saving = loadSaving();

        if (levelType == 0) {
            level = getLastLevel(saving);
            score = getLastScore(saving);
            timePlayed = getLastTime(saving);
        } else {
            level = levelType;
            score = 0;
            timePlayed = 0;

            game->type = PARTIAL;
        }

        setGameState(game, level, score, 0, timePlayed, 1);
        closeSaving(saving);
    }

    playGame(game, board, hero, 1);

    destroyEceman(hero);
    destroyGameState(game);
}
