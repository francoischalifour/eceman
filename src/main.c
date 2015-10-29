#include "../lib/setup.h"

int main() {
    do {
        displayMenu();

        launchAction(getChoice());
    } while (1);

    getchar();
    return 0;
}
