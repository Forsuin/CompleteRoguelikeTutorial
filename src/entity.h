#pragma once

#include <string>

#include "libtcod.hpp"

namespace yarl {
class entity {
   public:
    int x, y;
    int character;
    TCOD_ColorRGB color;

    entity(int x, int y, int character, TCOD_ColorRGB color) : x(x), y(y), character(character), color(color) {}
    void move(int dx, int dy);
};

}  // namespace yarl
