#pragma once
#include <map>

enum class GameStates { Idle, Pause };

enum class FieldStates {
	Idle,
	Finished
};

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

enum class CardStates {
  Idle,
  Highlighted, Selected, Hinted
};

const sf::Color NormalColor = sf::Color(230, 230, 230, 255),
                HighlightedColor = sf::Color(230, 230, 210, 255),
                SelectedColor = sf::Color(230, 230, 190, 255),
                HintedColor = sf::Color(230, 230, 170, 255);

enum class Language {
    Russian,
    English
};

struct LanguageSet {
  std::string ResumeText;
  std::string PauseText;
  std::string TurtleText;
  std::string WaveText;
  std::string PairsText;
  std::string RefreshText;
  std::string HintText;
  std::string LanguageText;
  std::string MahjongText;
  std::string QuitText;
};

inline std::map<Language, LanguageSet> Languages = {
    {Language::Russian,
     {"Продолжить", "Пауза", "Черепаха", "Волна", "Пары:", "Перемешать",
      "Подсказка", "Рус", "Маджонг", "Выйти"}},
    {Language::English,
     {"Resume", "Pause", "Turtle", "Wave", "Pairs:", "Refresh",
      "Hint", "Eng", "Mahjong", "Quit"}}};