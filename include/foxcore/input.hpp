#pragma once

#include <SDL2/SDL.h>
#include <string>

SDL_Scancode getKey(std::string keyName);
bool isKeyDown(SDL_Scancode key);
