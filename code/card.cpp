#include "card.h"

Card::Card(sf::RenderWindow* window, Observer* overseer, AssetManager* manager,
           const CardTypes type)
    : Actor(window),
      Manager(manager),
      Type(type),
      Overseer(overseer),
      Shadow(*manager->GetCardShadow()),
      Shade(*manager->GetCardShade()),
      Edge(*manager->GetCardShadow()),
      Back(*manager->GetCardBack()),
      Face(*manager->GetCard(type)) {
  Overseer->AddSubscriber(this);

  Back.setColor(NormalColor);
  Edge.setColor(sf::Color(150, 150, 150, 255));
  Shadow.setColor(sf::Color(50, 50, 50, 255));
  Shade.setColor(sf::Color(20, 20, 20, 105));

  ImageOffset = manager->ImageOffset;
  ShadowOffset = manager->ShadowOffset;
  ShadeOffset = manager->ShadeOffset;
  EdgeOffset = manager->EdgeOffset;
  BackOffset = manager->BackOffset;
}

Card::~Card() { Overseer->RemoveSubscriber(this); }

CardTypes Card::GetType() { return Type; }

void Card::ResetScales(const sf::Vector2f offset, const float mult) {
  if (PosX == 0 && PosY == 0) {
    return;
  }
  Back.setPosition(sf::Vector2f((PosX + BackOffset.x) * mult + offset.x,
                                (PosY + BackOffset.y) * mult + offset.y));
  Edge.setPosition(sf::Vector2f((PosX + EdgeOffset.x) * mult + offset.x,
                                (PosY + EdgeOffset.y) * mult + offset.y));
  Face.setPosition(sf::Vector2f((PosX + ImageOffset.x) * mult + offset.x,
                                (PosY + ImageOffset.y) * mult + offset.y));
  Shadow.setPosition(sf::Vector2f((PosX + ShadowOffset.x) * mult + offset.x,
                                  (PosY + ShadowOffset.y) * mult + offset.y));
  Shade.setPosition(sf::Vector2f((PosX + ShadeOffset.x) * mult + offset.x,
                                 (PosY + ShadeOffset.y) * mult + offset.y));

  Shadow.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager->GetCardShadow()->getSize())));
  Shade.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager->GetCardShade()->getSize())));
  Edge.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager->GetCardShadow()->getSize())));
  Back.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager->GetCardBack()->getSize())));
  Face.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager->GetCard(Type)->getSize())));
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
  if (State == CardStates::Highlighted) {
    ChangeState(CardStates::Idle);
  }
  return result;
}

void Card::Draw() {
  Window->draw(Shadow);
  Window->draw(Edge);
  Window->draw(Back);
  Window->draw(Face);
}

void Card::ShadeTick() { Window->draw(Shade); }

void Card::SetLocation(const float x, const float y,
                       const sf::Vector2i coords) {
  PosX = x;
  PosY = y;
  Coords = coords;
  int mult = std::min(Window->getSize().x / 16, Window->getSize().y / 9);
  ResetScales(sf::Vector2f((Window->getSize().x - mult * 16) / 2,
                           (Window->getSize().y - mult * 9) / 2),
              mult / 120.);
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
      Back.setColor(NormalColor);
      break;
    case CardStates::Hinted:
      Back.setColor(HintedColor);
      break;
    case CardStates::Selected:
      Back.setColor(SelectedColor);
      break;
    case CardStates::Highlighted:
      Back.setColor(HighlightedColor);
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