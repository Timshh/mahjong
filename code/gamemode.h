#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "gameField.h"
#include "button.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window);
  void Tick();

 private:
  sf::RenderWindow* Window;

  GamemodeStates State = GamemodeStates::Preparing;
  AssetManager Manager;
  Button RestartButton;
  std::unique_ptr<GameField> Field;
};