#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/gtc/type_ptr.hpp>

#include "foxcore/shader.hpp"

#include "foxcore/render.hpp"

static unsigned int vaoQuad;
static unsigned int vboQuad;
static unsigned int eboQuad;

static unsigned int textureColor;

void initQuad(unsigned int *vao, unsigned int *vbo, unsigned int *ebo) {

    float vertices[] = {
        // xyz            TextureCoords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 2, 1
    };

    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // xyz
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    // TextureCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

SDL_Window* renderInit(int width, int height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow(
            "Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL
            );

    if (!window) {
        printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to load GL: %s\n", SDL_GetError());
        exit(1);
    }

    printf("OpenGL Loaded\n");
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthRange(0, 1);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);

    initQuad(&vaoQuad, &vboQuad, &eboQuad);

    glGenTextures(1, &textureColor);
    glBindTexture(GL_TEXTURE_2D, textureColor);

    uint8_t white[] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);

    glBindTexture(GL_TEXTURE_2D, 0);

    return window;
}

void renderClear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderEnd(SDL_Window* window) {
    SDL_GL_SwapWindow(window);
}

void drawQuad(glm::vec3 pos, glm::vec2 size, float rotate, glm::vec4 color, unsigned int shader) {

    useShader(shader);

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, pos);

    model = glm::translate(model, (glm::vec3){0.5f * size.x, 0.5f * size.y, 0.0f});
    model = glm::rotate(model, glm::radians(rotate), (glm::vec3){0.0f, 0.0f, 1.0f});
    model = glm::translate(model, (glm::vec3){-0.5f * size.x, -0.5f * size.y, 0.0f});

    model = glm::scale(model, (glm::vec3){size, 1.0f});

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    glBindTexture(GL_TEXTURE_2D, textureColor);

    glBindVertexArray(vaoQuad);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

unsigned int createTexture(const char* path) {

    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, colorChannels;
    unsigned char *data = stbi_load(path, &width, &height, &colorChannels, 0);
    if (!data) {
        printf("Error: Failed to load texture %s\n", path);
        return 0;
    }

    GLenum format = GL_RGBA;
    switch (colorChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            printf("Error: Invalid number of color channels: %s\n", path);
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void drawSprite(glm::vec3 pos, glm::vec2 size, float rotate, glm::vec4 color, unsigned int texture, unsigned int shader) {

    useShader(shader);

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, pos);

    model = glm::translate(model, (glm::vec3){0.5f * size.x, 0.5f * size.y, 0.0f});
    model = glm::rotate(model, glm::radians(rotate), (glm::vec3){0.0f, 0.0f, 1.0f});
    model = glm::translate(model, (glm::vec3){-0.5f * size.x, -0.5f * size.y, 0.0f});

    model = glm::scale(model, (glm::vec3){size, 1.0f});

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vaoQuad);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}
