#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "data.h"

class Card : public Actor {
 public:
  Card(sf::RenderWindow* window, AssetManager* manager, const CardTypes type);
  ~Card();

  CardTypes GetType();
  void ResetScales(const sf::Vector2f deltaSize) override;
  bool Tick(const bool reachable, const bool click);
  void SetLocation(const float x, const float y, const sf::Vector2i coords,
                   const sf::Color heightColor);
  void ChangeType(const CardTypes type, AssetManager* manager);
  void ChangeState(const CardStates state);
  sf::Vector2i Coords;

 private:
  bool IsMouseOnCard();

  AssetManager* Manager;
  CardStates State = CardStates::Idle;
  CardTypes Type;
  sf::Sprite Edge, Shadow, Back, Face;
  sf::Vector2f ImageOffset, EdgeOffset, BackOffset, ShadowOffset;
  sf::Color HeightColor;
};