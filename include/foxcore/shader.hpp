#include <glad/glad.h>

#include <foxcore/io.hpp>

void useShader(unsigned int shader);
unsigned int createShader(const char *pathVert, const char *pathFrag, int width, int height);
