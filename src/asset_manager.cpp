#include "asset_manager.hpp"
#include "config.hpp"
#include <raylib.h>

AssetManager::AssetManager() {
  bg = LoadTexture(TEXTURE_BG);
  card1 = LoadTexture(TEXTURE_CARD_1);
  card2 = LoadTexture(TEXTURE_CARD_2);
  card3 = LoadTexture(TEXTURE_CARD_3);
  card4 = LoadTexture(TEXTURE_CARD_4);
  card5 = LoadTexture(TEXTURE_CARD_5);
  card6 = LoadTexture(TEXTURE_CARD_6);
  card7 = LoadTexture(TEXTURE_CARD_7);
  cursor = LoadTexture(TEXTURE_CURSOR);

  bgm = LoadMusicStream(MUSIC_BG);
  SetMusicVolume(bgm, MUSIC_VOLUME);

  flip = LoadSound(SOUND_FLIP);
  right = LoadSound(SOUND_RIGHT);
  wrong = LoadSound(SOUND_WRONG);
  won = LoadSound(SOUND_WON);
  lost = LoadSound(SOUND_LOST);
  SetSoundVolume(flip, SOUND_VOLUME);
  SetSoundVolume(right, SOUND_VOLUME);
  SetSoundVolume(wrong, SOUND_VOLUME);
  SetSoundVolume(won, SOUND_VOLUME);
  SetSoundVolume(lost, SOUND_VOLUME);
}

AssetManager::~AssetManager() {
  UnloadTexture(bg);
  UnloadTexture(card1);
  UnloadTexture(card2);
  UnloadTexture(card3);
  UnloadTexture(card4);
  UnloadTexture(card5);
  UnloadTexture(card6);
  UnloadTexture(card7);
  UnloadTexture(cursor);

  UnloadMusicStream(bgm);

  UnloadSound(flip);
  UnloadSound(right);
  UnloadSound(wrong);
  UnloadSound(won);
  UnloadSound(lost);
}
