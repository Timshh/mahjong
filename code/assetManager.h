#pragma once
#include <lunasvg.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "data.h"

class AssetManager {
 public:
  AssetManager();

  sf::Texture* GetBG();
  sf::Texture* GetCardShadow();
  sf::Texture* GetCardBack();
  sf::Texture* GetCard(const CardTypes type);
  sf::Texture* GetButton();

  sf::Font MainFont;
  sf::Texture Empty;

  const sf::Vector2f ImageOffset = sf::Vector2f(10.5, 14),
                     EdgeOffset = sf::Vector2f(0, 0),
                     ShadowOffset = sf::Vector2f(5, 5),
                     BackOffset = sf::Vector2f(2, 2);

 private:
  bool LoadResource(auto& resource, const std::string& path);
  bool LoadSVG(auto& resource, const std::string& path,
               const sf::Vector2i size);
  bool OpenResource(auto& resource, const std::string& path);

  sf::Texture Shadow, Back, Button,
      Word1, Word2, Word3, Word4, Word5, Word6, Word7, Word8, Word9, Word10,
      Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num10, Pin1, Pin2,
      Pin3, Pin4, Pin5, Pin6, Pin7, Pin8, Pin9, Pin10, One, Two, Three, Four,
      Five, Six, BG;

  const sf::Vector2i CardSize = sf::Vector2i(90, 120),
                     ShadowSize = sf::Vector2i(96, 126),
                     ImageSize = sf::Vector2i(69, 92),
                     ButtonSize = sf::Vector2i(90, 180);
};