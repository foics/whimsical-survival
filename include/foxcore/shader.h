#include <glad/glad.h>

#include <foxcore/io.h>

void useShader(unsigned int shader);
unsigned int createShader(const char *pathVert, const char *pathFrag, int width, int height);
