#pragma once

#include <glm/glm.hpp>

class Player {
public:
    int x, y, z;
    int xSize, ySize;
    glm::vec4 color;

    Player(int x, int y, int z, int xSize, int ySize, glm::vec4 color) {
        this->x = x;
        this->y = y;
        this->z = z;

        this->xSize = xSize;
        this->ySize = ySize;

        this->color = color;
    }

    int rot = 0.0f;

};
