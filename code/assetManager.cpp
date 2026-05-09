#include "assetManager.h"

AssetManager::AssetManager() {
  BG.setRepeated(true);

  bool Opened = true;

  Opened &= OpenResource(MainFont, "data/Roboto-Medium.ttf");
  Opened &= LoadResource(BG, "data/Background.png");
  // Backs
  Opened &= LoadSVG(Empty, "data/cards/Back.svg");
  Opened &= LoadSVG(Shadow, "data/cards/Shadow.svg");
  Opened &= LoadSVG(Back, "data/cards/Back.svg");
  Opened &= LoadSVG(Selected, "data/cards/Selected.svg");
  // Cards
  Opened &= LoadSVG(Word1, "data/cards/Word1.svg");
  Opened &= LoadSVG(Word2, "data/cards/Word2.svg");
  Opened &= LoadSVG(Word3, "data/cards/Word3.svg");
  Opened &= LoadSVG(Word4, "data/cards/Word4.svg");
  Opened &= LoadSVG(Word5, "data/cards/Word5.svg");
  Opened &= LoadSVG(Word6, "data/cards/Word6.svg");
  Opened &= LoadSVG(Word7, "data/cards/Word7.svg");
  Opened &= LoadSVG(Word8, "data/cards/Word8.svg");
  Opened &= LoadSVG(Word9, "data/cards/Word9.svg");
  Opened &= LoadSVG(Word10, "data/cards/Word10.svg");
  Opened &= LoadSVG(Num1, "data/cards/Num1.svg");
  Opened &= LoadSVG(Num2, "data/cards/Num2.svg");
  Opened &= LoadSVG(Num3, "data/cards/Num3.svg");
  Opened &= LoadSVG(Num4, "data/cards/Num4.svg");
  Opened &= LoadSVG(Num5, "data/cards/Num5.svg");
  Opened &= LoadSVG(Num6, "data/cards/Num6.svg");
  Opened &= LoadSVG(Num7, "data/cards/Num7.svg");
  Opened &= LoadSVG(Num8, "data/cards/Num8.svg");
  Opened &= LoadSVG(Num9, "data/cards/Num9.svg");
  Opened &= LoadSVG(Num10, "data/cards/Num10.svg");
  Opened &= LoadSVG(Pin1, "data/cards/Pin1.svg");
  Opened &= LoadSVG(Pin2, "data/cards/Pin2.svg");
  Opened &= LoadSVG(Pin3, "data/cards/Pin3.svg");
  Opened &= LoadSVG(Pin4, "data/cards/Pin4.svg");
  Opened &= LoadSVG(Pin5, "data/cards/Pin5.svg");
  Opened &= LoadSVG(Pin6, "data/cards/Pin6.svg");
  Opened &= LoadSVG(Pin7, "data/cards/Pin7.svg");
  Opened &= LoadSVG(Pin8, "data/cards/Pin8.svg");
  Opened &= LoadSVG(Pin9, "data/cards/Pin9.svg");
  Opened &= LoadSVG(Pin10, "data/cards/Pin10.svg");
  Opened &= LoadSVG(One, "data/cards/One.svg");
  Opened &= LoadSVG(Two, "data/cards/Two.svg");
  Opened &= LoadSVG(Three, "data/cards/Three.svg");
  Opened &= LoadSVG(Four, "data/cards/Four.svg");
  Opened &= LoadSVG(Five, "data/cards/Five.svg");
  Opened &= LoadSVG(Six, "data/cards/Six.svg");

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

bool AssetManager::LoadSVG(auto& resource, const std::string& path) {
  auto document = lunasvg::Document::loadFromFile(path);
  if (!document) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  auto bitmap = document->renderToBitmap(75, 100);
  std::vector<std::uint8_t> pixels(bitmap.width() * bitmap.height() * 4);

  const auto* src = bitmap.data();

  for (int i = 0; i < bitmap.width() * bitmap.height(); ++i) {
    pixels[i * 4 + 0] = src[i * 4 + 2];
    pixels[i * 4 + 1] = src[i * 4 + 1];
    pixels[i * 4 + 2] = src[i * 4 + 0];
    pixels[i * 4 + 3] = src[i * 4 + 3];
  }
  resource.resize(sf::Vector2u(bitmap.width(), bitmap.height()));
  resource.update(pixels.data());
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