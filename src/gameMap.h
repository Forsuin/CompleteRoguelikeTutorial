#pragma once

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>

#include "libtcod.hpp"

namespace yarl {
enum class Tiles { Wall = 0, Floor = 1 };

class GameMap {
   public:
    int width, height;
    std::vector<Tiles> tiles;

    GameMap(int width, int height) : width(width), height(height) {
        tiles = std::vector<Tiles>(width * height, yarl::Tiles::Floor);

        for (int x = 30; x < 33; x++) {
            tiles[getIndex(x, 22)] = yarl::Tiles::Wall;
        }
    }

    int getIndex(int x, int y) { return (y * width + x); }

    bool inBounds(int x, int y) { return 0 <= x && x < width && 0 <= y && y < height; }

    void render(tcod::Console& console) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                console.at({x, y}) = tiles[getIndex(x, y)] == Tiles::Floor
                                         ? TCOD_ConsoleTile{'.', tcod::ColorRGB{255, 255, 255}, tcod::ColorRGB{0, 0, 0}}
                                         : TCOD_ConsoleTile{'#', tcod::ColorRGB{255, 255, 255}, {0, 0, 0}};
            }
        }
    }
};
}  // namespace yarl

#endif
