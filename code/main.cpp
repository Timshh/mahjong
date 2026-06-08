#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "gamemode.h"

int main() {
  srand(time(NULL));

  sf::RenderWindow Window(sf::VideoMode({1920, 1080}), "Mahjong",
                          sf::State::Windowed);
  Gamemode GM = Gamemode(&Window);

  while (Window.isOpen()) {
    while (auto event = Window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) Window.close();
      if (const auto* resized = event->getIf<sf::Event::Resized>()) {
        sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
        Window.setView(sf::View(visibleArea));
        GM.Resize();
      }
    }
    GM.Tick();
  }
  return 0;
}