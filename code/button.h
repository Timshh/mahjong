#pragma once
#include "actor.h"
#include "assetManager.h"

class Button : public Actor {
 public:
  Button(sf::RenderWindow* window, AssetManager* manager,
         const std::string text, const float x, const float y);

  void ResetScales(const sf::Vector2f deltaSize) override;
  void ChangeLanguage() override;
  bool Tick();

 private:
  bool IsMouseOnButton();

  AssetManager* Manager;
  bool Pressed = false, Overlap = false;
  sf::Vector2i Position;
  sf::Text ButtonText;
  sf::Sprite Back;
};