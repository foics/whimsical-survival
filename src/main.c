#include <foxcore/render.h>
#include <foxcore/shader.h>

bool running = true;

static int WIDTH = 1280;
static int HEIGHT = 720;

enum gameState {
    ACTIVE,
    MENU
};

int main(int argc, char* argv[]) {

    SDL_Window *window = renderInit(WIDTH, HEIGHT);

    unsigned int defaultShader = createShader("./shaders/default.vert", "./shaders/default.frag");

    useShader(defaultShader);

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
