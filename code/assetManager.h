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
  sf::Texture* GetCardOutline();
  sf::Texture* GetCardBack();
  sf::Texture* GetCardSelected();
  sf::Texture* GetCard(const CardTypes type);
  sf::Texture* GetButton();
  sf::Texture* GetButtonSelected();

  sf::Font MainFont;
  sf::Texture Empty;

  const sf::Vector2i ImageOffset = sf::Vector2i(5, 7),
                     OutlineOffset = sf::Vector2i(-1, -1);

 private:
  bool LoadResource(auto& resource, const std::string& path);
  bool LoadSVG(auto& resource, const std::string& path,
               const sf::Vector2i size);
  bool OpenResource(auto& resource, const std::string& path);

  sf::Texture Shadow, Outline, Back, Selected, Button, ButtonSelected, Word1,
      Word2, Word3, Word4, Word5, Word6, Word7, Word8, Word9, Word10, Num1,
      Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num10, Pin1, Pin2, Pin3,
      Pin4, Pin5, Pin6, Pin7, Pin8, Pin9, Pin10, One, Two, Three, Four, Five,
      Six, BG;

  const sf::Vector2i CardSize = sf::Vector2i(90, 120),
                     OutlineSize = sf::Vector2i(92, 122),
                     ImageSize = sf::Vector2i(80, 106),
                     ButtonSize = sf::Vector2i(90, 120);
};