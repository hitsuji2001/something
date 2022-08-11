#include "../header/opengl-template.hpp"

Camera *OpenGL::m_Camera = new Camera();
Mouse  *OpenGL::m_Mouse  = new Mouse();

OpenGL::OpenGL() {
  this->m_Window  = new Window();
  this->m_Shader  = new Shader();

  this->m_Texture = new Texture();
  this->m_VAO     = NULL;
  this->m_VBO     = NULL;
  this->m_EBO     = NULL;
}

void OpenGL::SetCursorCallback() {
  glfwSetCursorPosCallback(this->m_Window->GetOpenGLWindow(), this->CursorCallback);
}

void OpenGL::SetScrollCallback() {
  glfwSetScrollCallback(this->m_Window->GetOpenGLWindow(), this->ScrollCallback);
}

void OpenGL::SetCamera(Camera *camera) {
  OpenGL::m_Camera = camera;
}

void OpenGL::SetMouse(Mouse *mouse) {
  OpenGL::m_Mouse = mouse;
}

void OpenGL::SetVAO(VAO *vao) {
  this->m_VAO = vao;
}

void OpenGL::SetVBO(VBO *vbo) {
  this->m_VBO = vbo;
}

void OpenGL::SetEBO(EBO *ebo) {
  this->m_EBO = ebo;
}

void OpenGL::CleanUp() {
  delete this->m_Texture;

  delete this->m_Shader;
  delete this->m_Window;

  if (this->m_EBO != NULL) {
    this->m_EBO->Delete();
    delete this->m_EBO;
  }
  if (this->m_VAO != NULL) {
    this->m_VAO->Delete();
    delete this->m_VAO;
  }
  if (this->m_VBO != NULL) {
    this->m_VBO->Delete();
    delete this->m_VBO;
  }

  delete OpenGL::m_Camera;
  delete OpenGL::m_Mouse;
}

OpenGL::~OpenGL() {
  this->CleanUp();
  glfwTerminate();
}

Shader *OpenGL::GetShader() {
  return this->m_Shader;
}

Camera *OpenGL::GetCamera() {
  return OpenGL::m_Camera;
}

Mouse *OpenGL::GetMouse() {
  return OpenGL::m_Mouse;
}

Window *OpenGL::GetWindow() {
  return this->m_Window;
}

Texture *OpenGL::GetTexture() {
  return this->m_Texture;
}

VAO *OpenGL::GetVAO() {
  return this->m_VAO;
}

VBO *OpenGL::GetVBO() {
  return this->m_VBO;
}

EBO *OpenGL::GetEBO() {
  return this->m_EBO;
}

void OpenGL::CursorCallback(GLFWwindow *window, double xPosIn, double yPosIn) {
  (void) window;
  float xpos = (float) xPosIn;
  float ypos = (float) yPosIn;

  if (OpenGL::m_Mouse->IsFirstMouse()) {
    OpenGL::m_Mouse->SetLastXPos(xpos);
    OpenGL::m_Mouse->SetLastYPos(ypos);
    OpenGL::m_Mouse->SetFirstMouse(false);
  }

  float xoffset = xpos - OpenGL::m_Mouse->GetLastXPos();
  float yoffset = OpenGL::m_Mouse->GetLastYPos() - ypos;

  OpenGL::m_Mouse->SetLastXPos(xpos);
  OpenGL::m_Mouse->SetLastYPos(ypos);

  xoffset *= OpenGL::m_Mouse->GetSensitivity();
  yoffset *= OpenGL::m_Mouse->GetSensitivity();

  OpenGL::m_Camera->a_Yaw   += xoffset;
  OpenGL::m_Camera->a_Pitch += yoffset;
  
  if (OpenGL::m_Camera->a_Pitch > 89.0f) OpenGL::m_Camera->a_Pitch = 89.0f;
  if (OpenGL::m_Camera->a_Pitch < -89.0f) OpenGL::m_Camera->a_Pitch = -89.0f;

  glm::vec3 front;
  front.x = cos(glm::radians(OpenGL::m_Camera->a_Yaw)) * cos(glm::radians(OpenGL::m_Camera->a_Pitch));
  front.y = sin(glm::radians(OpenGL::m_Camera->a_Pitch));
  front.z = sin(glm::radians(OpenGL::m_Camera->a_Yaw)) * cos(glm::radians(OpenGL::m_Camera->a_Pitch));
  OpenGL::m_Camera->SetFrontVector(glm::normalize(front));
}

void OpenGL::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  (void) window;
  (void) xoffset;

  OpenGL::m_Camera->a_FOV -= (float) yoffset;
  if (OpenGL::m_Camera->a_FOV < 1.0F) OpenGL::m_Camera->a_FOV = 1.0f;
  if (OpenGL::m_Camera->a_FOV > 45.0F) OpenGL::m_Camera->a_FOV = 45.0f;
}
