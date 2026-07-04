#include "observer.h"

Observer::Observer(AssetManager* manager) : Manager(manager) {}

void Observer::SizeChanged(const sf::Vector2f offset, const float mult,
                           const sf::Vector2i windowSize) {
  Manager->SizeChanged(offset, mult, windowSize);

  for (Actor* actor : Subscribers) {
    actor->ResetScales(sf::Vector2f(offset.x, offset.y), mult);
  }
}

void Observer::SwapLanguage() {
  Manager->SwapLanguage();

  for (Actor* actor : Subscribers) {
    actor->ChangeLanguage();
  }
}

void Observer::AddSubscriber(Actor* subscriber) {
  Subscribers.push_back(subscriber);
}

void Observer::RemoveSubscriber(Actor* subscriber) {
  std::erase(Subscribers, subscriber);
}