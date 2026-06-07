#include "gamemode.h"

Gamemode::Gamemode(sf::RenderWindow* window)
    : Manager(AssetManager(sf::Vector2f(window->getSize()))),
      NameText(Manager.MainFont, "Mahjong", 140),
      PauseButton(window, &Manager, "Pause", 50, 40),
      ResumeButton(window, &Manager, "Resume", 850, 400),
      TurtleButton(window, &Manager, "Turtle", 850, 500),
      WaveButton(window, &Manager, "Wave", 850, 600),
      QuitButton(window, &Manager, "Quit", 850, 700),
      BG(Manager.Empty) {
  Window = window;

  BG.setTexture(*Manager.GetBG());
  BG.setColor(sf::Color(127, 127, 127, 255));
  NameText.setPosition(sf::Vector2f(725, 200));
  NameText.setFillColor(sf::Color::Black);
}

void Gamemode::Tick() {
  TimeDelta += Time.restart().asSeconds();
  if (TimeDelta >= 1 / 10) {

    Window->clear();
    DrawBG();
    switch (State) {
      case GameStates::Pause:
        Window->draw(NameText);
        if (QuitButton.Tick()) {
          Window->close();
          return;
        }
        if (TurtleButton.Tick()) {
          Field.reset(new GameField(Window, &Manager, MahjongForms::Turtle));
          State = GameStates::Idle;
        }
        if (WaveButton.Tick()) {
          Field.reset(new GameField(Window, &Manager, MahjongForms::Wave));
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
  Manager.SizeChanged(sf::Vector2f(Window->getSize()));
  NameText.setCharacterSize(sf::Vector2f(Window->getSize()).length() /
                              sf::Vector2f(1920, 1080).length() * 140);
  NameText.setPosition(sf::Vector2f(Window->getSize().x / 1920. * 725.,
                                    Window->getSize().y / 1080. * 200.));
  //std::cout << Window->getPosition().x << "x" << Window->getPosition().y << std::endl;
}

void Gamemode::DrawBG() { Window->draw(BG); }