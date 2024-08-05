#include "memory_matching_game.hpp"
#include "config.hpp"
#include "util.hpp"
#include <raylib.h>

MemoryMatchingGame::MemoryMatchingGame() {
  winSize = GetWindowSize();
  PlayMusicStream(am.bgm);
  Restart();
}

bool MemoryMatchingGame::ShouldExit() { return WindowShouldClose(); }

void MemoryMatchingGame::Resize(Vector2 old, Vector2 neew) {
  for (size_t i = 0; i < cards.size(); ++i) {
    cards[i].Resize(old, neew);
  }
  winSize = neew;
}

void MemoryMatchingGame::Update() {
  HandleMusic();
  HandlePaused();
  if (paused) {
    return;
  }
  if (won) {
    HandleWon();
    return;
  }
  if (lost) {
    HandleLost();
    return;
  }
  HandleCards();
  HandleTimers();
}

void MemoryMatchingGame::Draw() {
  if (paused) {
    DrawPaused();
    return;
  }
  if (won) {
    DrawWon();
    return;
  }
  if (lost) {
    DrawLost();
    return;
  }

  DrawTexturePro(am.bg, {0, 0, (float)am.bg.width, (float)am.bg.height},
                 {0, 0, winSize.x, winSize.y}, {0, 0}, 0, WHITE);
  for (size_t i = 0; i < cards.size(); ++i) {
    cards[i].Draw(GetTextureFromCardType(cards[i].GetCardType()));
  }
  DrawTexturePro(
      am.cursor, {0, 0, (float)am.cursor.width, (float)am.cursor.height},
      {(float)GetMouseX(), (float)GetMouseY(), CURSOR_SIZE.x, CURSOR_SIZE.y},
      {0, 0}, 0, WHITE);
}

MemoryMatchingGame::~MemoryMatchingGame() {}

void MemoryMatchingGame::Restart() {
  paused = false;
  won = false;
  lost = false;
  gameTimer = GAME_TIME;
  // TODO: regenerate deck
}

Texture2D MemoryMatchingGame::GetTextureFromCardType(CardType ct) {
  switch (ct) {
  case A:
    return am.card1;
  case B:
    return am.card2;
  case C:
    return am.card3;
  case D:
    return am.card4;
  case E:
    return am.card5;
  case F:
    return am.card6;
  case G:
    return am.card7;
  default:
    return am.card1;
  }
}

void MemoryMatchingGame::HandleMusic() {
  if (IsKeyPressed(KEY_MUTE)) {
    if (IsMusicStreamPlaying(am.bgm)) {
      PauseMusicStream(am.bgm);
    } else {
      ResumeMusicStream(am.bgm);
    }
  }
  UpdateMusicStream(am.bgm);
}

void MemoryMatchingGame::HandlePaused() {
  if (IsKeyPressed(KEY_PAUSE_GAME)) {
    paused = !paused;
  }
}

void MemoryMatchingGame::HandleCards() {
  for (size_t i = 0; i < cards.size(); ++i) {
    cards[i].Update();

    if (IsMouseButtonPressed(MOUSE_BUTTON_FLIP_CARD) &&
        MouseHovered(cards[i].GetRec())) {
      cards[i].Flip();

      std::vector<int> flippedIndices = GetFlippedCards();
      if (CheckFlippedCards(flippedIndices)) {
        DeleteFlippedCards(flippedIndices);
        if (cards.size() == 0) {
          won = true;
          PlaySound(am.won);
        } else {
          PlaySound(am.right);
        }
      } else {
        UnflipCards(flippedIndices);
        PlaySound(am.wrong);
      }
    }
  }
}

void MemoryMatchingGame::HandleWon() {
  if (IsKeyPressed(KEY_RESTART)) {
    Restart();
  }
}

void MemoryMatchingGame::HandleLost() {
  if (IsKeyPressed(KEY_RESTART)) {
    Restart();
  }
}

void MemoryMatchingGame::DrawPaused() {
  const char *text = "Paused";
  Vector2 textSize =
      AssertTextFitsInViewport(text, FONT_SIZE, GetWindowSize() / 2);
  DrawText(text, winSize.x / 2 - textSize.x / 2, winSize.y / 2 - textSize.y / 2,
           textSize.y, UI_TEXT_COLOR);
}

void MemoryMatchingGame::DrawWon() {
  const char *text = "Won";
  Vector2 textSize =
      AssertTextFitsInViewport(text, FONT_SIZE, GetWindowSize() / 2);
  DrawText(text, winSize.x / 2 - textSize.x / 2, winSize.y / 2 - textSize.y / 2,
           textSize.y, UI_TEXT_COLOR);
}

void MemoryMatchingGame::DrawLost() {
  const char *text = "Lost";
  Vector2 textSize =
      AssertTextFitsInViewport(text, FONT_SIZE, GetWindowSize() / 2);
  DrawText(text, winSize.x / 2 - textSize.x / 2, winSize.y / 2 - textSize.y / 2,
           textSize.y, UI_TEXT_COLOR);
}

std::vector<int> MemoryMatchingGame::GetFlippedCards() {
  std::vector<int> res;

  for (size_t i = 0; i < cards.size(); ++i) {
    if (cards[i].GetFlipped()) {
      res.push_back(i);
    }
  }

  return res;
}

void MemoryMatchingGame::DeleteFlippedCards(std::vector<int> flippedIndices) {
  for (size_t i = 0; i < flippedIndices.size(); ++i) {
    cards.erase(cards.begin() + flippedIndices[i]);
  }
}

void MemoryMatchingGame::UnflipCards(std::vector<int> flippedIndices) {
  for (size_t i = 0; i < flippedIndices.size(); ++i) {
    cards[flippedIndices[i]].Flip();
  }
}

void MemoryMatchingGame::HandleTimers() {
  gameTimer -= GetFrameTime();
  if (gameTimer <= 0.0f) {
    lost = true;
    PlaySound(am.lost);
  }
}
