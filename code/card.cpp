#include "card.h"

Card::Card(sf::RenderWindow* window, AssetManager* manager,
           const CardTypes type)
    : Actor(window),
      Shadow(*manager->GetCardShadow()),
      Edge(*manager->GetCardShadow()),
      Back(*manager->GetCardBack()),
      Face(*manager->GetCard(type)) {
  Manager = manager;
  Manager->AddSubscriber(this);
  Type = type;

  ImageOffset = manager->ImageOffset;
  ShadowOffset = manager->ShadowOffset;
  EdgeOffset = manager->EdgeOffset;
  BackOffset = manager->BackOffset;
}

Card::~Card() { Manager->RemoveSubscriber(this); }

CardTypes Card::GetType() { return Type; }

void Card::ResetScales(const sf::Vector2f deltaSize) {
  Back.setPosition(sf::Vector2f(Back.getPosition().x * deltaSize.x,
                                Back.getPosition().y * deltaSize.y));
  Back.setScale(sf::Vector2f(Back.getScale().x * deltaSize.x,
                             Back.getScale().y * deltaSize.y));
  Edge.setPosition(sf::Vector2f(Edge.getPosition().x * deltaSize.x,
                                Edge.getPosition().y * deltaSize.y));
  Edge.setScale(sf::Vector2f(Edge.getScale().x * deltaSize.x,
                             Edge.getScale().y * deltaSize.y));
  Face.setPosition(sf::Vector2f(Face.getPosition().x * deltaSize.x,
                                Face.getPosition().y * deltaSize.y));
  Face.setScale(sf::Vector2f(Face.getScale().x * deltaSize.x,
                             Face.getScale().y * deltaSize.y));
  Shadow.setPosition(sf::Vector2f(Shadow.getPosition().x * deltaSize.x,
                                  Shadow.getPosition().y * deltaSize.y));
  Shadow.setScale(sf::Vector2f(Shadow.getScale().x * deltaSize.x,
                               Shadow.getScale().y * deltaSize.y));
}

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

  ResetScales(
      sf::Vector2f(Window->getSize().x / 1920., Window->getSize().y / 1080.));
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

  sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*Window));

  if (Back.getGlobalBounds().contains(sf::Vector2f(mouse.x, mouse.y))) {
    return true;
  }
  return false;
}