#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "data.h"

class Card {
 public:
  Card(sf::RenderWindow* window, AssetManager* manager, const CardTypes type);

  CardTypes GetType();
  bool Tick(const bool reachable, const bool click);
  void SetLocation(const float x, const float y);
  void ChangeType(const CardTypes type, AssetManager* manager);
  void ChangeState(const CardStates state);

 private:
  sf::RenderWindow* Window;

  bool IsMouseOnCard();
  CardStates State = CardStates::Idle;
  CardTypes Type;
  sf::Sprite Shadow, Outline, Back, Selected, Face;
  const float HighlightedAlpha = 32, SelectedAlpha = 64,
              HintedAlpha = 128, ShadowOffsetY = 5, ShadowOffsetX = 5;
  sf::Vector2i ImageOffset, OutlineOffset;
};