#ifndef __OPENGL_TEMPLATE_HPP__
#define __OPENGL_TEMPLATE_HPP__

#include <iostream>
#include <assert.h>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGL {
public:
  static OpenGL &CreateInstance() {
    static OpenGL opengl;
    return opengl;
  }
  ~OpenGL();

  bool CreateWindow(const char *title, uint32_t width = 0, uint32_t height = 0, bool centered = true);
  GLFWwindow *GetWindow();

  uint32_t *GetShaderProgramAdress(uint32_t index);
  uint32_t GetShaderProgram(uint32_t index);
  bool LoadShaders(const char *vertexFilePath, const char *fragmentFilePath, GLuint *shaderProgram);
  bool InitGLAD();

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
  static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
  std::string SlurpFile(const char *filePath);
  bool CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader);
  bool CompileShaderFile(const char *filePath, GLenum shaderType, GLuint *shader);
  bool LinkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint *shaderProgram);

private:
  GLFWwindow *m_Window;
  GLFWmonitor **m_Monitors;
  const GLFWvidmode *m_VideoMode;

  uint32_t *m_ShaderProgram;
  
  uint32_t *m_VAO;
  uint32_t *m_VBO;
  uint32_t *m_EBO;

  int a_MonitorCount;
  uint32_t a_WindowWidth;
  uint32_t a_WindowHeight;

  uint32_t a_CurrentMaxShaderProgram;

  const uint32_t a_MaxBufferSize = 10;
  const uint32_t a_MaxShaderProgramSize = 10;
  const char *a_WindowTitle;
};

#endif // __OPENGL_TEMPLATE_HPP__
