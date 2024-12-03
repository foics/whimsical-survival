#include <stdio.h>

#include "foxcore/shader.h"
#include "cglm/cglm.h"

void useShader(unsigned int shader) {
    glUseProgram(shader);
}

unsigned int createShader(const char *pathVert, const char *pathFrag, int width, int height) {
    int success;
    char log[512];

    File fileVertex = ioFileRead(pathVert);
    if (!fileVertex.isValid) {
        printf("Error reading shader: %s\n", pathVert);
        return -1;
    }

    File fileFragment = ioFileRead(pathFrag);
    if (!fileFragment.isValid) {
        printf("Error reading shader: %s\n", pathFrag);
        return -1;
    }

    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char *const *)&fileVertex, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, log);
        printf("Error shader vertex compilation failed! Logs: %s\n", log);
        return -1;
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char *const *)&fileFragment, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, log);
        printf("Error shader fragment compilation failed! Logs: %s\n", log);
        return -1;
    }

    // shader program
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, log);
        printf("Error shader program linking failed. Log: %s\n", log);
        return -1;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(fileVertex.data);
    free(fileFragment.data);

    useShader(shader);

    mat4 projection;
    glm_ortho(0, width, height, 0, -1.0f, 1.0f, projection);

    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, (const GLfloat*)projection);


    return shader;
}
