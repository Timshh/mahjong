#include <cstdlib>
#include <ctime>

#include "gamemode.h"

#ifndef _RELEASE

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#endif 

int main() {
  srand(time(NULL));

  sf::RenderWindow Window(sf::VideoMode({800, 600}), "Mahjong",
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
    GM.Draw();
  }
  return 0;
}