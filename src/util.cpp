#include "util.hpp"
#include <raylib.h>

float GetWindowWidth() { return GetRenderWidth(); }
float GetWindowHeight() { return GetRenderHeight(); }
Vector2 GetWindowSize() { return {GetWindowWidth(), GetWindowHeight()}; }

Vector2 operator/(Vector2 a, float b) { return {a.x / b, a.y / b}; }
Vector2 operator/(Vector2 a, Vector2 b) { return {a.x / b.x, a.y / b.y}; }
Vector2 operator*(Vector2 a, Vector2 b) { return {a.x * b.x, a.y * b.y}; }
Vector2 operator+(Vector2 a, Vector2 b) { return {a.x + b.x, a.y + b.y}; }

Vector2 CalculateSize(Vector2 sizeToWinSizePercentage) {
  return GetWindowSize() / sizeToWinSizePercentage;
}
Vector2 MaintainPosAfterResize(Vector2 old, Vector2 neew, Vector2 pos) {
  return pos / old * neew;
}

Vector2 AssertTextFitsInViewport(const char *text, float fontSize,
                                 Vector2 maxSize) {
  float textW = MeasureText(text, fontSize);

  while (textW > maxSize.x || fontSize > maxSize.y) {
    fontSize--;
    textW = MeasureText(text, fontSize);
  }

  return {textW, fontSize};
}

bool MouseHovered(Rectangle area) {
  Vector2 mousePos = GetMousePosition();
  return mousePos.x >= area.x && mousePos.x <= area.x + area.width &&
         mousePos.y >= area.y && mousePos.y <= area.y + area.height;
}
