#pragma once

#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

SDL_Window* renderInit(int width, int height);
void renderClear(float r, float g, float b, float a);
void renderEnd(SDL_Window* window);

void drawQuad(glm::vec3 pos, glm::vec2 size, float rotate, glm::vec4 color, unsigned int shader);

unsigned int createTexture(const char* path);

void drawSprite(glm::vec3 pos, glm::vec2 size, float rotate, glm::vec4 color, unsigned int texture, unsigned int shader);
