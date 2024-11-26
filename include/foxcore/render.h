#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>

SDL_Window* renderInit(int width, int height);
void renderBegin();
void renderEnd(SDL_Window* window);
