#ifndef ECEMAN_MAP_H
#define ECEMAN_MAP_H

FILE* loadMap(short level);
void closeMap(FILE* map);
void editMap(const int level);

#endif // ECEMAN_MAP_H
