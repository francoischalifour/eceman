#include "../lib/setup.h"

int main() {
    unsigned char choice;

    do {
        displayMenu();

        choice = getChoice();

        launchAction(choice);
    } while (choice != QUIT_CHOICE);

    getchar();
    return 0;
}
