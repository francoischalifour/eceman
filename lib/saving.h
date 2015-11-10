#ifndef ECEMAN_SAVING_H
#define ECEMAN_SAVING_H

#include "game.h"

void save(GameState* game);
void saveRanking(const int score);
FILE* loadSaving();
void closeSaving(FILE* saving);

#endif // ECEMAN_SAVING_H
