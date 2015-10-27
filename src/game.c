#include "../lib/setup.h"
#include <conio.h>
#include <assert.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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

    return game;
}

/**
 * Met à jour l'état du jeu.
 * @param score Le score total
 * @param levelScore Le score du niveau
 * @param level Le niveau actuel
 * @return Le nouvel état du jeu
 */
void setGameState(GameState* game, const unsigned short score, const unsigned short levelScore, const unsigned short level, const unsigned short pause) {
    game->score = score;
    game->levelScore = levelScore;
    game->level = level;
    game->pause = pause;
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
 * Retourne au menu et stop le jeu.
 * @param game L'état du jeu
 */
void backToMenu(GameState* game) {
    game->pause = 1;
    displayMenu();
}

/**
 * Met le jeu en pause.
 * Bloque le timer et toutes les interactions.
 * @param game L'état du jeu
 */
void stopGame(GameState* game) {
    game->pause = 1;
    goToXY(22, 0);
    printf("Pause\n");

    getch();

    game->pause = 0;
    goToXY(22, 0);
    printf("     \n");
}

/**
 * Met fin au jeu.
 * @param game L'état du jeu
 */
void gameOver(GameState* game) {
    game->pause = 1;
    clearSaving();
    displayGameOver();
}

/**
 * Lance une action liée à l'appui d'une touche.
 * @param key La touche
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 */
static void launchGameAction(const char key, GameState* game, char board[ROWS][COLS], Eceman* hero) {
    if (key == UP_KEY || key == DOWN_KEY || key == LEFT_KEY || key == RIGHT_KEY) {
        changeCaseType(board, hero->pos);
        moveEceman(key, game, board, hero);
        drawEceman(board, hero);
    }

    switch (key) {
        case 'p':
            stopGame(game);
            break;

        case 'q':
            save(game->level, game->score);
            backToMenu(game);
            break;
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
    FILE* map = loadMap(game->level);

    system("cls");

    game->pause = 0;

    drawBoard(map, game, board);

    goToSpawn(board, hero);

    drawEceman(board, hero);

    while (!(game->pause)) {
        launchGameAction(getch(), game, board, hero);

        #ifdef _WIN32
        Sleep(DELAY);
        #else
        usleep(DELAY * 1000);
        #endif
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
    playGame(game, board, hero);
}

/**
 * Initialise une partie de jeu.
 */
void initGame() {
    GameState* game = newGameState();
    Eceman* hero = newEceman();
    FILE* saving = NULL;
    char board[ROWS][COLS];

    if ((saving = loadSaving())) {
        setGameState(game, getScore(saving), 0, getLevel(saving), 1);
        closeSaving(saving);
    }

    playGame(game, board, hero);

    destroyGameState(game);
}
