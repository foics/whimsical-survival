#include <foxcore/render.hpp>
#include <foxcore/shader.hpp>
#include <foxcore/input.hpp>
#include <foxcore/object.hpp>
#include <foxcore/collision.hpp>

#include "input.hpp"

bool running = true;

static int WIDTH = 1280;
static int HEIGHT = 720;

int main(int argc, char* argv[]) {

    SDL_Window* window = renderInit(WIDTH, HEIGHT);

    unsigned int defaultShader = createShader("./shaders/default.vert", "./shaders/default.frag", WIDTH, HEIGHT);

    unsigned int quadTex = createTexture("./assets/player.png");

    Object *player = new Object(WIDTH / 2 - 50, HEIGHT / 2 - 50, 1, 100, 100, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    Object *object = new Object(WIDTH / 3, HEIGHT / 3, 0, 100, 100, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

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

        inputHandler(player);

        player->x += player->vx;
        player->y += player->vy;

        if (isOverlapping(player, object)) {
            object->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        } else {
            object->color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
        }

        renderClear(0.3f, 0.3f, 0.3f, 1.0f);

        drawSprite((glm::vec3){player->x, player->y, player->z},
                   (glm::vec2){player->width, player->height},
                   player->rot,
                   player->color,
                   quadTex,
                   defaultShader);

        drawQuad((glm::vec3){object->x, object->y, object->z}, (glm::vec2){object->width, object->height}, object->rot, object->color, defaultShader);

        renderEnd(window);
    }

    return 0;
}
