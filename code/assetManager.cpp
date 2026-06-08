#include "assetManager.h"

AssetManager::AssetManager(const sf::Vector2f windowSize) {
  BG.setRepeated(true);

  bool Opened = true;

  //Opened &= OpenResource(MainFont, "data/Roboto-Medium.ttf");
  Opened &= OpenResource(MainFont, "data/Caveat-Font.ttf");
  Opened &= LoadResource(BG, "data/Background.png");

  Opened &= RenderResources();

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

sf::Texture* AssetManager::GetButton() { return &Button; }

std::u8string AssetManager::GetText(const TextElement elem) {
  switch (elem) {
    case TextElement::Resume:
      return CurrentLanguage.ResumeText;
      break;
    case TextElement::Hint:
      return CurrentLanguage.HintText;
      break;
    case TextElement::Pairs:
      return CurrentLanguage.PairsText;
      break;
    case TextElement::Pause:
      return CurrentLanguage.PauseText;
      break;
    case TextElement::Quit:
      return CurrentLanguage.QuitText;
      break;
    case TextElement::Refresh:
      return CurrentLanguage.RefreshText;
      break;
    case TextElement::Language:
      return CurrentLanguage.LanguageText;
      break;
    case TextElement::Turtle:
      return CurrentLanguage.TurtleText;
      break;
    case TextElement::Wave:
      return CurrentLanguage.WaveText;
      break;
  }
  return u8"";
}

void AssetManager::SizeChanged(const sf::Vector2f offset, const float mult) {
  Mult = mult;
  if (!RenderResources()) {
    throw std::runtime_error("Failed to load data");
  }

  for (Actor* actor : Subscribers) {
    actor->ResetScales(sf::Vector2f(offset.x, offset.y), mult);
  }
}

void AssetManager::SwapLanguage() {
  switch (Lang) {
    case Language::English:
      Lang = Language ::Russian;
      CurrentLanguage = Languages[Lang];
      break;
    case Language::Russian:
      Lang = Language ::English;
      CurrentLanguage = Languages[Lang];
      break;
  }

  for (Actor* actor : Subscribers) {
    actor->ChangeLanguage();
  }
}

void AssetManager::AddSubscriber(Actor* subscriber) {
  Subscribers.push_back(subscriber);
}

void AssetManager::RemoveSubscriber(Actor* subscriber) {
  std::erase(Subscribers, subscriber);
}

sf::Texture* AssetManager::GetBG() { return &BG; }

bool AssetManager::LoadSVG(auto& resource, const std::string& path,
                           const sf::Vector2i size) {
  auto document = lunasvg::Document::loadFromFile(path);
  if (!document) {
    std::cerr << "Failed to load: " << path << "\n";
    return false;
  }
  auto bitmap = document->renderToBitmap(size.x * Mult, size.y * Mult);
  bitmap.convertToRGBA();
  resource.resize(sf::Vector2u(size.x * Mult, size.y * Mult));
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

bool AssetManager::RenderResources() {
  bool Rendered = true;

  // Backs
  Rendered &= LoadSVG(Empty, "data/cards/Back.svg", CardSize);
  Rendered &= LoadSVG(Shadow, "data/cards/Back.svg", ShadowSize);
  Rendered &= LoadSVG(Back, "data/cards/Back.svg", CardSize);
  Rendered &= LoadSVG(Button, "data/cards/Back.svg", ButtonSize);

  // Cards
  Rendered &= LoadSVG(Word1, "data/cards/Word1.svg", ImageSize);
  Rendered &= LoadSVG(Word2, "data/cards/Word2.svg", ImageSize);
  Rendered &= LoadSVG(Word3, "data/cards/Word3.svg", ImageSize);
  Rendered &= LoadSVG(Word4, "data/cards/Word4.svg", ImageSize);
  Rendered &= LoadSVG(Word5, "data/cards/Word5.svg", ImageSize);
  Rendered &= LoadSVG(Word6, "data/cards/Word6.svg", ImageSize);
  Rendered &= LoadSVG(Word7, "data/cards/Word7.svg", ImageSize);
  Rendered &= LoadSVG(Word8, "data/cards/Word8.svg", ImageSize);
  Rendered &= LoadSVG(Word9, "data/cards/Word9.svg", ImageSize);
  Rendered &= LoadSVG(Word10, "data/cards/Word10.svg", ImageSize);
  Rendered &= LoadSVG(Num1, "data/cards/Num1.svg", ImageSize);
  Rendered &= LoadSVG(Num2, "data/cards/Num2.svg", ImageSize);
  Rendered &= LoadSVG(Num3, "data/cards/Num3.svg", ImageSize);
  Rendered &= LoadSVG(Num4, "data/cards/Num4.svg", ImageSize);
  Rendered &= LoadSVG(Num5, "data/cards/Num5.svg", ImageSize);
  Rendered &= LoadSVG(Num6, "data/cards/Num6.svg", ImageSize);
  Rendered &= LoadSVG(Num7, "data/cards/Num7.svg", ImageSize);
  Rendered &= LoadSVG(Num8, "data/cards/Num8.svg", ImageSize);
  Rendered &= LoadSVG(Num9, "data/cards/Num9.svg", ImageSize);
  Rendered &= LoadSVG(Num10, "data/cards/Num10.svg", ImageSize);
  Rendered &= LoadSVG(Pin1, "data/cards/Pin1.svg", ImageSize);
  Rendered &= LoadSVG(Pin2, "data/cards/Pin2.svg", ImageSize);
  Rendered &= LoadSVG(Pin3, "data/cards/Pin3.svg", ImageSize);
  Rendered &= LoadSVG(Pin4, "data/cards/Pin4.svg", ImageSize);
  Rendered &= LoadSVG(Pin5, "data/cards/Pin5.svg", ImageSize);
  Rendered &= LoadSVG(Pin6, "data/cards/Pin6.svg", ImageSize);
  Rendered &= LoadSVG(Pin7, "data/cards/Pin7.svg", ImageSize);
  Rendered &= LoadSVG(Pin8, "data/cards/Pin8.svg", ImageSize);
  Rendered &= LoadSVG(Pin9, "data/cards/Pin9.svg", ImageSize);
  Rendered &= LoadSVG(Pin10, "data/cards/Pin10.svg", ImageSize);
  Rendered &= LoadSVG(One, "data/cards/One.svg", ImageSize);
  Rendered &= LoadSVG(Two, "data/cards/Two.svg", ImageSize);
  Rendered &= LoadSVG(Three, "data/cards/Three.svg", ImageSize);
  Rendered &= LoadSVG(Four, "data/cards/Four.svg", ImageSize);
  Rendered &= LoadSVG(Five, "data/cards/Five.svg", ImageSize);
  Rendered &= LoadSVG(Six, "data/cards/Six.svg", ImageSize);
  return Rendered;
}
