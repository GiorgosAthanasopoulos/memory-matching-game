#pragma once

#include <raylib.h>

class AssetManager {
public:
  Texture2D bg, card1, card2, card3, card4, card5, card6, card7, cursor;
  Sound flip, right, wrong, won, lost;
  Music bgm;

  AssetManager();
  ~AssetManager();
};
