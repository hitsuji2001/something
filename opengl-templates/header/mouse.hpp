#ifndef __MOUSE_HPP__
#define __MOUSE_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./window.hpp"

class Mouse {
public:
  float GetLastXPos();
  float GetLastYPos();
  float GetSensitivity();
  bool IsFirstMouse();

  void SetFirstMouse(bool value);
  void SetLastXPos(float value);
  void SetLastYPos(float value);
  
  Mouse();
  ~Mouse();

public:
  float a_Sensitivty;

private:

private:
  bool a_FirstMouse;

  float a_XPos;
  float a_YPos;

  float a_LastXPos;
  float a_LastYPos;
};

#endif // __MOUSE_HPP__
