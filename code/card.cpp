#include "card.h"

Card::Card(sf::RenderWindow* window, AssetManager* manager,
           const CardTypes type)
    : Shadow(*manager->GetCardShadow()),
      Edge(*manager->GetCardShadow()),
      Back(*manager->GetCardBack()),
      Face(*manager->GetCard(type)) {
  Window = window;
  Type = type;

  ImageOffset = manager->ImageOffset;
  ShadowOffset = manager->ShadowOffset;
  EdgeOffset = manager->EdgeOffset;
  BackOffset = manager->BackOffset;
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
  Window->draw(Edge);
  Window->draw(Back);
  Window->draw(Face);
  if (State == CardStates::Highlighted) {
    ChangeState(CardStates::Idle);
  }
  return result;
}

void Card::SetLocation(const float x, const float y, const sf::Vector2i coords,
                       const sf::Color heightColor) {
  HeightColor = heightColor;
  Coords = coords;

  Edge.setPosition(sf::Vector2f(x + EdgeOffset.x, y + EdgeOffset.y));
  Shadow.setPosition(sf::Vector2f(x + ShadowOffset.x, y + ShadowOffset.y));
  Back.setPosition(sf::Vector2f(x + BackOffset.x, y + BackOffset.x));
  Face.setPosition(sf::Vector2f(x + ImageOffset.x + BackOffset.x,
                                y + ImageOffset.y + BackOffset.y));

  Face.setColor(HeightColor);
  Back.setColor(NormalColor * HeightColor);
  Edge.setColor(sf::Color(150, 150, 150, 255) * HeightColor);
  Shadow.setColor(sf::Color(50, 50, 50, 255) * HeightColor);
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
      Back.setColor(NormalColor * HeightColor);
      break;
    case CardStates::Hinted:
      Back.setColor(HintedColor * HeightColor);
      break;
    case CardStates::Selected:
      Back.setColor(SelectedColor * HeightColor);
      break;
    case CardStates::Highlighted:
      Back.setColor(HighlightedColor * HeightColor);
      break;
  }
}

bool Card::IsMouseOnCard() {
  if (!Window->hasFocus()) {
    return false;
  }

  sf::Vector2i mouse = sf::Mouse::getPosition();

  if (Back.getGlobalBounds().contains(sf::Vector2f(mouse.x, mouse.y))) {
    return true;
  }
  return false;
}