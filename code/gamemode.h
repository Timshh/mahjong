#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "button.h"
#include "observer.h"
#include "forms.h"
#include "gameField.h"

class Gamemode {
 public:
  Gamemode(sf::RenderWindow* window);
  void Tick();
  void Resize();

 private:
  sf::RenderWindow* Window;

  void DrawBG();
  bool CanEscape = true;
  float TimeDelta = 0;

  Observer Overseer;
  sf::Text NameText;
  sf::Vector2f OffsetMain = sf::Vector2f(0, 0), OffsetSub = sf::Vector2f(0, 0);
  sf::Sprite BG, Vignette;
  sf::Clock Time;
  AssetManager Manager;
  GameStates State = GameStates::Pause;
  Button PauseButton, TurtleButton, WaveButton, ResumeButton, QuitButton,
      LangButton;
  std::unique_ptr<GameField> Field;
};