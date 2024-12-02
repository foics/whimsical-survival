#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <cglm/cglm.h>

SDL_Window* renderInit(int width, int height);
void renderInitShader(unsigned int shader, int width, int height);
void renderBegin();
void renderEnd(SDL_Window* window);

void drawQuad(vec3 pos, vec2 size, vec4 color, unsigned int shader);
