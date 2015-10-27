#include "../lib/setup.h"
#include "../lib/tool.h"

/**
 * Change la masse du Eceman à LIGHTNESS pour ne pas casser la glace
 * @param hero Le Eceman dont la masse doit changer
 */
void onDrinkPotion(Eceman*	hero) {
	hero->state = LIGHTNESS;
}