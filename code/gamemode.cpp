#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* window)
    : Manager(AssetManager()),
      RestartButton(window, &Manager, "Restart", 300, 150),
      BGMain(Manager.Empty),
      BGSub(Manager.Empty) {
  Window = window;
  Field.reset(new GameField(Window, &Manager));

  BGMain.setTexture(*Manager.GetBG());
  BGSub.setTexture(*Manager.GetBGSub());
  BGMain.setColor(sf::Color(127, 127, 127, 255));
  BGSub.setColor(sf::Color(255, 255, 255, 127));
}

void Gamemode::Tick() {
  float deltatime = Time.restart().asSeconds();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    Window->close();
    return;
  }
  
  Window->clear();
  DrawBG(deltatime);
  if (RestartButton.Tick()) {
    Field.reset(new GameField(Window, &Manager));
  }
  Field->Tick();
  Window->display();
}

void Gamemode::DrawBG(const float deltatime) {
  OffsetMain.x += 6. * deltatime;
  OffsetMain.y += 6. * deltatime;

  BGMain.setTextureRect(
      sf::IntRect(sf::Vector2i(OffsetMain.x, OffsetMain.y),
                  sf::Vector2i(Window->getSize().x, Window->getSize().y)));
  Window->draw(BGMain);

  OffsetSub.x -= 6. * deltatime;
  OffsetSub.y -= 6. * deltatime;

  BGSub.setTextureRect(
      sf::IntRect(sf::Vector2i(OffsetSub.x, OffsetSub.y),
                  sf::Vector2i(Window->getSize().x, Window->getSize().y)));
  Window->draw(BGSub);
}