#include <format>

#include "libtcod.hpp"

template <typename... Args>
void print(const std::string_view str_fmt, Args&&... args) {
  fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
  print("Hello World");

  int playerX = 40, playerY = 25;

  TCODConsole::initRoot(80, 50, "CompleteRoguelikeTutorial", false);

  while (!TCODConsole::isWindowClosed()) {
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

    switch (key.vk) {
      case TCODK_UP:
        playerY--;
        break;
      case TCODK_DOWN:
        playerY++;
        break;
      case TCODK_LEFT:
        playerX--;
        break;
      case TCODK_RIGHT:
        playerX++;
        break;
    }

    TCODConsole::root->clear();
    TCODConsole::root->putChar(playerX, playerY, '@');
    TCODConsole::flush();
  }
  return 0;
}
