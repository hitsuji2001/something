#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
  GLuint m_ProgramID;
  Shader();
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();
  void Use(void);

  void SetBool(const std::string& name, bool value);
  void SetInteger(const std::string& name, int value);
  void SetFloat(const std::string& name, float value);

  void SetVec2(const std::string& name, float x, float y);
  void SetVec3(const std::string& name, float x, float y, float z);
  void SetVec4(const std::string& name, float x, float y, float z, float w);

  void SetVec2(const std::string& name, const glm::vec2& value);
  void SetVec3(const std::string& name, const glm::vec3& value);
  void SetVec4(const std::string& name, const glm::vec4& value);

  void SetMat2(const std::string& name, const glm::mat2& value);
  void SetMat3(const std::string& name, const glm::mat3& value);
  void SetMat4(const std::string& name, const glm::mat4& value);

  bool LoadShaders(const char *vertexFilePath, const char *fragmentFilePath);
private:
  std::string GetFileContents(const char *filePath);
  bool CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader);
  bool CompileShaderFile(const char *filePath, GLenum shaderType, GLuint *shader);
  bool LinkProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif // __SHADER_HPP__
