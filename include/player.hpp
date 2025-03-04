#pragma once

#include <glm/glm.hpp>

class Player {
public:
    int x, y, z;
    int width, height;
    glm::vec4 color;

    Player(int x, int y, int z, int width, int height, glm::vec4 color) {
        this->x = x;
        this->y = y;
        this->z = z;

        this->width = width;
        this->height = height;

        this->color = color;
    }

    int rot = 0.0f;

};
