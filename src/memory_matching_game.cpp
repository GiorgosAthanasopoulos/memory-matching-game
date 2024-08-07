#include "memory_matching_game.hpp"
#include "asset_manager.hpp"
#include "card.hpp"
#include "card_type.hpp"
#include "config.hpp"
#include "util.hpp"
#include <cmath>
#include <ctime>
#include <raylib.h>

MemoryMatchingGame::MemoryMatchingGame() {
  winSize = GetWindowSize();
  PlayMusicStream(am.bgm);
  Restart();
}

bool MemoryMatchingGame::ShouldExit() { return WindowShouldClose(); }

void MemoryMatchingGame::Resize(Vector2 old, Vector2 neew) {
  for (size_t i = 0; i < cards.size(); ++i) {
    cards[i]->Resize(old, neew);
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
    cards[i]->Draw(GetTextureFromCardType(cards[i]->GetCardType()));
  }
  DrawTexturePro(
      am.cursor, {0, 0, (float)am.cursor.width, (float)am.cursor.height},
      {(float)GetMouseX(), (float)GetMouseY(), CURSOR_SIZE.x, CURSOR_SIZE.y},
      {0, 0}, 0, WHITE);

  float timeRemaining = gameTimer / GAME_TIME;
  DrawRectangle(0, winSize.y - TIMER_H, timeRemaining * winSize.x, TIMER_H,
                TIMER_COLOR);
}

MemoryMatchingGame::~MemoryMatchingGame() { DeleteCards(); }

void MemoryMatchingGame::Restart() {
  paused = false;
  won = false;
  lost = false;
  gameTimer = GAME_TIME;

  pendingUnflipIndices.clear();
  unflipTimer = 0;
  isWaitingToUnflip = false;

  DeleteCards();
  for (int i = 0; i < TOTAL_CARDS; ++i) {
    int indexX = i % (int)DECK_SIZE_X;
    int indexY = i / DECK_SIZE_X;
    Vector2 cardSize = CalculateSize({CARD_SIZE_RATIO_X, CARD_SIZE_RATIO_Y});
    Vector2 pos = {GetWindowWidth() / 8 +
                       (GetWindowWidth() / 100 + cardSize.x) * indexX,
                   GetWindowHeight() / 18 +
                       (GetWindowHeight() / 15 + cardSize.y) * indexY};
    CardType ct = GetRandomCardType();
    cards.push_back(new Card(pos, ct));
  }
}

Texture2D MemoryMatchingGame::GetTextureFromCardType(CardType ct) {
  switch (ct) {
  case CardType::A:
    return am.card1;
  case CardType::B:
    return am.card2;
  case CardType::C:
    return am.card3;
  case CardType::D:
    return am.card4;
  case CardType::E:
    return am.card5;
  case CardType::F:
    return am.card6;
  case CardType::G:
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
  // Update all cards
  for (size_t i = 0; i < cards.size(); ++i) {
    cards[i]->Update();
  }

  if (isWaitingToUnflip) {
    unflipTimer -= GetFrameTime();
    if (unflipTimer <= 0) {
      UnflipCards(pendingUnflipIndices);
      pendingUnflipIndices.clear();
      isWaitingToUnflip = false;
    }
    return;
  }

  for (size_t i = 0; i < cards.size(); ++i) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_FLIP_CARD) &&
        MouseHovered(cards[i]->GetRec()) && !cards[i]->GetFlipped()) {
      cards[i]->Flip();

      std::vector<int> flippedIndices = GetFlippedCards();
      if (flippedIndices.size() < MATCHING_AMOUNT) {
        PlaySound(am.flip);
        return;
      }

      if (CheckFlippedCards(flippedIndices)) {
        HandleCardMatch(flippedIndices);
      } else {
        HandleCardMismatch(flippedIndices);
      }

      break;
    }
  }
}

void MemoryMatchingGame::HandleCardMatch(
    const std::vector<int> &flippedIndices) {
  DeleteFlippedCards(flippedIndices);
  if (cards.empty()) {
    won = true;
    PlaySound(am.won);
  } else {
    PlaySound(am.right);
  }
}

void MemoryMatchingGame::HandleCardMismatch(
    const std::vector<int> &flippedIndices) {
  pendingUnflipIndices = flippedIndices;
  unflipTimer = WAIT_TO_HIDE_CARDS_TIME;
  isWaitingToUnflip = true;
  PlaySound(am.wrong);
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
    if (cards[i]->GetFlipped()) {
      res.push_back(i);
    }
  }
  return res;
}

void MemoryMatchingGame::DeleteFlippedCards(std::vector<int> flippedIndices) {
  for (size_t i = 0; i < flippedIndices.size(); ++i) {
    delete cards[flippedIndices[i]];
    cards.erase(cards.begin() + flippedIndices[i]);
    for (size_t j = 0; j < flippedIndices.size(); ++j) {
      flippedIndices[j]--;
    }
  }
}

void MemoryMatchingGame::UnflipCards(std::vector<int> flippedIndices) {
  for (size_t i = 0; i < flippedIndices.size(); ++i) {
    cards[flippedIndices[i]]->Flip();
  }
}

void MemoryMatchingGame::HandleTimers() {
  gameTimer -= GetFrameTime();
  if (gameTimer <= 0.0f) {
    lost = true;
    PlaySound(am.lost);
  }
}

bool MemoryMatchingGame::CheckFlippedCards(std::vector<int> flippedIndices) {
  for (size_t i = 1; i < flippedIndices.size(); ++i) {
    if (cards[flippedIndices[i - 1]]->GetCardType() !=
        cards[flippedIndices[i]]->GetCardType()) {
      return false;
    }
  }
  return true;
}

CardType MemoryMatchingGame::GetRandomCardType() {
  while (true) {
    CardType ct = static_cast<CardType>(GetRandomValue(0, CARD_AMOUNT - 1));
    if (CountCardType(ct) < MATCHING_AMOUNT) {
      return ct;
    }
  }
}

int MemoryMatchingGame::CountCardType(CardType ct) {
  int res = 0;
  for (size_t i = 0; i < cards.size(); ++i) {
    if (cards[i]->GetCardType() == ct) {
      res++;
    }
  }
  return res;
}

void MemoryMatchingGame::DeleteCards() {
  for (size_t i = 0; i < cards.size(); ++i) {
    delete cards[i];
  }
  cards.clear();
}
