#pragma once

#include "assetManager.h"
#include "observer.h"

class Card : public Actor {
 public:
  Card(sf::RenderWindow* window, Observer* overseer, AssetManager* manager,
       const CardTypes type);
  ~Card();

  CardTypes GetType();
  void ResetScales(const sf::Vector2f offset, const float mult) override;
  bool Tick(const bool reachable, const bool click);
  void Draw();
  void ShadeTick();
  void SetLocation(const float x, const float y, const sf::Vector2i coords);
  void ChangeType(const CardTypes type, AssetManager* manager);
  void ChangeState(const CardStates state);
  sf::Vector2i Coords;

 private:
  bool IsMouseOnCard();

  int PosX = 0, PosY = 0;
  Observer* Overseer;
  AssetManager* Manager;
  CardStates State = CardStates::Idle;
  CardTypes Type;
  sf::Sprite Back, Face, Shade;
  sf::Vector2f ImageOffset, BackOffset, ShadeOffset;
};