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
                        if (gameMap.tiles[gameMap.getIndex(player->x, player->y)] == yarl::Tiles::Floor) {
                            player->move(0, -1);
                            break;
                        }
                    }
                    case SDLK_DOWN: {
                        if (gameMap.tiles[gameMap.getIndex(player->x, player->y)] == yarl::Tiles::Floor) {
                            player->move(0, 1);
                            break;
                        }
                    }
                    case SDLK_LEFT: {
                        if (gameMap.tiles[gameMap.getIndex(player->x, player->y)] == yarl::Tiles::Floor) {
                            player->move(-1, 0);
                            break;
                        }
                    }
                    case SDLK_RIGHT: {
                        if (gameMap.tiles[gameMap.getIndex(player->x, player->y)] == yarl::Tiles::Floor) {
                            player->move(1, 0);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void yarl::Engine::render(tcod::Console& console, tcod::Context& context) {
    TCOD_console_clear(console.get());

    gameMap.render(console);

    for (auto const& entity : entities) {
        console.at({entity->x, entity->y}).ch = entity->character;
        console.at({entity->x, entity->y}).fg = entity->color;
    }

    context.present(console);
}
