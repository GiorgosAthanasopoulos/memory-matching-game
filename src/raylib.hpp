#pragma once

#include <raylib.h>

class Raylib {
public:
  Raylib();
  void Resize(Vector2 old, Vector2 neew);
  void Update();
  void Draw();
  ~Raylib();
};
