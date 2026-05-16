#include "gameField.h"

GameField::GameField(sf::RenderWindow* window, AssetManager* manager)
    : PairsText(manager->MainFont, "", 40),
      HintButton(window, manager, "Hint", 50, 240),
      RefreshButton(window, manager, "Refresh", 50, 340) {
  Window = window;
  Manager = manager;
  GenerateField();
  CheckPairs();
  PairsText.setPosition(sf::Vector2f(60, 155));
  PairsText.setFillColor(sf::Color::Black);
}

void GameField::Tick() {
  if (State == FieldStates::Idle) {
    if (RefreshButton.Tick()) {
      Refresh();
    }

    if (HintButton.Tick()) {
      Hint();
    }

    Clicked = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (CanClick) {
        Clicked = true;
        CanClick = false;
      }
    } else {
      CanClick = true;
    }

    for (int z = 0; z < Cards.size(); ++z) {
      for (int x = 0; x < FieldWidth; ++x) {
        for (int y = 0; y < FieldWidth; ++y) {
          if (Cards[z][y][x]) {
            if (Cards[z][y][x]->Coords == sf::Vector2i(x, y)) {
              if (Cards[z][y][x]->Tick(CheckReachable(z, y, x), Clicked)) {
                Click(z, y, x, true);
                Clicked = false;
              }
            }
          }
        }
      }
    }
    if (Clicked) {
      Click(0, 0, 0, false);
    }
  } else {
    RefreshButton.Tick();
    HintButton.Tick();
  }

  TickDraw();
}

void GameField::TickDraw() {
  PairsText.setString("Pairs: " + std::to_string(Pairs));
  Window->draw(PairsText);
}

void GameField::Click(const int cardZ, const int cardX, const int cardY,
                      const bool isNewValid) {
  if (SelectedCard) {
    if (isNewValid) {
      if (SelectedCard == Cards[cardZ][cardX][cardY]) {
        return;
      }
      if (SelectedCard->GetType() == Cards[cardZ][cardX][cardY]->GetType()) {
        delete SelectedCard;
        delete Cards[cardZ][cardX][cardY];

        Cards[cardZ][cardX][cardY] = Cards[cardZ][cardX + 1][cardY] =
            Cards[cardZ][cardX][cardY + 1] =
                Cards[cardZ][cardX + 1][cardY + 1] = nullptr;
        Cards[SelectedCoords.x][SelectedCoords.y][SelectedCoords.z] =
            Cards[SelectedCoords.x][SelectedCoords.y + 1][SelectedCoords.z] =
                Cards[SelectedCoords.x][SelectedCoords.y]
                     [SelectedCoords.z + 1] =
                         Cards[SelectedCoords.x][SelectedCoords.y + 1]
                              [SelectedCoords.z + 1] = nullptr;

        SelectedCard = nullptr;
        CheckPairs();
      } else {
        SelectedCard->ChangeState(CardStates::Idle);
        SelectedCard = Cards[cardZ][cardX][cardY];
        SelectedCoords = sf::Vector3i(cardZ, cardX, cardY);
        SelectedCard->ChangeState(CardStates::Selected);
      }
    } else {
      SelectedCard->ChangeState(CardStates::Idle);
      SelectedCard = nullptr;
    }
  } else {
    if (isNewValid) {
      SelectedCard = Cards[cardZ][cardX][cardY];
      SelectedCoords = sf::Vector3i(cardZ, cardX, cardY);
      SelectedCard->ChangeState(CardStates::Selected);
    }
  }
}

void GameField::CheckPairs() {
  Pairs = 0;
  std::vector<int> pairVector;
  pairVector.resize(static_cast<int>(CardTypes::COUNT));
  for (int z = 0; z < Cards.size(); ++z) {
    for (int y = 0; y < Cards[z].size(); ++y) {
      for (int x = 0; x < Cards[z][y].size(); ++x) {
        if (Cards[z][y][x]) {
          if (Cards[z][y][x]->Coords == sf::Vector2i(x, y)) {
            if (CheckReachable(z, y, x)) {
              pairVector[static_cast<int>(Cards[z][y][x]->GetType())] += 1;
            }
          }
        }
      }
    }
  }
  for (int i : pairVector) {
    Pairs += i / 2;
  }
}

bool GameField::CheckReachable(int cardZ, int cardX, int cardY) {
  bool reachable = true;
  bool xMinus = false, xPlus = false;

  if (cardY < FieldWidth - 2) {
    if (Cards[cardZ][cardX][cardY + 2]) {
      xMinus = true;
    }
    if (Cards[cardZ][cardX + 1][cardY + 2]) {
      xMinus = true;
    }
  }

  if (cardY > 0) {
    if (Cards[cardZ][cardX][cardY - 1]) {
      xPlus = true;
    }
    if (Cards[cardZ][cardX + 1][cardY - 1]) {
      xPlus = true;
    }
  }

  if (xPlus && xMinus) {
    reachable = false;
  }

  for (int z = cardZ + 1; z < Cards.size(); z++) {
    if (z < Cards.size()) {
      if (Cards[z][cardX][cardY] || Cards[z][cardX + 1][cardY] ||
          Cards[z][cardX][cardY + 1] || Cards[z][cardX + 1][cardY + 1]) {
        reachable = false;
      }
    }
  }

  return reachable;
}

