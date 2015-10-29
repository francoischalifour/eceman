#ifndef ECEMAN_ECEMAN_H
#define ECEMAN_ECEMAN_H

/**
 * Enumération de l'état de Eceman.
 */
enum EcemanState {
    NORMAL,
    LIGHTNESS
};

/**
 * Structure de la position de Eceman.
 */
typedef struct Position {
   unsigned short x;
   unsigned short y;
} Position;

/**
 * Structure du personnage principal Eceman.
 */
typedef struct Eceman {
   enum EcemanState state;
   Position* pos;
   unsigned char caseBelow;
} Eceman;

#endif // ECEMAN_ECEMAN_H
