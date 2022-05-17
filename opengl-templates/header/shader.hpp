#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
  uint32_t m_ProgramID;
  Shader();
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();
  void Use(void);

  void SetBool(const std::string& name, bool value);
  void SetInteger(const std::string& name, int value);
  void SetFloat(const std::string& name, float value);
  bool LoadShaders(const char *vertexFilePath, const char *fragmentFilePath);
private:
  std::string GetFileContents(const char *filePath);
  bool CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader);
  bool CompileShaderFile(const char *filePath, GLenum shaderType, GLuint *shader);
  bool LinkProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif // __SHADER_HPP__
