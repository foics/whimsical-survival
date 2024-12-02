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

    renderInitShader(defaultShader, WIDTH, HEIGHT);

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

        drawQuad((vec3){(WIDTH / 2) - 50, (HEIGHT / 2) - 50, 1}, (vec2){100, 100}, (vec4){1.0f, 1.0f, 1.0f, 1.0f}, defaultShader);
        drawQuad((vec3){(WIDTH / 2) - 25, (HEIGHT / 2) - 25, 0}, (vec2){100, 100}, (vec4){1.0f, 0.0f, 1.0f, 1.0f}, defaultShader);

        renderEnd(window);
    }

    return 0;
}
