#ifndef ECEMAN_SCORE_H
#define ECEMAN_SCORE_H

int getLastScore(FILE* scoreFile);
int getMinHighScore();
int getScoreLine(FILE* scoreFile, const int score);
int getNbScores();
int deleteScore(const int score);
float getLastTime(FILE* saving);
float getLastTimeStop(FILE* saving);

#endif // ECEMAN_SCORE_H
