#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
  Window();
  ~Window();
  bool CreateWindow(const char *title, uint32_t width = 0, uint32_t height = 0, bool centeredOnStartUp = true);
  GLFWwindow *GetOpenGLWindow();
  
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
