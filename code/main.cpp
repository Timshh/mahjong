#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "gamemode.h"

int main() {
  srand(time(NULL));

  sf::RenderWindow Window(sf::VideoMode({1920, 1080}), "Mahjong",
                          sf::State::Fullscreen);
  Gamemode GM = Gamemode(&Window);


  while (Window.isOpen()) {
    while (auto event = Window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) Window.close();
    }
    GM.Tick();
  }
  return 0;
}