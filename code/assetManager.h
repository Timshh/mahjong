#pragma once
#include <lunasvg.h>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#include "data.h"

class AssetManager {
 public:
  AssetManager(const sf::Vector2i windowSize);

  sf::Texture* GetBG();
  sf::Texture* GetVignette();
  sf::Texture* GetCardShade();
  sf::Texture* GetCardBack();
  sf::SoundBuffer* GetCardHighlightSound();
  sf::SoundBuffer* GetButtonHighlightSound();
  sf::SoundBuffer* GetDestroySound();
  sf::SoundBuffer* GetButtonClickSound();
  sf::SoundBuffer* GetCardClickSound();
  sf::SoundBuffer* GetWinSound();
  sf::Texture* GetCard(const CardTypes type);
  sf::Texture* GetButton();
  std::u8string GetText(const TextElement elem);
  void SizeChanged(const sf::Vector2f offset, const float mult,
                   const sf::Vector2i windowSize);
  void SwapLanguage();

  sf::Font MainFont;
  sf::Texture Empty;

  const sf::Vector2f ImageOffset = sf::Vector2f(10.5, 14),
                     ShadeOffset = sf::Vector2f(-16, -8),
                     BackOffset = sf::Vector2f(0, 0);

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
  sf::Texture Vignette, Shade, Back, Button, BG;
  sf::SoundBuffer ButtonHighlightSound, CardHighlightSound, CardSound, WinSound,
      ButtonSound,
      DestroySound;

  const sf::Vector2i CardSize = sf::Vector2i(100, 130),
                     ShadeSize = sf::Vector2i(100, 128),
                     ImageSize = sf::Vector2i(69, 92),
                     ButtonSize = sf::Vector2i(90, 180);
};