#pragma once

enum class GamemodeStates{ Preparing, Idle, GameOver };

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