#include "../header/opengl-template.hpp"

OpenGL::OpenGL() {
  this->a_CurrentMaxShaderProgram = 0;

  this->m_Window = new Window();
  this->m_Shader = new Shader();
  this->m_VAO = new uint32_t[this->a_MaxBufferSize];
  this->m_VBO = new uint32_t[this->a_MaxBufferSize];
  this->m_EBO = new uint32_t[this->a_MaxBufferSize];
}

void OpenGL::CleanUp() {
  glDeleteVertexArrays(this->a_MaxBufferSize, this->m_VAO);
  glDeleteBuffers(this->a_MaxBufferSize, this->m_VBO);
  glDeleteBuffers(this->a_MaxBufferSize, this->m_EBO);

  delete[] this->m_VAO;
  std::cout << "[INFO]: Successfully delete `VAOs`" << std::endl;
  delete[] this->m_VBO;
  std::cout << "[INFO]: Successfully delete `VBOs`" << std::endl;
  delete[] this->m_EBO;
  std::cout << "[INFO]: Successfully delete `EBOs`" << std::endl;
  delete this->m_Shader;
  delete this->m_Window;
}

OpenGL::~OpenGL() {
  glfwTerminate();
}

Shader *OpenGL::GetShader() {
  return this->m_Shader;
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

Window *OpenGL::GetWindow() {
  return this->m_Window;
}
