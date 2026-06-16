#include "button.h"

Button::Button(sf::RenderWindow* window, Observer* overseer,
               AssetManager* manager,
               const TextElement type, const float x, const float y)
    : Actor(window),
      Back(*manager->GetButton()),
      ButtonText(manager->MainFont, "", 40) {
  Type = type;
  Manager = manager;
  Overseer = overseer;
  Overseer->AddSubscriber(this);
  Back.setColor(NormalColor);

  Back.setColor(sf::Color(230, 230, 230, 255));
  Back.setRotation(sf::degrees(90));

  Back.setScale(sf::Vector2f(1, -1));
  ButtonText.setFillColor(sf::Color::Black);

  Position = sf::Vector2i(x, y);
  float mult = std::min(Window->getSize().x / 16, Window->getSize().y / 9);
  ResetScales(sf::Vector2f((Window->getSize().x - mult * 16) / 2,
                           (Window->getSize().y - mult * 9) / 2),
              mult / 120.);
  ChangeLanguage();
}

Button::~Button() { Overseer->RemoveSubscriber(this); }

void Button::ResetScales(const sf::Vector2f offset, const float mult) {
  Back.setPosition(
      sf::Vector2f(Position.x * mult + offset.x, Position.y * mult + offset.y));
  ButtonText.setPosition(sf::Vector2f((Position.x + 20) * mult + offset.x,
                                      (Position.y + 20) * mult + offset.y));

  ButtonText.setCharacterSize(mult * 40);
  Back.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager->GetButton()->getSize())));
}

void Button::ChangeLanguage() {
  std::u8string name = Manager->GetText(Type);
  ButtonText.setString(sf::String::fromUtf8(name.begin(), name.end()));
}

bool Button::Tick() {
  bool result = false;
  if (IsMouseOnButton()) {
    if (!Overlap) {
      Overlap = true;
      Back.setColor(HighlightedColor);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!Pressed) {
        Pressed = true;
        result = true;
        Back.setColor(SelectedColor);
      }
    } else {
      Pressed = false;
      Back.setColor(HighlightedColor);
    }
  } else {
    if (Overlap) {
      Overlap = false;
      Back.setColor(NormalColor);
    }
  }
  Window->draw(Back);
  Window->draw(ButtonText);

  return result;
}

bool Button::IsMouseOnButton() {
  if (!Window->hasFocus()) {
    return false;
  }

  sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*Window));

  if (Back.getGlobalBounds().contains(mouse)) {
    return true;
  }
  return false;
}