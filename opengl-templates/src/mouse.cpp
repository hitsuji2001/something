#include "../header/mouse.hpp"

Mouse::Mouse() {
  this->a_Sensitivty = 0.075f;

  this->a_XPos = 0.0f;
  this->a_YPos = 0.0f;
  this->a_LastXPos = 0.0f;
  this->a_LastYPos = 0.0f;
  this->a_FirstMouse = true;
}

Mouse::~Mouse() {

}

bool Mouse::IsFirstMouse() {
  return this->a_FirstMouse;
}

float Mouse::GetSensitivity() {
  return this->a_Sensitivty;
}

float Mouse::GetLastXPos() {
  return this->a_LastXPos;
}

float Mouse::GetLastYPos() {
  return this->a_LastYPos;
}

void Mouse::SetLastXPos(float value) {
  this->a_LastXPos = value;
}

void Mouse::SetLastYPos(float value) {
  this->a_LastYPos = value;
}

void Mouse::SetFirstMouse(bool value) {
  this->a_FirstMouse = value;
}
