#include "gameField.h"

GameField::GameField(sf::RenderWindow* window, AssetManager* manager)
    : PairsText(manager->MainFont, "", 40),
      HintButton(window, manager, "Hint", 300, 350),
      RefreshButton(window, manager, "Refresh", 300, 450){
  Window = window;
  Manager = manager;
  GenerateField();
  CheckPairs();
  PairsText.setPosition(sf::Vector2f(320, 250));
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

    sf::Vector2i mouseCoord = sf::Mouse::getPosition(*Window);
    sf::Vector2i selectedCoord =
        sf::Vector2i((mouseCoord.y - FieldOffsetY) / CardSizeY,
                     (mouseCoord.x - FieldOffsetX) / CardSizeX);

    bool isCardValid = false;
    int currCardZ = 0;
    if (selectedCoord.x < FieldWidth && selectedCoord.x >= 0 &&
        selectedCoord.y < FieldWidth && selectedCoord.y >= 0) {
      for (int z = 0; z < Cards.size(); ++z) {
        if (Cards[z][selectedCoord.x][selectedCoord.y]) {
          if (CheckReachable(z, selectedCoord.x, selectedCoord.y)) {
            isCardValid = true;
            currCardZ = z;
          }
        }
      }
    }

    if (isCardValid) {
      Cards[currCardZ][selectedCoord.x][selectedCoord.y]->ChangeState(
          CardStates::Highlighted);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (CanClick) {
        Click(currCardZ, selectedCoord.x, selectedCoord.y, isCardValid);
        if (Cards.empty()) {
          State = FieldStates::Finished;
        }
        CanClick = false;
      }
    } else {
      CanClick = true;
    }
  } else {
    RefreshButton.Tick();
    HintButton.Tick();
  }

  TickDraw();
}

void GameField::TickDraw() {
  for (int z = 0; z < Cards.size(); ++z) {
    for (int y = 0; y < Cards[z].size(); ++y) {
      for (Card* card : Cards[z][y]) {
        if (card) {
          card->Tick();
        }
      }
    }
  }
  PairsText.setString("Pairs: " + std::to_string(Pairs));
  Window->draw(PairsText);
}

void GameField::Click(int cardZ, int cardX, int cardY, bool isNewValid) {
  if (SelectedCard) {
    if (isNewValid) {
      if (SelectedCard == Cards[cardZ][cardX][cardY]) {
        return;
      }
      if (SelectedCard->GetType() == Cards[cardZ][cardX][cardY]->GetType()) {
        delete SelectedCard;
        delete Cards[cardZ][cardX][cardY];

        Cards[cardZ][cardX][cardY] = nullptr;
        Cards[SelectedCoords.x][SelectedCoords.y][SelectedCoords.z] = nullptr;

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
          if (CheckReachable(z, y, x)) {
            pairVector[static_cast<int>(Cards[z][y][x]->GetType())] += 1;
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

  if (cardY < FieldWidth - 1) {
    if (Cards[cardZ][cardX][cardY + 1]) {
      xMinus = true;
    }
  }

  if (cardY > 0) {
    if (Cards[cardZ][cardX][cardY - 1]) {
      xPlus = true;
    }
  }

  if (xPlus && xMinus) {
    reachable = false;
  }

  for (int z = cardZ + 1; z < Cards.size(); z++) {
    if (z < Cards.size()) {
      if (Cards[z][cardX][cardY]) {
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
          refreshBuffer.push_back(Cards[z][y][x]);
          refreshBufferIDs.push_back(sf::Vector3i(z, y, x));
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
            if (CheckReachable(z, y, x)) {
              checkList.push_back(Cards[z][y][x]);
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
  std::vector<sf::Vector3f> coords;
  Cards.resize(FieldHeight);
  for (int z = 0; z < Cards.size(); ++z) {
    Cards[z].resize(FieldWidth);
    for (int x = 0; x < Cards[z].size(); ++x) {
      Cards[z][x].resize(FieldWidth);
      for (int y = 0; y < Cards[z][x].size(); ++y) {
        coords.push_back(sf::Vector3f(x, y, z));
      }
    }
  }
  while (!coords.empty()) {
    CardTypes currType =
        static_cast<CardTypes>(rand() % static_cast<int>(CardTypes::COUNT));
    for (int i = 0; i <= 1; i++) {
      int id = rand() % coords.size();
      sf::Vector3f currCoord = coords[id];
      Cards[currCoord.z][currCoord.y][currCoord.x] =
          new Card(Window, Manager, currType);
      Cards[currCoord.z][currCoord.y][currCoord.x]->SetLocation(
          currCoord.x * CardSizeX + FieldOffsetX - currCoord.z * CardOffsetZX +
              OffsetX,
          currCoord.y * CardSizeY + FieldOffsetY - currCoord.z * CardOffsetZY +
              OffsetY);
      coords.erase(coords.begin() + id);
    }
  }
}
