#pragma once
#include <map>

enum class GameStates { Idle, Pause };

enum class FieldStates { Idle, Finished };

enum class CardTypes {
  Word1,
  Word2,
  Word3,
  Word4,
  Word5,
  Word6,
  Word7,
  Word8,
  Word9,
  Word10,
  Num1,
  Num2,
  Num3,
  Num4,
  Num5,
  Num6,
  Num7,
  Num8,
  Num9,
  Num10,
  Pin1,
  Pin2,
  Pin3,
  Pin4,
  Pin5,
  Pin6,
  Pin7,
  Pin8,
  Pin9,
  Pin10,
  One,
  Two,
  Three,
  Four,
  Five,
  Six,
  COUNT
};

enum class CardStates { Idle, Highlighted, Selected, Hinted };

const sf::Color NormalColor = sf::Color(230, 230, 230, 255),
                HighlightedColor = sf::Color(230, 230, 210, 255),
                SelectedColor = sf::Color(230, 230, 190, 255),
                HintedColor = sf::Color(230, 230, 170, 255);

enum class Language { Russian, English };

enum class TextElement {
  Resume,
  Pause,
  Turtle,
  Wave,
  Pairs,
  Refresh,
  Hint,
  Language,
  Quit
};

struct LanguageSet {
  std::u8string ResumeText;
  std::u8string PauseText;
  std::u8string TurtleText;
  std::u8string WaveText;
  std::u8string PairsText;
  std::u8string RefreshText;
  std::u8string HintText;
  std::u8string LanguageText;
  std::u8string QuitText;
};

inline std::map<Language, LanguageSet> Languages = {
    {Language::Russian,
     {u8"Вернуться", u8"Пауза", u8"Черепаха", u8"Волна", u8"Пары:",
      u8"Смешать", u8"Подсказка", u8"Rus", u8"Выйти"}},
    {Language::English,
     {u8"Resume", u8"Pause", u8"Turtle", u8"Wave", u8"Pairs:", u8"Refresh",
      u8"Hint", u8"Eng", u8"Quit"}}};