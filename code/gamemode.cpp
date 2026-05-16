#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* window)
    : Manager(AssetManager()),
      RestartButton(window, &Manager, "Restart", 50, 40),
      BG(Manager.Empty) {
  Window = window;
  Field.reset(new GameField(Window, &Manager));

  BG.setTexture(*Manager.GetBG());
  BG.setColor(sf::Color(127, 127, 127, 255));
}

void Gamemode::Tick() {
  float deltatime = Time.restart().asSeconds();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    Window->close();
    return;
  }
  
  Window->clear();
  DrawBG();
  if (RestartButton.Tick()) {
    Field.reset(new GameField(Window, &Manager));
  }
  Field->Tick();
  Window->display();
}

void Gamemode::DrawBG() {
  Window->draw(BG);
}