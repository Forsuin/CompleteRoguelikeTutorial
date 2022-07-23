#include "SDL.h"

#include "engine.h"

#include <iostream>

void yarl::Engine::handleEvents() {
    SDL_Event event;
    SDL_WaitEvent(nullptr);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                std::exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: {
                        player->move(0, -1);
                        std::cout << "UP" << std::endl;
                        break;
                    }
                    case SDLK_DOWN: {
                        player->move(0, 1);
                        std::cout << "DOWN" << std::endl;
                        break;
                    }
                    case SDLK_LEFT: {
                        player->move(-1, 0);
                        std::cout << "LEFT" << std::endl;
                        break;
                    }
                    case SDLK_RIGHT: {
                        player->move(1, 0);
                        std::cout << "RIGHT" << std::endl;
                        break;
                    }
                }
            }
        }
    }
}

void yarl::Engine::render(tcod::Console& console, tcod::Context& context) {
    TCOD_console_clear(console.get());

    for (auto const& entity : entities) {
        tcod::print(console, {entity->x, entity->y}, entity->character, entity->color, std::nullopt);
    }

    context.present(console);
}
