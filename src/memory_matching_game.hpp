#pragma once

#include "asset_manager.hpp"
#include "card.hpp"
#include "card_type.hpp"
#include <raylib.h>
#include <vector>

class MemoryMatchingGame {
public:
  MemoryMatchingGame();
  bool ShouldExit();
  void Resize(Vector2 old, Vector2 neew);
  void Update();
  void Draw();
  ~MemoryMatchingGame();

private:
  Vector2 winSize;
  std::vector<Card *> cards;
  AssetManager am;
  bool paused, won, lost;
  float gameTimer;

  std::vector<int> pendingUnflipIndices;
  float unflipTimer;
  bool isWaitingToUnflip;

  void Restart();
  Texture2D GetTextureFromCardType(CardType ct);
  std::vector<int> GetFlippedCards();
  bool CheckFlippedCards(std::vector<int> flippedIndices);
  void DeleteFlippedCards(std::vector<int> flippedIndices);
  void UnflipCards(std::vector<int> flippedIndices);
  CardType GetRandomCardType();
  int CountCardType(CardType ct);
  void DeleteCards();

  void HandleMusic();
  void HandlePaused();
  void HandleCards();
  void HandleWon();
  void HandleLost();
  void HandleTimers();
  void HandleCardMatch(const std::vector<int> &flippedIndices);
  void HandleCardMismatch(const std::vector<int> &flippedIndices);

  void DrawPaused();
  void DrawWon();
  void DrawLost();
};
