#include <foxcore/parser.hpp>

#include "input.hpp"

SDL_Scancode up = getKey(getValue("./config.ini", "up"));
SDL_Scancode down = getKey(getValue("./config.ini", "down"));
SDL_Scancode left = getKey(getValue("./config.ini", "left"));
SDL_Scancode right = getKey(getValue("./config.ini", "right"));

void inputHandler(Object *player) {
    int speed = 2;

    if (isKeyDown(up) && isKeyDown(down)) {
        player->vy = 0;
    } else if (isKeyDown(up)) {
        player->vy = -speed;
    } else if (isKeyDown(down)) {
        player->vy = speed;
    } else {
        player->vy = 0;
    }

    if (isKeyDown(left) && isKeyDown(right)) {
        player->vx = 0;
    } else if (isKeyDown(left)) {
        player->vx = -speed;
    } else if (isKeyDown(right)) {
        player->vx = speed;
    } else {
        player->vx = 0;
    }
}
