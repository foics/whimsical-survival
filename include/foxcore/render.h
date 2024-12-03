#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <cglm/cglm.h>

SDL_Window* renderInit(int width, int height);
void renderClear(float r, float g, float b, float a);
void renderEnd(SDL_Window* window);

void drawQuad(vec3 pos, vec2 size, float rotate, vec4 color, unsigned int shader);

unsigned int createTexture(const char* path);

void drawSprite(vec3 pos, vec2 size, float rotate, vec4 color, unsigned int texture, unsigned int shader);
