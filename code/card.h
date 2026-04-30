#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "data.h"

class Card {
 public:
  Card(sf::RenderWindow* window, AssetManager* manager, const CardTypes type);

  CardTypes GetType();
  void Tick();
  void SetLocation(const float x, const float y);
  void ChangeType(const CardTypes type, AssetManager* manager);
  void ChangeState(const CardStates state);

 private:
  sf::RenderWindow* Window;

  CardStates State = CardStates::Idle;
  CardTypes Type;
  sf::Sprite Shadow, Back, Selected, Face;
  const float CardSize = 0.125, HighlightedAlpha = 32, SelectedAlpha = 64,
              HintedAlpha = 128, ShadowOffset = 5;
};