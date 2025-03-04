#include <foxcore/render.hpp>
#include <foxcore/shader.hpp>

#include "player.hpp"

bool running = true;

static int WIDTH = 1280;
static int HEIGHT = 720;

int main(int argc, char* argv[]) {

    SDL_Window* window = renderInit(WIDTH, HEIGHT);

    unsigned int defaultShader = createShader("./shaders/default.vert", "./shaders/default.frag", WIDTH, HEIGHT);

    unsigned int quadTex = createTexture("./assets/player.png");

    Player *player = new Player(WIDTH / 2 - 50, HEIGHT / 2 - 50, 1, 100, 100, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

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

        player->x++;

        renderClear(0.3f, 0.3f, 0.3f, 1.0f);

        drawSprite((glm::vec3){player->x, player->y, player->z},
                   (glm::vec2){player->width, player->height},
                   player->rot,
                   player->color,
                   quadTex,
                   defaultShader);

        drawQuad((glm::vec3){(WIDTH / 2) - 25, (HEIGHT / 2) - 25, 0}, (glm::vec2){100, 100}, 20.0f, (glm::vec4){1.0f, 0.0f, 1.0f, 1.0f}, defaultShader);

        renderEnd(window);
    }

    return 0;
}
