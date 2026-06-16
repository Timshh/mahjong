#pragma once
#include <lunasvg.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "actor.h"
#include "data.h"

class AssetManager {
 public:
  AssetManager(const sf::Vector2i windowSize);

  sf::Texture* GetBG();
  sf::Texture* GetVignette();
  sf::Texture* GetCardShadow();
  sf::Texture* GetCardShade();
  sf::Texture* GetCardBack();
  sf::Texture* GetCard(const CardTypes type);
  sf::Texture* GetButton();
  std::u8string GetText(const TextElement elem);
  void SizeChanged(const sf::Vector2f offset, const float mult,
                   const sf::Vector2i windowSize);
  void SwapLanguage();

  sf::Font MainFont;
  sf::Texture Empty;

  const sf::Vector2f ImageOffset = sf::Vector2f(10.5, 14),
                     EdgeOffset = sf::Vector2f(0, 0),
                     ShadowOffset = sf::Vector2f(5, 5),
                     ShadeOffset = sf::Vector2f(-16, -8),
                     BackOffset = sf::Vector2f(2, 2);

 private:
  bool LoadResource(auto& resource, const std::string& path);
  bool LoadSVG(auto& resource, const std::string& path,
               const sf::Vector2i size);
  bool OpenResource(auto& resource, const std::string& path);
  bool RenderResources(const sf::Vector2i windowSize);

  float Mult = 1;
  Language Lang = Language::Russian;
  LanguageSet CurrentLanguage = Languages[Language::Russian];
  std::map<CardTypes, sf::Texture> FaceTextures;
  sf::Texture Vignette, Shadow, Shade, Back, Button, BG;

  const sf::Vector2i CardSize = sf::Vector2i(90, 120),
                     ShadowSize = sf::Vector2i(96, 126),
                     ShadeSize = sf::Vector2i(110, 138),
                     ImageSize = sf::Vector2i(69, 92),
                     ButtonSize = sf::Vector2i(90, 180);
};