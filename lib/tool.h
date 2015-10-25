#ifndef TOOL_H
#define TOOL_H

/**
 * Enumération des types d'outil.
 */
enum ToolType {
    MOWER,
    BRICK,
    LIGHTNESS_POTION,
    TUNNEL
};

/**
 * Structure d'un outil.
 */
typedef struct Tool {
    Position* pos;
    enum ToolType type;
} Tool;

#endif
