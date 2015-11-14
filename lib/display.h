#ifndef ECEMAN_DISPLAY_H
#define ECEMAN_DISPLAY_H

void displayTitle();
void displayMenu();
void displayLevels(const int mode);
void displaySettings();
void displayEditor();
void displayRules();
void displayGameOver(const int scoreFinal, const float timePlayed);
void displayRanking();
void displayAbout();
void displayMessage(char* message);

#endif // ECEMAN_DISPLAY_H
