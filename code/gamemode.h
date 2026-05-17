#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "button.h"
#include "forms.h"
#include "gameField.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window);
  void Tick();

 private:
  sf::RenderWindow* Window;

  void DrawBG();
  bool CanEscape = true;

  sf::Text NameText;
  sf::Vector2f OffsetMain = sf::Vector2f(0, 0), OffsetSub = sf::Vector2f(0, 0);
  sf::Sprite BG;
  sf::Clock Time;
  AssetManager Manager;
  GameStates State = GameStates::Pause;
  Button PauseButton, TurtleButton, WaveButton, ResumeButton, QuitButton;
  std::unique_ptr<GameField> Field;
};