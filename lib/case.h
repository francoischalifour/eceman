#ifndef ECEMAN_CASE_H
#define ECEMAN_CASE_H

#define HERO_CHAR '*'
#define SPAWN_CHAR '$'
#define THIN_CHAR 'o'
#define THICK_CHAR 'O'
#define MELT_CHAR '~'
#define OUTSIDE_CHAR '#'
#define WALL_CHAR 'W'
#define DOOR_CHAR 'D'
#define LIGHTNESS_POTION_CHAR 'P'
#define TUNNEL_CHAR 'T'
#define TUNNEL_EXIT_CHAR 'E'
#define ENEMY_CHAR 'Y'

#define HERO_CHAR_COLOR 176
#define THIN_CHAR_COLOR 191
#define THICK_CHAR_COLOR 176
#define MELT_CHAR_COLOR 151
#define OUTSIDE_CHAR_COLOR 128
#define WALL_CHAR_COLOR 63
#define DOOR_CHAR_COLOR 232
#define LIGHTNESS_POTION_CHAR_COLOR 191
#define TUNNEL_CHAR_COLOR 8
#define ENEMY_CHAR_COLOR 191
#define DEFAULT_COLOR 15

/**
 * Enumération des types de case.
 */
enum CaseType {
    MELT,
    THIN,
    THICK,
    WALL,
    OUTSIDE,
    DOOR,
    SPAWN
};

/**
 * Structure de la case.
 */
typedef struct Case {
    enum CaseType type;
} Case;

#endif // ECEMAN_CASE_H
