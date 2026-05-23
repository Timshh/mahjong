#include "button.h"

Button::Button(sf::RenderWindow* window, AssetManager* manager,
               const std::string text, const float x, const float y)
    : Actor(window), Back(*manager->GetButton()),
      ButtonText(manager->MainFont, text, 40) {

  Manager = manager;
  Manager->AddSubscriber(this);
  Back.setColor(NormalColor); 

  Back.setColor(sf::Color(230, 230, 230, 255));
  Back.setRotation(sf::degrees(90));

  Back.setScale(sf::Vector2f(1, -1));
  ButtonText.setFillColor(sf::Color::Black);

  Position = sf::Vector2i(x, y);
  Back.setPosition(
      sf::Vector2f(Position.x, Position.y));
  ButtonText.setPosition(sf::Vector2f(Position.x + 20,
                                      Position.y + 20));
}

void Button::ResetScales(const sf::Vector2f deltaSize) {
  Back.setPosition(sf::Vector2f(Back.getPosition().x * deltaSize.x,
                                Back.getPosition().y * deltaSize.y));
  ButtonText.setPosition(
      sf::Vector2f(ButtonText.getPosition().x * deltaSize.x,
                   ButtonText.getPosition().y * deltaSize.y));
  ButtonText.setCharacterSize(sf::Vector2f(Window->getSize()).length() / sf::Vector2f(1920, 1080).length() * 40);
}

void Button::ChangeLanguage() {}

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

  //sf::Vector2f mouse = Window->mapPixelToCoords(sf::Mouse::getPosition());
  sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition() - Window->getPosition());

  if (Back.getGlobalBounds().contains(mouse)) {
    return true;
  }
  return false;
}