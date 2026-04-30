#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "gameField.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window);
  void Tick();

 private:
  sf::RenderWindow* Window;

  GamemodeStates State = GamemodeStates::Preparing;
  AssetManager Manager;
  std::unique_ptr<GameField> Field;
  bool CanRestart = true;
};