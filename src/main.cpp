#include <filesystem>
#include <iostream>
#include <vector>
#include <memory>

#include "SDL.h"
#include "libtcod.hpp"

#include "engine.h"
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

        std::vector<std::shared_ptr<yarl::entity>> entities;

        auto player = std::make_shared<yarl::entity>(
            console.get_width() / 2, console.get_height() / 2, "@", TCOD_ColorRGB(255, 255, 255));
        auto npc = std::make_shared<yarl::entity>(
            (console.get_width() / 2) - 5, (console.get_height() / 2), "@", TCOD_ColorRGB(255, 255, 0));

        entities.push_back(player);
        entities.push_back(npc);

        yarl::Engine engine(entities, player);

        while (true) {
            engine.render(console, context);

            engine.handleEvents();
        }

    } catch (const std::exception& exc) {
        std::cerr << exc.what() << "\n";
        throw;
    }
}
