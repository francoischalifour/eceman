#ifndef ECEMAN_TOOL_H
#define ECEMAN_TOOL_H

#include "game.h"
#include "position.h"

/**
 * Enumération des types d'outils.
 */
enum ToolType {
    MOWER,
    ENEMY
};

/**
 * Enumération des états des outils.
 */
enum ToolState {
    ACTIVE,
    FINAL
};

/**
 * Structure d'un outil.
 */
typedef struct Tool {
    Position* pos;
    enum ToolType type;
    enum ToolState state;
    enum Direction direction;
    unsigned char caseBelow;
} Tool;

#endif // ECEMAN_TOOL_H
