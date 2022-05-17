#ifndef __OPENGL_TEMPLATE_HPP__
#define __OPENGL_TEMPLATE_HPP__

#include "../header/shader.hpp"
#include "../header/window.hpp"

class OpenGL {
public:
  static OpenGL &CreateInstance() {
    static OpenGL opengl;
    return opengl;
  }
  ~OpenGL();

  Window *GetWindow();
  Shader *GetShader();

  uint32_t GetVAO(uint32_t index);
  uint32_t *GetVAOAddress(uint32_t index);

  uint32_t GetVBO(uint32_t index);
  uint32_t *GetVBOAddress(uint32_t index);

  uint32_t GetEBO(uint32_t index);
  uint32_t *GetEBOAddress(uint32_t index);

  void CleanUp();
protected:
  OpenGL();
  OpenGL(const OpenGL&) = delete;

private:
  bool InitGLFW();
  void WindowSetUpAttributes();
  static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

private:
  Window *m_Window;
  Shader *m_Shader;
  
  uint32_t *m_VAO;
  uint32_t *m_VBO;
  uint32_t *m_EBO;

  uint32_t a_CurrentMaxShaderProgram;

  const uint32_t a_MaxBufferSize = 10;
  const uint32_t a_MaxShaderProgramSize = 10;
};

#endif // __OPENGL_TEMPLATE_HPP__
