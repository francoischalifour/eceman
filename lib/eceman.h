#ifndef ECEMAN_ECEMAN_H
#define ECEMAN_ECEMAN_H

#include "position.h"
#include "direction.h"

/**
 * Enumération de l'état de Eceman.
 */
enum EcemanState {
    NORMAL,
    LIGHTNESS
};

/**
 * Structure du personnage principal Eceman.
 */
typedef struct Eceman {
   Position* pos;
   enum EcemanState state;
   enum Direction direction;
   unsigned char caseBelow;
} Eceman;

#endif // ECEMAN_ECEMAN_H
