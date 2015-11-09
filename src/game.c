#include "../lib/setup.h"
#include <conio.h>
#include <assert.h>
#include <Windows.h>
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
    game->timeTotal = 0;

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
void setGameState(GameState* game, const unsigned short level, const unsigned short score, const unsigned short levelScore, const float timeTotal, const unsigned short pause) {
    game->level = level;
    game->score = score;
    game->levelScore = levelScore;
    game->timeTotal = timeTotal;
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
    game->pause = 1;
    game->timeTotal += (clock() - game->timeStart);

    goToXY(7, 17);
    printf("Pause\n");

    getch();

    game->pause = 0;
    game->timeStart = clock();

    goToXY(7, 17);
    printf("     \n");
}

/**
 * Met fin au jeu.
 * @param game L'état du jeu
 */
void gameOver(GameState* game) {
    game->playing = 0;
    game->timeTotal += (clock() - game->timeStart);
    game->timeTotal /= 10000.0;
    game->score += game->levelScore;
    game->score = (int) ((float) (game->score / game->timeTotal) * 100);

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
    if (key == UP_KEY || key == DOWN_KEY || key == LEFT_KEY || key == RIGHT_KEY) {
        changeCaseType(game, board, hero);
        moveEceman(key, game, board, hero, entityList);
        drawEceman(board, hero);
    }

    switch (key) {
        case 'p':
            pauseGame(game);
            break;

        case 'r':
            reloadLevel(game, board, hero);
            break;

        case 'q':
            game->timeTotal = game->timeTotal + (clock() - game->timeStart);
            save(game);
            closeGame(game);
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
 *
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

        Sleep(DELAY);
    }

    i = 0;

    while (entityList[i] != NULL) {
        destroyEntity(entityList[i]);
        i++;
    }

    destroyEceman(hero);
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
 */
void initGame(const int isNew) {
    GameState* game = newGameState();
    Eceman* hero = newEceman();
    FILE* saving = NULL;
    char board[ROWS][COLS];
    unsigned int level;

    game->timeStart = clock();

    if (isNew != 0) {
        saving = loadSaving();

        if (isNew == 1)
            level = getLastLevel(saving);
        else
            level = isNew;

        setGameState(game, level, getLastScore(saving), 0, getLastTime(saving), 1);
        closeSaving(saving);
    }

    playGame(game, board, hero);
    destroyGameState(game);
}
