#include <foxcore/render.h>
#include <stdbool.h>

bool running = true;

static int WIDTH = 1280;
static int HEIGHT = 720;

int main(int argc, char* argv[]) {

    SDL_Window *window = renderInit(WIDTH, HEIGHT);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        renderBegin();

        renderEnd(window);
    }

    return 0;
}
