#include "../lib/setup.h"
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/**
 * Lance une action liée à l'appui d'une touche.
 * @param hero Le Eceman
 * @param key La touche
 */
void launchGameAction(Eceman* hero, const char key) {
    // TODO
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
    char board[ROWS][COLS] = {{'0'}};
    char key;
    Eceman* hero = newEceman();

    system("cls");

    drawBoard(board, hero);

    while (1) {
        if (kbhit()) {
            launchGameAction(hero, getch());
        }

        clearEceman(board, hero);

        moveEceman(board, key, hero);

        drawEceman(board, hero);

        #ifdef _WIN32
        Sleep(DELAY);
        #else
        usleep(DELAY * 1000);
        #endif
    }

    destroyEceman(hero);
}
