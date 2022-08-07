#include "../header/window.hpp"

Window::Window() {
  this->InitGLFW();
  this->SetUpAttributes();
}

Window::~Window() {

}

bool Window::CreateWindow(const char *title, uint32_t width, uint32_t height, bool centeredOnStartUp) {
  if (width != 0 and height != 0) {
    this->a_WindowWidth = width;
    this->a_WindowHeight = height;
  } else if (width != 0 and height == 0) {
    this->a_WindowWidth = width;
    this->a_WindowHeight = this->a_WindowWidth / 16 * 9;
  }
  this->a_WindowTitle = title;

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  this->m_Window = glfwCreateWindow(this->a_WindowWidth, this->a_WindowHeight, this->a_WindowTitle, NULL, NULL);
  if (this->m_Window == NULL) {
    std::cerr << "Could not create Window\n";
    glfwTerminate();
    return false;
  }
  glfwDefaultWindowHints();
  if (!centeredOnStartUp) {
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);
    glfwShowWindow(this->m_Window);
    
    this->InitGLAD();
    return true;
  }
  else {
    int monitorX;
    int monitorY;
    glfwGetMonitorPos(this->m_Monitors[0], &monitorX, &monitorY);
    glfwSetWindowPos(this->m_Window,
		   monitorX + (this->m_VideoMode->width - this->a_WindowWidth) / 2.0f,
		   monitorY + (this->m_VideoMode->height - this->a_WindowHeight) / 2.0f);
    glfwShowWindow(this->m_Window);
  }

  glfwMakeContextCurrent(this->m_Window);
  glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);
  this->InitGLAD();
  return true;
}

GLFWwindow *Window::GetOpenGLWindow() {
  return this->m_Window;
}

uint32_t Window::GetWidth() {
  return this->a_WindowWidth;
}

uint32_t Window::GetHeight() {
  return this->a_WindowHeight;
}

void Window::SetWidth(uint32_t value) {
  this->a_WindowWidth = value;
}

void Window::SetHeight(uint32_t value) {
  this->a_WindowHeight = value;
}

bool Window::InitGLFW() {
  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return true;
}

bool Window::InitGLAD() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Could not initialize GLAD\n";
    return false;
  }
  return true;
}

void Window::SetUpAttributes() {
  this->m_Window = NULL;
  this->m_Monitors = glfwGetMonitors(&this->a_MonitorCount);
  this->m_VideoMode = glfwGetVideoMode(this->m_Monitors[0]);
  this->a_WindowWidth = this->m_VideoMode->width / 1.75f;
  this->a_WindowHeight = this->a_WindowWidth / 16 * 9;
}

void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  (void) window;
  glViewport(0, 0, width, height);
}
