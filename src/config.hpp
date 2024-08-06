#pragma once

#include <raylib.h>

// window
#define WIN_FLAGS FLAG_WINDOW_RESIZABLE
#define WIN_W 1280
#define WIN_H 720
#define WIN_TITLE "Memory Matching Game"
#define WIN_FPS 60
#define WIN_MIN_W 640
#define WIN_MIN_H 480
#define WIN_MAX_W 3840
#define WIN_MAX_H 2160
#define WIN_BG BLACK

// keybind
#define KEY_EXIT KEY_NULL
#define MOUSE_BUTTON_FLIP_CARD MOUSE_BUTTON_LEFT
#define KEY_PAUSE_GAME KEY_P
#define KEY_MUTE KEY_M
#define KEY_RESTART KEY_SPACE

// debug
#define DEBUG true

// card//deck
#define CARD_AMOUNT 7
#define MATCHING_AMOUNT 3
#define DECK_SIZE_X CARD_AMOUNT
#define DECK_SIZE_Y MATCHING_AMOUNT
#define CARD_SIZE_RATIO_X 10
#define CARD_SIZE_RATIO_Y 4
#define CARD_FLIPPED_COLOR BLACK
#define CARD_FLIPPED_DIAMOND_COLOR WHITE
#define TOTAL_CARDS DECK_SIZE_X *DECK_SIZE_Y

// assets
#define ASSETS "assets/"

// texture
#define TEXTURE_BG ASSETS "bg.png"
#define TEXTURE_CARD_1 ASSETS "card1.png"
#define TEXTURE_CARD_2 ASSETS "card2.png"
#define TEXTURE_CARD_3 ASSETS "card3.png"
#define TEXTURE_CARD_4 ASSETS "card4.png"
#define TEXTURE_CARD_5 ASSETS "card5.png"
#define TEXTURE_CARD_6 ASSETS "card6.png"
#define TEXTURE_CARD_7 ASSETS "card7.png"
#define TEXTURE_CURSOR ASSETS "cursor.png"
const Vector2 CURSOR_SIZE = {32, 32};

// music
#define MUSIC_BG ASSETS "bgm.mp3"
#define MUSIC_VOLUME 1.0f

// sound
#define SOUND_FLIP ASSETS "flip.mp3"
#define SOUND_RIGHT ASSETS "right.mp3"
#define SOUND_WRONG ASSETS "wrong.mp3"
#define SOUND_WON ASSETS "won.mp3"
#define SOUND_LOST ASSETS "lost.mp3"
#define SOUND_VOLUME 1.0f

// game
#define GAME_TIME 60
#define WAIT_TO_HIDE_CARDS_TIME 1.5f

// ui
#define FONT_SIZE 1000
#define UI_TEXT_COLOR WHITE
#define TIMER_H 20
#define TIMER_COLOR WHITE
