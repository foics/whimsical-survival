#include <foxcore/parser.hpp>

#include "input.hpp"

SDL_Scancode up = getKey(getValue("./config.ini", "up"));
SDL_Scancode down = getKey(getValue("./config.ini", "down"));
SDL_Scancode left = getKey(getValue("./config.ini", "left"));
SDL_Scancode right = getKey(getValue("./config.ini", "right"));

void inputHandler(Object *player) {
    if (isKeyDown(up)) {
        player->y--;
    }
    if (isKeyDown(down)) {
        player->y++;
    }

    if (isKeyDown(left)) {
        player->x--;
    }
    if (isKeyDown(right)) {
        player->x++;
    }
}
