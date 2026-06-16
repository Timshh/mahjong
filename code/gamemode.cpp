#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* window)
    : Manager(AssetManager(sf::Vector2i(window->getSize()))),
      NameText(Manager.MainFont, "Mahjong", 140),
      PauseButton(window, &Overseer, &Manager, TextElement::Pause, 50, 40),
      ResumeButton(window, &Overseer, &Manager, TextElement::Resume, 850, 400),
      TurtleButton(window, &Overseer, &Manager, TextElement::Turtle, 850, 500),
      WaveButton(window, &Overseer, &Manager, TextElement::Wave, 850, 600),
      QuitButton(window, &Overseer, &Manager, TextElement::Quit, 850, 800),
      LangButton(window, &Overseer, &Manager, TextElement::Language, 850, 700),
      BG(*Manager.GetBG()),
      Vignette(*Manager.GetVignette()),
      Overseer(&Manager) {
  Window = window;

  BG.setColor(sf::Color(127, 127, 127, 255));
  NameText.setPosition(sf::Vector2f(725, 200));
  NameText.setFillColor(sf::Color::Black);
  Resize();
}

void Gamemode::Tick() {
  TimeDelta += Time.restart().asSeconds();
  if (TimeDelta >= 1. / 60.) {
    Window->clear();
    DrawBG();
    switch (State) {
      case GameStates::Pause:
        Window->draw(NameText);
        if (QuitButton.Tick()) {
          Window->close();
          return;
        }
        if (LangButton.Tick()) {
          Overseer.SwapLanguage();
        }
        if (TurtleButton.Tick()) {
          Field.reset(
              new GameField(Window, &Overseer, &Manager, MahjongForms::Turtle));
          State = GameStates::Idle;
        }
        if (WaveButton.Tick()) {
          Field.reset(
              new GameField(Window, &Overseer, &Manager, MahjongForms::Wave));
          State = GameStates::Idle;
        }
        if (Field.get() != nullptr) {
          if (ResumeButton.Tick()) {
            State = GameStates::Idle;
          } else {
            if (Window->hasFocus()) {
              if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (CanEscape) {
                  State = GameStates::Idle;
                  CanEscape = false;
                }
              } else {
                CanEscape = true;
              }
            }
          }
        }
        break;
      case GameStates::Idle:
        if (PauseButton.Tick()) {
          State = GameStates::Pause;
        } else {
          if (Window->hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
              if (CanEscape) {
                State = GameStates::Pause;
                CanEscape = false;
              }
            } else {
              CanEscape = true;
            }
          }
        }
        Field->Tick();
        break;
    }
    Window->display();
    TimeDelta = 0;
  }
}

void Gamemode::Resize() {
  float mult = std::min(Window->getSize().x / 16, Window->getSize().y / 9);
  int offsetX = (Window->getSize().x - mult * 16) / 2,
      offsetY = (Window->getSize().y - mult * 9) / 2;

  NameText.setCharacterSize(mult / 120. * 140);
  NameText.setPosition(
      sf::Vector2f(mult / 120. * 725. + offsetX, mult / 120. * 200. + offsetY));

  Overseer.SizeChanged(sf::Vector2f(offsetX, offsetY), mult / 120.,
                      sf::Vector2i(Window->getSize()));

  Vignette.setTextureRect(sf::IntRect(
      sf::Vector2i(0, 0), sf::Vector2i(Manager.GetVignette()->getSize())));
}

void Gamemode::DrawBG() {
  Window->draw(BG);
  // Window->draw(Vignette);
}