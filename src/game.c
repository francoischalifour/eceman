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

    return game;
}

/**
 * Met à jour l'état du jeu.
 * @param score Le score total
 * @param levelScore Le score du niveau
 * @param level Le niveau actuel
 * @return Le nouvel état du jeu
 */
void setGameState(GameState* game, const unsigned short score, const unsigned short levelScore, const unsigned short level) {
    game->score = score;
    game->levelScore = levelScore;
    game->level = level;
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
            stopGame();
            break;

        case 'q':
            displayMenu();
            break;
    }
}

/**
 * Met fin au jeu.
 */
void gameOver() {
    displayGameOver();
}

/**
 * Commence une partie.
 *
 * @param game L'état du jeu
 * @param hero Le Eceman
 * @param board Le plateau de jeu
 */
static void playGame(GameState* game, char board[ROWS][COLS], Eceman* hero) {
    unsigned char key;

    FILE* map = loadMap(game->level);

    system("cls");

    drawBoard(map, game, board);

    goToSpawn(board, hero);

    drawEceman(board, hero);

    while (1) {
        key = getch();

        launchGameAction(key, game, board, hero);

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
 * Initialise une partie de jeu.
 */
void initGame() {
    GameState* game = newGameState();
    Eceman* hero = newEceman();
    char board[ROWS][COLS];

    setGameState(game, 0, 0, 1);

    playGame(game, board, hero);

    destroyGameState(game);
}
