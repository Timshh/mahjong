#include "assetManager.h"

AssetManager::AssetManager(const sf::Vector2i windowSize) {
  BG.setRepeated(true);

  bool Opened = true;

  Opened &= OpenResource(MainFont, "data/Caveat-Font.ttf");
  Opened &= LoadResource(BG, "data/Background.png");

  Opened &= RenderResources(windowSize);

  if (!Opened) {
    throw std::runtime_error("Failed to load data");
  }
}

sf::Texture* AssetManager::GetCard(const CardTypes type) {
  return &FaceTextures[type];
}

sf::Texture* AssetManager::GetVignette() { return &Vignette; }

sf::Texture* AssetManager::GetCardShade() { return &Shade; }

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
    case TextElement::Victory:
      return CurrentLanguage.WinText;
      break;
  }
  return u8"";
}

void AssetManager::SizeChanged(const sf::Vector2f offset, const float mult,
                               const sf::Vector2i windowSize) {
  Mult = mult;
  if (!RenderResources(windowSize)) {
    throw std::runtime_error("Failed to load data");
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

bool AssetManager::RenderResources(const sf::Vector2i windowSize) {
  bool Rendered = true;

  Rendered &= LoadSVG(Vignette, "data/Vignette.svg", windowSize);

  // Backs
  Rendered &= LoadSVG(Empty, "data/cards/Back.svg", CardSize);
  Rendered &= LoadSVG(Shade, "data/cards/Shade.svg", ShadeSize);
  Rendered &= LoadSVG(Back, "data/cards/Front.svg", CardSize);
  Rendered &= LoadSVG(Button, "data/cards/Front.svg", ButtonSize);

  // Cards
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word1], "data/cards/Word1.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word2], "data/cards/Word2.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word3], "data/cards/Word3.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word4], "data/cards/Word4.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word5], "data/cards/Word5.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word6], "data/cards/Word6.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word7], "data/cards/Word7.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word8], "data/cards/Word8.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word9], "data/cards/Word9.svg",
                      ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Word10], "data/cards/Word10.svg",
                      ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num1], "data/cards/Num1.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num2], "data/cards/Num2.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num3], "data/cards/Num3.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num4], "data/cards/Num4.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num5], "data/cards/Num5.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num6], "data/cards/Num6.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num7], "data/cards/Num7.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num8], "data/cards/Num8.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Num9], "data/cards/Num9.svg", ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Num10], "data/cards/Num10.svg",
                      ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin1], "data/cards/Pin1.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin2], "data/cards/Pin2.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin3], "data/cards/Pin3.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin4], "data/cards/Pin4.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin5], "data/cards/Pin5.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin6], "data/cards/Pin6.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin7], "data/cards/Pin7.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin8], "data/cards/Pin8.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Pin9], "data/cards/Pin9.svg", ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Pin10], "data/cards/Pin10.svg",
                      ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::One], "data/cards/One.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Two], "data/cards/Two.svg", ImageSize);
  Rendered &= LoadSVG(FaceTextures[CardTypes::Three], "data/cards/Three.svg",
                      ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Four], "data/cards/Four.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Five], "data/cards/Five.svg", ImageSize);
  Rendered &=
      LoadSVG(FaceTextures[CardTypes::Six], "data/cards/Six.svg", ImageSize);
  return Rendered;
}
