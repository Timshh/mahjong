#include "assetManager.h"

AssetManager::AssetManager() {
  BG.setRepeated(true);

  bool Opened = true;

  Opened &= OpenResource(MainFont, "data/Roboto-Medium.ttf");
  Opened &= LoadResource(BG, "data/Background.png");
  // Backs
  Opened &= LoadSVG(Empty, "data/cards/Back.svg", CardSize);
  Opened &= LoadSVG(Outline, "data/cards/Shadow.svg", OutlineSize);
  Opened &= LoadSVG(Shadow, "data/cards/Back.svg", ShadowSize);
  Opened &= LoadSVG(ShadowOutline, "data/cards/Shadow.svg", ShadowOutlineSize);
  Opened &= LoadSVG(Back, "data/cards/Back.svg", CardSize);
  Opened &= LoadSVG(Selected, "data/cards/Selected.svg", CardSize);
  Opened &= LoadSVG(Button, "data/cards/Back.svg", ButtonSize);
  Opened &= LoadSVG(ButtonSelected, "data/cards/Selected.svg", ButtonSize);
  // Cards
  Opened &= LoadSVG(Word1, "data/cards/Word1.svg", ImageSize);
  Opened &= LoadSVG(Word2, "data/cards/Word2.svg", ImageSize);
  Opened &= LoadSVG(Word3, "data/cards/Word3.svg", ImageSize);
  Opened &= LoadSVG(Word4, "data/cards/Word4.svg", ImageSize);
  Opened &= LoadSVG(Word5, "data/cards/Word5.svg", ImageSize);
  Opened &= LoadSVG(Word6, "data/cards/Word6.svg", ImageSize);
  Opened &= LoadSVG(Word7, "data/cards/Word7.svg", ImageSize);
  Opened &= LoadSVG(Word8, "data/cards/Word8.svg", ImageSize);
  Opened &= LoadSVG(Word9, "data/cards/Word9.svg", ImageSize);
  Opened &= LoadSVG(Word10, "data/cards/Word10.svg", ImageSize);
  Opened &= LoadSVG(Num1, "data/cards/Num1.svg", ImageSize);
  Opened &= LoadSVG(Num2, "data/cards/Num2.svg", ImageSize);
  Opened &= LoadSVG(Num3, "data/cards/Num3.svg", ImageSize);
  Opened &= LoadSVG(Num4, "data/cards/Num4.svg", ImageSize);
  Opened &= LoadSVG(Num5, "data/cards/Num5.svg", ImageSize);
  Opened &= LoadSVG(Num6, "data/cards/Num6.svg", ImageSize);
  Opened &= LoadSVG(Num7, "data/cards/Num7.svg", ImageSize);
  Opened &= LoadSVG(Num8, "data/cards/Num8.svg", ImageSize);
  Opened &= LoadSVG(Num9, "data/cards/Num9.svg", ImageSize);
  Opened &= LoadSVG(Num10, "data/cards/Num10.svg", ImageSize);
  Opened &= LoadSVG(Pin1, "data/cards/Pin1.svg", ImageSize);
  Opened &= LoadSVG(Pin2, "data/cards/Pin2.svg", ImageSize);
  Opened &= LoadSVG(Pin3, "data/cards/Pin3.svg", ImageSize);
  Opened &= LoadSVG(Pin4, "data/cards/Pin4.svg", ImageSize);
  Opened &= LoadSVG(Pin5, "data/cards/Pin5.svg", ImageSize);
  Opened &= LoadSVG(Pin6, "data/cards/Pin6.svg", ImageSize);
  Opened &= LoadSVG(Pin7, "data/cards/Pin7.svg", ImageSize);
  Opened &= LoadSVG(Pin8, "data/cards/Pin8.svg", ImageSize);
  Opened &= LoadSVG(Pin9, "data/cards/Pin9.svg", ImageSize);
  Opened &= LoadSVG(Pin10, "data/cards/Pin10.svg", ImageSize);
  Opened &= LoadSVG(One, "data/cards/One.svg", ImageSize);
  Opened &= LoadSVG(Two, "data/cards/Two.svg", ImageSize);
  Opened &= LoadSVG(Three, "data/cards/Three.svg", ImageSize);
  Opened &= LoadSVG(Four, "data/cards/Four.svg", ImageSize);
  Opened &= LoadSVG(Five, "data/cards/Five.svg", ImageSize);
  Opened &= LoadSVG(Six, "data/cards/Six.svg", ImageSize);

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

sf::Texture* AssetManager::GetShadowOutline() { return &ShadowOutline; }

sf::Texture* AssetManager::GetCardShadow() { return &Shadow; }

sf::Texture* AssetManager::GetCardOutline() { return &Outline; }

sf::Texture* AssetManager::GetCardBack() { return &Back; }

sf::Texture* AssetManager::GetCardSelected() { return &Selected; }

sf::Texture* AssetManager::GetButton() { return &Button; }

sf::Texture* AssetManager::GetButtonSelected() { return &ButtonSelected; }

sf::Texture* AssetManager::GetBG() { return &BG; }

bool AssetManager::LoadSVG(auto& resource, const std::string& path, const sf::Vector2i size) {
  auto document = lunasvg::Document::loadFromFile(path);
  if (!document) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  auto bitmap = document->renderToBitmap(size.x, size.y);
  bitmap.convertToRGBA();
  resource.resize(sf::Vector2u(size.x, size.y));
  resource.update(bitmap.data());
  return true;
}

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