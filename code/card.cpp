#include "card.h"

Card::Card(sf::RenderWindow* window, AssetManager* manager,
           const CardTypes type)
    : Shadow(manager->Empty),
      Back(manager->Empty),
      Selected(manager->Empty),
      Face(manager->Empty) {
  Window = window;
  Type = type;

  ImageOffset = manager->ImageOffset;

  Shadow.setTexture(*manager->GetCardShadow());
  Back.setTexture(*manager->GetCardBack());
  Back.setColor(sf::Color(230, 230, 230, 255));
  Selected.setTexture(*manager->GetCardSelected());
  Selected.setColor(sf::Color(255, 255, 255, 0));
  Face.setTexture(*manager->GetCard(Type));
}

CardTypes Card::GetType() { return Type; }

bool Card::Tick(const bool reachable, const bool click) {
  bool result = false;
  if (reachable && IsMouseOnCard()) {
    if (State == CardStates::Idle) {
      ChangeState(CardStates::Highlighted);
    }
    if (click) {
      if (State != CardStates::Selected) {
        result = true;
        ChangeState(CardStates::Selected);
      }
    }
  }
  Window->draw(Shadow);
  Window->draw(Back);
  Window->draw(Selected);
  Window->draw(Face);
  if (State == CardStates::Highlighted) {
    ChangeState(CardStates::Idle);
  }
  return result;
}

void Card::SetLocation(const float x, const float y) {
  Shadow.setPosition(sf::Vector2f(x + ShadowOffsetX, y + ShadowOffsetY));
  Back.setPosition(sf::Vector2f(x, y));
  Selected.setPosition(sf::Vector2f(x, y));
  Face.setPosition(sf::Vector2f(x + ImageOffset.x, y + ImageOffset.y));
}

void Card::ChangeType(const CardTypes type, AssetManager* manager) {
  Type = type;
  Face.setTexture(*manager->GetCard(Type));
  ChangeState(CardStates::Idle);
}

void Card::ChangeState(CardStates state) {
  switch (State) {
    case CardStates::Selected:
      if (state == CardStates::Highlighted || state == CardStates::Hinted) {
        return;
      }
      break;
    case CardStates::Hinted:
      if (state == CardStates::Highlighted || state == CardStates::Hinted) {
        return;
      }
      break;
  }
  State = state;
  switch (State) {
    case CardStates::Idle:
      Selected.setColor(sf::Color(255, 255, 255, 0));
      break;
    case CardStates::Hinted:
      Selected.setColor(sf::Color(255, 255, 255, HintedAlpha));
      break;
    case CardStates::Selected:
      Selected.setColor(sf::Color(255, 255, 255, SelectedAlpha));
      break;
    case CardStates::Highlighted:
      Selected.setColor(sf::Color(255, 255, 255, HighlightedAlpha));
      break;
  }
}

bool Card::IsMouseOnCard() {
  sf::Vector2i mouse = sf::Mouse::getPosition();

  if (Back.getGlobalBounds().contains(sf::Vector2f(mouse.x, mouse.y))) {
    return true;
  }
  return false;
}