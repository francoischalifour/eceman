#include "../lib/setup.h"
#include <conio.h>
#include <assert.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/**
 * Lance une action liée à l'appui d'une touche.
 * @param key La touche
 * @param board Le plateau de jeu
 * @param hero Le Eceman
 */
void launchGameAction(const char key, char board[ROWS][COLS], Eceman* hero) {
    if (key == UP_KEY || key == DOWN_KEY || key == LEFT_KEY || key == RIGHT_KEY) {
        changeCaseType(board, hero->pos);
        moveEceman(key, board, hero);
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
 * Charge le niveau suivant.
 * @param gameState L'état actuel du jeu
 * @param hero Le héro
 */
void loadNextLevel(GameState* gameState, Eceman* hero) {
    printf("Chargement du niveau suivant...\n");
}

/**
 * Met fin au jeu.
 */
void gameOver() {
    displayGameOver();
}

/**
 * Commence la partie.
 * Cette procédure initialise le plateau de jeu, affiche le plateau
 * et les changements intervenants au cours du jeu.
 */
void startGame() {
    unsigned char key;
    char board[ROWS][COLS];
    Eceman* hero = NULL;
    FILE* map = NULL;

    map = loadMap(1);
    hero = newEceman();

    system("cls");

    drawBoard(map, board);

    drawEceman(board, hero);

    while (1) {
        key = getch();

        launchGameAction(key, board, hero);

        #ifdef _WIN32
        Sleep(DELAY);
        #else
        usleep(DELAY * 1000);
        #endif
    }

    destroyEceman(hero);
}
