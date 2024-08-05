#pragma once

#include "card_type.hpp"
#include <raylib.h>

float GetWindowWidth();
float GetWindowHeight();
Vector2 GetWindowSize();

Vector2 operator/(Vector2 a, float b);
Vector2 operator/(Vector2 a, Vector2 b);
Vector2 operator*(Vector2 a, Vector2 b);

Vector2 CalculateSize(Vector2 sizeToWinSizePercentage);
Vector2 MaintainPosAfterResize(Vector2 old, Vector2 neew, Vector2 pos);

CardType GetCardTypeFromInt(int idx);

Vector2 AssertTextFitsInViewport(const char *text, float fontSize,
                                 Vector2 maxSize);

bool MouseHovered(Rectangle area);
