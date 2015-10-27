#ifndef ECEMAN_CASE_H
#define ECEMAN_CASE_H

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
