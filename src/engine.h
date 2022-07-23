#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "entity.h"
#include "gameMap.h"

namespace yarl {

class Engine {
   public:
    std::vector<std::shared_ptr<yarl::entity>> entities;  // TODO: change to enforce uniqueness
    std::shared_ptr<yarl::entity> player;
    yarl::GameMap gameMap;

    Engine(
        std::vector<std::shared_ptr<yarl::entity>> entities,
        yarl::GameMap& gameMap,
        std::shared_ptr<yarl::entity> player)
        : entities(entities), gameMap(gameMap), player(player) {}
    void handleEvents();
    void render(tcod::Console& console, tcod::Context& context);
};
}  // namespace yarl
#endif
