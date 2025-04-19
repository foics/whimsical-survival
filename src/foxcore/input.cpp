#include <string>

#include "foxcore/input.hpp"

const uint8_t *currentKeyStates = SDL_GetKeyboardState(NULL);

SDL_Scancode getKey(std::string keyName) {
    SDL_Scancode key = SDL_GetScancodeFromName(keyName.c_str());
    return key;
}

bool isKeyDown(SDL_Scancode key) {
    if (currentKeyStates[key]) {
        return true;
    } else {
        return false;
    }
}
