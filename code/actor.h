#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "data.h"

class Actor{
 public:
  Actor(sf::RenderWindow* const window);
  virtual ~Actor() = default;

  void virtual ResetScales(const sf::Vector2f offset, const float mult);
  void virtual ChangeLanguage();

 protected:
  sf::RenderWindow* Window;
};