#include "foxcore/render.h"

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

    glEnable(GL_DEPTH_TEST);

    return window;
}

void renderBegin() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderEnd(SDL_Window* window) {
    SDL_GL_SwapWindow(window);
}
