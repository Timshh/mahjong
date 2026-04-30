#pragma once
#include <SFML/Graphics.hpp>

#include "assetManager.h"
#include "card.h"
#include "data.h"

class GameField {
 public:
  GameField(sf::RenderWindow* window, AssetManager* manager);

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

  sf::Text PairsText, TipText;
  sf::Vector3i SelectedCoords;
  FieldStates State = FieldStates::Idle;
  bool CanClick = true, CanRefresh = true, CanHint = true;
  int Pairs = 0;

  const float CardSizeX = 85, CardSizeY = 140, FieldOffsetX = 700,
              FieldOffsetY = 120;
  const int FieldHeight = 5, FieldWidth = 6, CardOffsetZ = 5;
};