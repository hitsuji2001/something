#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

class Window {
public:
  Window();
  ~Window();

  // If both `width` and `height` is set to 0
  // This will create a window of the size
  // width = (primary monior width) / 1.75f
  // height = width / 16 * 9
  bool CreateWindow(const char *title, uint32_t width = 0, uint32_t height = 0, bool centeredOnStartUp = true);
  
public:
  uint32_t GetWidth();
  uint32_t GetHeight();
  GLFWwindow *GetOpenGLWindow();

  void SetMouseInputMode();
  void SetWidth(uint32_t value);
  void SetHeight(uint32_t value);
private:
  bool InitGLFW();
  bool InitGLAD();

  void SetUpAttributes();
  static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

private:
  GLFWwindow *m_Window;
  GLFWmonitor **m_Monitors;
  const GLFWvidmode *m_VideoMode;

  int a_MonitorCount;
  uint32_t a_WindowWidth;
  uint32_t a_WindowHeight;
  const char *a_WindowTitle;
};

#endif // __WINDOW_HPP__
