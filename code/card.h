#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "data.h"

class Card : public Actor {
 public:
  Card(sf::RenderWindow* window, AssetManager* manager, const CardTypes type);
  ~Card();

  CardTypes GetType();
  void ResetScales(const sf::Vector2f offset, const float mult) override;
  bool Tick(const bool reachable, const bool click);
  void SetLocation(const float x, const float y, const sf::Vector2i coords);
  void ChangeType(const CardTypes type, AssetManager* manager);
  void ChangeState(const CardStates state);
  sf::Vector2i Coords;

 private:
  bool IsMouseOnCard();

  int PosX = 0, PosY = 0;
  AssetManager* Manager;
  CardStates State = CardStates::Idle;
  CardTypes Type;
  sf::Sprite Edge, Shadow, Back, Face;
  sf::Vector2f ImageOffset, EdgeOffset, BackOffset, ShadowOffset;
};