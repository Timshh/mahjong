#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "data.h"

class AssetManager {
 public:
  AssetManager();

  sf::Texture* GetBG();
  sf::Texture* GetCardShadow();
  sf::Texture* GetCardBack();
  sf::Texture* GetCardSelected();
  sf::Texture* GetCard(const CardTypes type);

  sf::Font MainFont;
  sf::Texture Empty;

 private:
  bool LoadResource(auto& resource, const std::string& path);
  bool OpenResource(auto& resource, const std::string& path);

  sf::Texture Shadow, Back, Selected, Word1, Word2, Word3, Word4, Word5, Word6,
      Word7, Word8, Word9, Word10, Num1, Num2, Num3, Num4, Num5, Num6, Num7,
      Num8, Num9, Num10, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8, Pin9,
      Pin10, One, Two, Three, Four, Five, Six, BG;
};