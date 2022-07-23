#pragma once

#include <vector>

#include "entity.h"

namespace yarl {

class Engine {
   public:
    std::vector<std::shared_ptr<yarl::entity>> entities;  // TODO: change to enforce uniqueness
    std::shared_ptr<yarl::entity> player;

    Engine(std::vector<std::shared_ptr<yarl::entity>> entities, std::shared_ptr<yarl::entity> player)
        : entities(entities), player(player) {}
    void handleEvents();
    void render(tcod::Console& console, tcod::Context& context);
};
}  // namespace yarl
