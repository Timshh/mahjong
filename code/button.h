#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "data.h"

class Button {
 public:
  Button(sf::RenderWindow* window, AssetManager* manager,
         const std::string text, const float x, const float y);

  bool Tick();

 private:
  sf::RenderWindow* Window;

  bool IsMouseOnButton();

  bool Pressed = false, Overlap = false;
  sf::Text ButtonText;
  sf::Sprite Back, Selected;
  const float OverlapAlpha = 16, ClickedAlpha = 32;
};