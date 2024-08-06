#include "card.hpp"
#include "card_type.hpp"
#include "config.hpp"
#include "util.hpp"
#include <raylib.h>

Card::Card(Vector2 pos, CardType ct) {
  this->pos = pos;
  this->ct = ct;
  flipped = false;
  Resize(GetWindowSize(), GetWindowSize());
}

void Card::Resize(Vector2 old, Vector2 neew) {
  size = CalculateSize({CARD_SIZE_RATIO_X, CARD_SIZE_RATIO_Y});
  pos = MaintainPosAfterResize(old, neew, pos);
}

void Card::Update() {}

void Card::Draw(Texture2D tex) {
  if (flipped) {
    DrawTexturePro(tex, {0, 0, (float)tex.width, (float)tex.height}, GetRec(),
                   {0, 0}, 0, WHITE);
    return;
  }
  DrawRectangleRec(GetRec(), CARD_FLIPPED_COLOR);
  DrawPoly(pos + (size / 2), 4, size.x / 4, 0, CARD_FLIPPED_DIAMOND_COLOR);
}

Card::~Card() {}

CardType Card::GetCardType() { return ct; }

Rectangle Card::GetRec() { return {pos.x, pos.y, size.x, size.y}; }

void Card::Flip() { flipped = !flipped; }

bool Card::GetFlipped() { return flipped; }
