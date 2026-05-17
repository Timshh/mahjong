#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "card.h"
#include "data.h"
#include "forms.h"
#include "button.h"

class GameField {
 public:
  GameField(sf::RenderWindow* const window, AssetManager* const manager, const MahjongForms form);

  void Tick();
  void TickDraw();
  void Click(int cardZ, int cardX, int cardY, bool isNewValid);
  void CheckPairs();
  bool CheckReachable(int cardZ, int cardX, int cardY);
  void Refresh();
  void Hint();

 private:
  sf::RenderWindow* Window;
  AssetManager* Manager;
  std::vector<std::vector<std::vector<Card*>>> Cards;
  Card* SelectedCard = nullptr;

  void GenerateField();
  
  sf::Text PairsText;
  sf::Vector3i SelectedCoords;
  Button RefreshButton, HintButton;
  FieldStates State = FieldStates::Idle;
  bool CanClick = true, Clicked = false;
  int Pairs = 0;
  MahjongForms Form;

  const float CardSizeX = 92/2, CardSizeY = 122/2, OffsetY = 40, OffsetX = 10,
              CardOffsetZY = 19 / 2, CardOffsetZX = 19 / 2;
  float FieldOffsetX = 250, FieldOffsetY = 0; 
  int FieldHeight, FieldWidth;
};