void GameField::Refresh() {
  std::vector<Card*> refreshBuffer;
  std::vector<sf::Vector3i> refreshBufferIDs;
  for (int z = 0; z < Cards.size(); ++z) {
    for (int y = 0; y < Cards[z].size(); ++y) {
      for (int x = 0; x < Cards[z][y].size(); ++x) {
        if (Cards[z][y][x]) {
          if (Cards[z][y][x]->Coords == sf::Vector2i(x, y)) {
            refreshBuffer.push_back(Cards[z][y][x]);
            refreshBufferIDs.push_back(sf::Vector3i(z, y, x));
          }
        }
      }
    }
  }
  while (refreshBuffer.size() > 1) {
    int changeID = rand() % (refreshBuffer.size() - 1) + 1;
    CardTypes typeBuffer = refreshBuffer[0]->GetType();

    // Swap locations
    refreshBuffer[0]->ChangeType(refreshBuffer[changeID]->GetType(), Manager);
    refreshBuffer[changeID]->ChangeType(typeBuffer, Manager);

    refreshBuffer.erase(refreshBuffer.begin());
    refreshBufferIDs.erase(refreshBufferIDs.begin());
  }
  CheckPairs();
}

void GameField::Hint() {
  if (Pairs != 0) {
    std::vector<Card*> checkList;
    for (int z = 0; z < Cards.size(); ++z) {
      for (int y = 0; y < Cards[z].size(); ++y) {
        for (int x = 0; x < Cards[z][y].size(); ++x) {
          if (Cards[z][y][x]) {
            if (Cards[z][y][x]->Coords == sf::Vector2i(x, y)) {
              if (CheckReachable(z, y, x)) {
                checkList.push_back(Cards[z][y][x]);
              }
            }
          }
        }
      }
    }
    while (checkList.size() > 1) {
      for (int i = 1; i < checkList.size(); ++i) {
        if (checkList[0]->GetType() == checkList[i]->GetType()) {
          checkList[0]->ChangeState(CardStates::Hinted);
          checkList[i]->ChangeState(CardStates::Hinted);
          return;
        }
      }
      checkList.erase(checkList.begin());
    }
  }
}

void GameField::GenerateField() {
  std::vector<sf::Vector3i> coords;
  Cards.resize(FieldHeight);
  for (int z = 0; z < Cards.size(); ++z) {
    Cards[z].resize(FieldWidth);
    for (int x = 0; x < Cards[z].size(); ++x) {
      Cards[z][x].resize(FieldWidth);
    }
  }
  coords = FormMahjongTurtle;
  // Generator
  /* for (int z = 0; z < Cards.size(); ++z) {
    for (int x = 0; x < Cards[z].size(); ++x) {
      if (x % 4 > 1) {
        for (int y = 0; y < Cards[z][x].size() - 1; ++y) {
          if (y % 2 == 0 && x % 2 == 0 && x < Cards[z].size() - 1) {
            coords.push_back(sf::Vector3f(x, y, z));
          }
        }
      } else {
        for (int y = 1; y < Cards[z][x].size() - 1; ++y) {
          if (y % 2 == 1 && x % 2 == 0 && x < Cards[z].size() - 1) {
            coords.push_back(sf::Vector3f(x, y, z));
          }
        }
      }
    }
  }*/

  while (coords.size() >= 2) {
    CardTypes currType =
        static_cast<CardTypes>(rand() % static_cast<int>(CardTypes::COUNT));
    for (int i = 0; i <= 1; i++) {
      int id = rand() % coords.size();
      sf::Vector3i currCoord = coords[id];
      Cards[currCoord.z][currCoord.y][currCoord.x] =
          new Card(Window, Manager, currType);
      Cards[currCoord.z][currCoord.y][currCoord.x]->SetLocation(
          currCoord.x * CardSizeX + FieldOffsetX - currCoord.z * CardOffsetZX +
              OffsetX,
          currCoord.y * CardSizeY + FieldOffsetY - currCoord.z * CardOffsetZY +
              OffsetY,
          sf::Vector2i(currCoord.x, currCoord.y));
      Cards[currCoord.z][currCoord.y + 1][currCoord.x] =
          Cards[currCoord.z][currCoord.y][currCoord.x + 1] =
              Cards[currCoord.z][currCoord.y + 1][currCoord.x + 1] =
                  Cards[currCoord.z][currCoord.y][currCoord.x];
      coords.erase(coords.begin() + id);
    }
  }
}
