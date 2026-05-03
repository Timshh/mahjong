#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* window)
    : Manager(AssetManager()),
      RestartButton(window, &Manager, "Restart", 300, 250) {
  Window = window;
  Field.reset(new GameField(Window, &Manager));
}

void Gamemode::Tick() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    Window->close();
    return;
  }
  
  Window->clear();
  if (RestartButton.Tick()) {
    Field.reset(new GameField(Window, &Manager));
  }
  Field->Tick();
  Window->display();
}