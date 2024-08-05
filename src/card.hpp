#pragma once

#include "card_type.hpp"
#include <raylib.h>

class Card {
public:
  Card(Vector2 pos, CardType ct);
  void Resize(Vector2 old, Vector2 neew);
  void Update();
  void Draw(Texture2D tex);
  ~Card();

  CardType GetCardType();
  Rectangle GetRec();
  void Flip();
  bool GetFlipped();

private:
  Vector2 pos, size;
  CardType ct;
  bool flipped;
};
