#include "button.h"

Button::Button(sf::RenderWindow* window, AssetManager* manager,
               const std::string text, const float x, const float y)
    : Back(*manager->GetButton()),
      ButtonText(manager->MainFont, text, 40) {
  Window = window;

  Back.setColor(NormalColor);

  Back.setPosition(sf::Vector2f(x, y));
  ButtonText.setPosition(sf::Vector2f(x + 20, y + 20));

  Back.setRotation(sf::degrees(90));
  Back.setColor(sf::Color(230, 230, 230, 255));

  Back.setScale(sf::Vector2f(1, -1));
  ButtonText.setFillColor(sf::Color::Black);
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
  sf::Vector2i mouse = sf::Mouse::getPosition();

  if (Back.getGlobalBounds().contains(sf::Vector2f(mouse.x, mouse.y))) {
    return true;
  }
  return false;
}