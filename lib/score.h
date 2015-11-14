#ifndef ECEMAN_SCORE_H
#define ECEMAN_SCORE_H

int getLastScore(FILE* scoreFile);
int getMinHighScore();
int getScoreLine(FILE* scoreFile, const int score);
int getNbScores();
float getLastTime(FILE* saving);
float getLastTimeStop(FILE* saving);

#endif // ECEMAN_SCORE_H
