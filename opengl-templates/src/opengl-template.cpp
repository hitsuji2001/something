#include "../header/opengl-template.hpp"

Camera *OpenGL::m_Camera = new Camera();
Mouse  *OpenGL::m_Mouse  = new Mouse();

OpenGL::OpenGL() {
  this->m_Window  = new Window();
  this->m_Shader  = new Shader();

  this->m_Texture = new Texture [this->a_MaxTextureSize];
  this->m_VAO	  = new uint32_t[this->a_MaxBufferSize];
  this->m_VBO	  = new uint32_t[this->a_MaxBufferSize];
  this->m_EBO	  = new uint32_t[this->a_MaxBufferSize];
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

void OpenGL::CleanUp() {
  glDeleteVertexArrays(this->a_MaxBufferSize, this->m_VAO);
  glDeleteBuffers(this->a_MaxBufferSize, this->m_VBO);
  glDeleteBuffers(this->a_MaxBufferSize, this->m_EBO);

  delete[] this->m_Texture;
  std::cout << "[INFO]: Successfully delete `Textures`" << std::endl;
  delete[] this->m_VAO;
  std::cout << "[INFO]: Successfully delete `VAOs`" << std::endl;
  delete[] this->m_VBO;
  std::cout << "[INFO]: Successfully delete `VBOs`" << std::endl;
  delete[] this->m_EBO;
  std::cout << "[INFO]: Successfully delete `EBOs`" << std::endl;

  delete this->m_Shader;
  delete this->m_Window;

  delete OpenGL::m_Camera;
  delete OpenGL::m_Mouse;
}

OpenGL::~OpenGL() {
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

Texture *OpenGL::GetTextureAt(uint32_t index) {
  if (index >= this->a_MaxTextureSize) {
    std::cerr << "[ERROR]: Index out of bound: `" << index << "`." << std::endl;
    std::cerr << "         Max number of Texture is: `" << this->a_MaxTextureSize << "`. Considering changing the value in the `opengl-templates` header file." << std::endl;
  }
  return &this->m_Texture[index];
}

uint32_t *OpenGL::GetVAOAddress(uint32_t index) {
  if (index >= this->a_MaxBufferSize) {
    std::cerr << "[ERROR]: Index out of bound. There is no VAO with such index: " << index << std::endl;;
    std::cerr << "         Max number of VAOs  are: " << this->a_MaxBufferSize << std::endl;
    exit(1);
  }
  return &this->m_VAO[index];
}

uint32_t *OpenGL::GetVBOAddress(uint32_t index) {
  if (index >= this->a_MaxBufferSize) {
    std::cerr << "[ERROR]: Index out of bound. There is no VBO with such index: " << index << std::endl;
    std::cerr << "         Max number of VBOs  are: " << this->a_MaxBufferSize << std::endl;
    exit(1);
  }
  return &this->m_VBO[index];
}

uint32_t *OpenGL::GetEBOAddress(uint32_t index) {
  if (index >= this->a_MaxBufferSize) {
    std::cerr << "[ERROR]: Index out of bound. There is no EBO with such index: " << index << std::endl;
    std::cerr << "         Max number of EBOs  are: " << this->a_MaxBufferSize << std::endl;
    exit(1);
  }
  return &this->m_EBO[index];
}

uint32_t OpenGL::GetVAO(uint32_t index) {
  if (index >= this->a_MaxBufferSize) {
    std::cerr << "[ERROR]: Index out of bound. There is no VAO with such index: " << index << std::endl;;
    std::cerr << "         Max number of VAOs  are: " << this->a_MaxBufferSize << std::endl;
    exit(1);
  }
  return this->m_VAO[index];
}

uint32_t OpenGL::GetVBO(uint32_t index) {
  if (index >= this->a_MaxBufferSize) {
    std::cerr << "[ERROR]: Index out of bound. There is no VBO with such index: " << index << std::endl;
    std::cerr << "         Max number of VBOs  are: " << this->a_MaxBufferSize << std::endl;
    exit(1);
  }
  return this->m_VBO[index];
}

uint32_t OpenGL::GetEBO(uint32_t index) {
  if (index >= this->a_MaxBufferSize) {
    std::cerr << "[ERROR]: Index out of bound. There is no EBO with such index: " << index;
    std::cerr << ". Max number of EBOs  are: " << this->a_MaxBufferSize << std::endl;
    exit(1);
  }
  return this->m_EBO[index];
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
