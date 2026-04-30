#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* window) : Manager(AssetManager()) {
  Window = window;
  Field.reset(new GameField(Window, &Manager));
}

void Gamemode::Tick() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    Window->close();
    return;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
    if (CanRestart) {
      Field.reset(new GameField(Window, &Manager));
      CanRestart = false;
    }
  } else {
    CanRestart = true;
  }
  Window->clear();
  Field->Tick();
  Window->display();
}