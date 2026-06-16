#pragma once
#include <lunasvg.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "actor.h"
#include "assetManager.h"
#include "data.h"

class Observer {
 public:
  Observer(AssetManager* manager);

  void AddSubscriber(Actor* subscriber);
  void RemoveSubscriber(Actor* subscriber);
  void SizeChanged(const sf::Vector2f offset, const float mult,
                   const sf::Vector2i windowSize);
  void SwapLanguage();

 private:
  AssetManager* Manager;
  std::vector<Actor*> Subscribers;
};