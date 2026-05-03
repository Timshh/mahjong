#include "button.h"

Button::Button(sf::RenderWindow* window, AssetManager* manager,
               const std::string text, const float x, const float y)
    : Back(manager->Empty),
      Selected(manager->Empty),
      ButtonText(manager->MainFont, text, 40) {
  Window = window;

  Back.setTexture(*manager->GetCardBack());
  Selected.setTexture(*manager->GetCardSelected());
  Selected.setColor(sf::Color(255, 255, 255, 0));

  Back.setPosition(sf::Vector2f(x, y));
  Selected.setPosition(sf::Vector2f(x, y));
  ButtonText.setPosition(sf::Vector2f(x + 20, y + 10));

  Back.setRotation(sf::degrees(90));
  Selected.setRotation(sf::degrees(90));

  Back.setScale(sf::Vector2f(SizeX, -SizeY));
  Selected.setScale(sf::Vector2f(SizeX, -SizeY));
  ButtonText.setFillColor(sf::Color::Black);
}

bool Button::Tick() {
  bool result = false;
  if (IsMouseOnButton()) {
    if (!Overlap) {
      Overlap = true;
      Selected.setColor(sf::Color(255, 255, 255, OverlapAlpha));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (!Pressed) {
        Pressed = true;
        result = true;
        Selected.setColor(sf::Color(255, 255, 255, ClickedAlpha));
      }
    } else {
      Pressed = false;
      Selected.setColor(sf::Color(255, 255, 255, OverlapAlpha));
    }
  } else {
    if (Overlap) {
      Overlap = false;
      Selected.setColor(sf::Color(255, 255, 255, 0));
    }
  }
  Window->draw(Back);
  Window->draw(Selected);
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