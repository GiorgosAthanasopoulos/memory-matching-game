#include "config.hpp"
#include "memory_matching_game.hpp"
#include "raylib.hpp"
#include "util.hpp"
#include <raylib.h>

int main() {
  Raylib *r = new Raylib;
  MemoryMatchingGame *g = new MemoryMatchingGame;
  Vector2 winSize = GetWindowSize();

  while (!g->ShouldExit()) {
    if (IsWindowResized()) {
      Vector2 neew = GetWindowSize();
      g->Resize(winSize, neew);
      r->Resize(winSize, neew);
      winSize = neew;
    }

    g->Update();
    r->Update();

    BeginDrawing();
    ClearBackground(WIN_BG);
    g->Draw();
    r->Draw();
    EndDrawing();
  }

  delete g;
  delete r;
  return 0;
}
