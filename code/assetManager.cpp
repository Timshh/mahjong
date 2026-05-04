#include "assetManager.h"

AssetManager::AssetManager() {
  BG.setRepeated(true);

  bool Opened = true;

  Opened &= OpenResource(MainFont, "data/Roboto-Medium.ttf");
  Opened &= LoadResource(BG, "data/Background.png");
  // Backs
  Opened &= LoadResource(Empty, "data/cards/Back.png");
  Opened &= LoadResource(Shadow, "data/cards/Shadow.png");
  Opened &= LoadResource(Back, "data/cards/Back.png");
  Opened &= LoadResource(Selected, "data/cards/Selected.png");
  // Cards
  Opened &= LoadResource(Word1, "data/cards/Word1.png");
  Opened &= LoadResource(Word2, "data/cards/Word2.png");
  Opened &= LoadResource(Word3, "data/cards/Word3.png");
  Opened &= LoadResource(Word4, "data/cards/Word4.png");
  Opened &= LoadResource(Word5, "data/cards/Word5.png");
  Opened &= LoadResource(Word6, "data/cards/Word6.png");
  Opened &= LoadResource(Word7, "data/cards/Word7.png");
  Opened &= LoadResource(Word8, "data/cards/Word8.png");
  Opened &= LoadResource(Word9, "data/cards/Word9.png");
  Opened &= LoadResource(Word10, "data/cards/Word10.png");
  Opened &= LoadResource(Num1, "data/cards/Num1.png");
  Opened &= LoadResource(Num2, "data/cards/Num2.png");
  Opened &= LoadResource(Num3, "data/cards/Num3.png");
  Opened &= LoadResource(Num4, "data/cards/Num4.png");
  Opened &= LoadResource(Num5, "data/cards/Num5.png");
  Opened &= LoadResource(Num6, "data/cards/Num6.png");
  Opened &= LoadResource(Num7, "data/cards/Num7.png");
  Opened &= LoadResource(Num8, "data/cards/Num8.png");
  Opened &= LoadResource(Num9, "data/cards/Num9.png");
  Opened &= LoadResource(Num10, "data/cards/Num10.png");
  Opened &= LoadResource(Pin1, "data/cards/Pin1.png");
  Opened &= LoadResource(Pin2, "data/cards/Pin2.png");
  Opened &= LoadResource(Pin3, "data/cards/Pin3.png");
  Opened &= LoadResource(Pin4, "data/cards/Pin4.png");
  Opened &= LoadResource(Pin5, "data/cards/Pin5.png");
  Opened &= LoadResource(Pin6, "data/cards/Pin6.png");
  Opened &= LoadResource(Pin7, "data/cards/Pin7.png");
  Opened &= LoadResource(Pin8, "data/cards/Pin8.png");
  Opened &= LoadResource(Pin9, "data/cards/Pin9.png");
  Opened &= LoadResource(Pin10, "data/cards/Pin10.png");
  Opened &= LoadResource(One, "data/cards/One.png");
  Opened &= LoadResource(Two, "data/cards/Two.png");
  Opened &= LoadResource(Three, "data/cards/Three.png");
  Opened &= LoadResource(Four, "data/cards/Four.png");
  Opened &= LoadResource(Five, "data/cards/Five.png");
  Opened &= LoadResource(Six, "data/cards/Six.png");

  if (!Opened) {
    throw std::runtime_error("Failed to load data");
  }
}

sf::Texture* AssetManager::GetCard(const CardTypes type) {
  switch (type) {
    case CardTypes::Word1:
      return &Word1;
      break;
    case CardTypes::Word2:
      return &Word2;
      break;
    case CardTypes::Word3:
      return &Word3;
      break;
    case CardTypes::Word4:
      return &Word4;
      break;
    case CardTypes::Word5:
      return &Word5;
      break;
    case CardTypes::Word6:
      return &Word6;
      break;
    case CardTypes::Word7:
      return &Word7;
      break;
    case CardTypes::Word8:
      return &Word8;
      break;
    case CardTypes::Word9:
      return &Word9;
      break;
    case CardTypes::Word10:
      return &Word10;
      break;
    case CardTypes::Num1:
      return &Num1;
      break;
    case CardTypes::Num2:
      return &Num2;
      break;
    case CardTypes::Num3:
      return &Num3;
      break;
    case CardTypes::Num4:
      return &Num4;
      break;
    case CardTypes::Num5:
      return &Num5;
      break;
    case CardTypes::Num6:
      return &Num6;
      break;
    case CardTypes::Num7:
      return &Num7;
      break;
    case CardTypes::Num8:
      return &Num8;
      break;
    case CardTypes::Num9:
      return &Num9;
      break;
    case CardTypes::Num10:
      return &Num10;
      break;
    case CardTypes::Pin1:
      return &Pin1;
      break;
    case CardTypes::Pin2:
      return &Pin2;
      break;
    case CardTypes::Pin3:
      return &Pin3;
      break;
    case CardTypes::Pin4:
      return &Pin4;
      break;
    case CardTypes::Pin5:
      return &Pin5;
      break;
    case CardTypes::Pin6:
      return &Pin6;
      break;
    case CardTypes::Pin7:
      return &Pin7;
      break;
    case CardTypes::Pin8:
      return &Pin8;
      break;
    case CardTypes::Pin9:
      return &Pin9;
      break;
    case CardTypes::Pin10:
      return &Pin10;
      break;
    case CardTypes::One:
      return &One;
      break;
    case CardTypes::Two:
      return &Two;
      break;
    case CardTypes::Three:
      return &Three;
      break;
    case CardTypes::Four:
      return &Four;
      break;
    case CardTypes::Five:
      return &Five;
      break;
    case CardTypes::Six:
      return &Six;
      break;
    default:
      return &Six;
      break;
  }
}

sf::Texture* AssetManager::GetCardShadow() { return &Shadow; }

sf::Texture* AssetManager::GetCardBack() { return &Back; }

sf::Texture* AssetManager::GetCardSelected() { return &Selected; }

sf::Texture* AssetManager::GetBG() { return &BG; }

bool AssetManager::LoadResource(auto& resource, const std::string& path) {
  if (!resource.loadFromFile(path)) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  return true;
}

bool AssetManager::OpenResource(auto& resource, const std::string& path) {
  if (!resource.openFromFile(path)) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  return true;
}