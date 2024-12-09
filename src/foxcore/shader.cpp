#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "foxcore/shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void useShader(unsigned int shader) {
    glUseProgram(shader);
}

unsigned int createShader(const char *pathVert, const char *pathFrag, int width, int height) {
    int success;
    char log[512];

    std::string fileVertex = readFile(pathVert);

    std::string fileFragment = readFile(pathFrag);

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

    useShader(shader);

    glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    return shader;
}
