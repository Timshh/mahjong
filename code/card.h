#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "data.h"

class Card {
 public:
  Card(sf::RenderWindow* window, AssetManager* manager, const CardTypes type);

  CardTypes GetType();
  bool Tick(const bool reachable, const bool click);
  void SetLocation(const float x, const float y, const sf::Vector2i coords);
  void ChangeType(const CardTypes type, AssetManager* manager);
  void ChangeState(const CardStates state);
  sf::Vector2i Coords;

 private:
  sf::RenderWindow* Window;

  bool IsMouseOnCard();
  CardStates State = CardStates::Idle;
  CardTypes Type;
  sf::Sprite Shadow, Outline, ShadowOutline, Back, Selected, Face;
  const float HighlightedAlpha = 32, SelectedAlpha = 64,
              HintedAlpha = 128;
  sf::Vector2f ImageOffset, ShadowOffset, OutlineOffset;
};