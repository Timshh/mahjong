#pragma once
#include <SFML/Graphics.hpp>

#include "data.h"

class Actor{
 public:
  Actor(sf::RenderWindow* const window);

  void virtual ResetScales(const sf::Vector2f offset, const float mult);
  void virtual ChangeLanguage();

 protected:
  sf::RenderWindow* Window;
};