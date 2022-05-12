#ifndef __OPENGL_TEMPLATE_HPP__
#define __OPENGL_TEMPLATE_HPP__

#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGL {
public:
  static OpenGL& GetInstance() {
    static OpenGL instance;
    return instance;
  }
  ~OpenGL();

  uint32_t a_VBO;
  uint32_t a_VAO;
  uint32_t a_EBO;

  GLFWwindow *GetWindow();
  uint32_t GetShaderProgram();
  uint32_t GetVAO();
  uint32_t GetVBO();

  bool CreateWindow(const char *title, uint32_t width = 0, uint32_t height = 0, bool centered = true);
  bool LoadShaders(const char *vertexFilePath, const char *fragmentFilePath);
  bool LinkProgram();
  bool InitGLAD();
protected:
  OpenGL();
  OpenGL(OpenGL const&);
  void operator=(OpenGL const&);

private:
  bool InitGLFW();
  static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
  std::string SlurpFile(const char *file_path);
  bool CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader);
  bool CompileShaderFile(const char *filePath, GLenum shaderType, GLuint *shader);
private:
  GLFWwindow *m_Window;
  GLFWmonitor **m_Monitors;
  const GLFWvidmode *m_VideoMode;
  
  int a_MonitorCount;
  uint32_t a_WindowWidth;
  uint32_t a_WindowHeight;

  uint32_t a_VertexShader;
  uint32_t a_FragmentShader;
  uint32_t a_ShaderProgram;

  const char *a_WindowTitle;
};

#endif // __OPENGL_TEMPLATE_HPP__
