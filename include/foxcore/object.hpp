#pragma once

#include <glm/glm.hpp>

class Object {
public:
    int x, y, z;
    int width, height;
    glm::vec4 color;

    Object(int x, int y, int z, int width, int height, glm::vec4 color) {
        this->x = x;
        this->y = y;
        this->z = z;

        this->width = width;
        this->height = height;

        this->color = color;
    }

    int rot = 0;

    int vx = 0;
    int vy = 0;

};
