#include "actor.h"

Actor::Actor(sf::RenderWindow* const window) {
  Window = window;
  //ResetScales(sf::Vector2i(Window->getSize().x / 1920, Window->getSize().y / 1080));
}

void Actor::ResetScales(const sf::Vector2f deltaSize) {}

void Actor::ChangeLanguage() {}
