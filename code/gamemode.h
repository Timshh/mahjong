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

  void DrawBG(const float deltatime);

  sf::Vector2f OffsetMain = sf::Vector2f(0, 0), OffsetSub = sf::Vector2f(0, 0);
  sf::Sprite BGMain, BGSub;
  sf::Clock Time;
  GamemodeStates State = GamemodeStates::Preparing;
  AssetManager Manager;
  Button RestartButton;
  std::unique_ptr<GameField> Field;
};