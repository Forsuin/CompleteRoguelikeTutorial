#include <filesystem>
#include <iostream>
#include <vector>

#include "SDL.h"
#include "libtcod.hpp"

#include "entity.h"

std::filesystem::path getDataDirectory() {
    static auto root = std::filesystem::path{"."};

    while (!std::filesystem::exists(root / "data")) {
        root /= "..";
        if (!std::filesystem::exists(root)) {
            throw std::runtime_error("Could not find data directory");
        }
    }

    return root / "data";
}

int main(int argc, char* argv[]) {
    try {
        auto console = tcod::Console{80, 40};
        auto params = TCOD_ContextParams{};

        auto tileset = tcod::load_tilesheet(getDataDirectory() / "dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);

        params.tcod_version = TCOD_COMPILEDVERSION;
        params.tileset = tileset.get();
        params.vsync = true;
        params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
        params.window_title = "Complete Roguelike Tutorial";
        params.argc = argc;
        params.argv = argv;
        params.console = console.get();

        auto context = tcod::Context(params);

        std::vector<yarl::entity> entities;

        yarl::entity player(console.get_width() / 2, console.get_height() / 2, "@", {255, 255, 255});
        yarl::entity npc((console.get_width() / 2) - 5, (console.get_height() / 2), "@", {255, 255, 0});

        entities.push_back(player);
        entities.push_back(npc);

        while (true) {
            TCOD_console_clear(console.get());
            tcod::print(console, {player.x, player.y}, player.character, player.color, std::nullopt);
            context.present(console);

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
                                player.move(0, -1);
                                break;
                            }
                            case SDLK_DOWN: {
                                player.move(0, 1);
                                break;
                            }
                            case SDLK_LEFT: {
                                player.move(-1, 0);
                                break;
                            }
                            case SDLK_RIGHT: {
                                player.move(1, 0);
                                break;
                            }
                        }
                    }
                }
            }
        }

    } catch (const std::exception& exc) {
        std::cerr << exc.what() << "\n";
        throw;
    }
}
