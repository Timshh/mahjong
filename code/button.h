#pragma once
#include "actor.h"
#include "observer.h"
#include "assetManager.h"

class Button : public Actor {
 public:
  Button(sf::RenderWindow* window, Observer* overseer, AssetManager* manager,
         const TextElement type,
         const float x, const float y);
  ~Button();

  void ResetScales(const sf::Vector2f offset, const float mult) override;
  void ChangeLanguage() override;
  bool Tick();

 private:
  bool IsMouseOnButton();

  Observer* Overseer;
  TextElement Type;
  AssetManager* Manager;
  bool Pressed = false, Overlap = false;
  sf::Vector2i Position;
  sf::Text ButtonText;
  sf::Sprite Back;
};