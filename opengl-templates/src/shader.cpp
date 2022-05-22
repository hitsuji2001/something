#include "../header/shader.hpp"

Shader::Shader() {

}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  this->LoadShaders(vertexPath, fragmentPath);
}

Shader::~Shader() {

}

void Shader::Use() {
  glUseProgram(this->m_ProgramID);
}

void Shader::SetBool(const std::string& name, bool value) {
  glUniform1i(glGetUniformLocation(this->m_ProgramID, name.c_str()), (int) value);
}

void Shader::SetInteger(const std::string& name, int value) {
  glUniform1i(glGetUniformLocation(this->m_ProgramID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) {
  glUniform1f(glGetUniformLocation(this->m_ProgramID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, float x, float y) {
  glUniform2f(glGetUniformLocation(this->m_ProgramID, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(this->m_ProgramID, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(this->m_ProgramID, name.c_str()), x, y, z, w);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) {
  glUniform2fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) {
  glUniform3fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) {
  glUniform4fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, &value[0]);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& value) {
  glUniformMatrix2fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value) {
  glUniformMatrix3fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
  glUniformMatrix4fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}


bool Shader::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath) {
  GLuint vertexShader = 0;
  if (!this->CompileShaderFile(vertexFilePath, GL_VERTEX_SHADER, &vertexShader)) {
    return false;
  }

  GLuint fragmentShader = 0;
  if (!this->CompileShaderFile(fragmentFilePath, GL_FRAGMENT_SHADER, &fragmentShader)) {
    return false;
  }
  
  if (!this->LinkProgram(vertexShader, fragmentShader)) {
    return false;
  }

  return true;
}

std::string Shader::GetFileContents(const char *filePath) {
  std::ifstream file(filePath);
  if (!file) {
    std::cerr << "File " << filePath << " does not exist" << std::endl;
    exit(1);
  }

  std::string fileContent;
  std::string temp;

  while (getline(file, temp)) {
    fileContent += temp + "\n";
  }
  file.close();

  return fileContent;
}
bool Shader::CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader) {
  *shader = glCreateShader(shaderType);
  glShaderSource(*shader, 1, &source, NULL);
  glCompileShader(*shader);
  std::string type;
  if (shaderType == GL_VERTEX_SHADER) type = "Vertex";
  else if (shaderType == GL_FRAGMENT_SHADER) type = "Fragment";
  else exit(1);
  
  GLint success = 0;
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    GLchar logMessage[1024];
    glGetShaderInfoLog(*shader, sizeof(logMessage), NULL, logMessage);
    std::cerr << "[ERROR]: " << type << " Shader compile failed: " << logMessage << std::endl;
    return false;
  }

  std::cout << "[INFO]: Successfully compile `" << type << " Shader`" << std::endl;
  return true;
}

bool Shader::CompileShaderFile(const char *filePath, GLenum shaderType, GLuint *shader) {
  std::string fileContent = this->GetFileContents(filePath);
  const char *source = fileContent.c_str();
  
  if (source == NULL) {
    std::cerr << "[ERROR]: Failed to read file `" << filePath << "`" << std::endl;
    return false;
  }
  bool success = this->CompileShaderSource(source, shaderType, shader);
  if (!success) {
    std::cerr << "[ERROR]: Failed to compile `" << filePath << "` (shader file)" << std::endl;
  }

  return success;
}

bool Shader::LinkProgram(GLuint vertexShader, GLuint fragmentShader) {
  this->m_ProgramID = glCreateProgram();
  glAttachShader(this->m_ProgramID, vertexShader);
  glAttachShader(this->m_ProgramID, fragmentShader);

  glLinkProgram(this->m_ProgramID);

  GLint success = 0;
  glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &success);

  if (!success) {
    GLchar logMessage[1024];
    glGetProgramInfoLog(this->m_ProgramID, sizeof(logMessage), NULL, logMessage);
    std::cerr << "[ERROR]: Link `Shader Program` failed: " << logMessage << std::endl;
    return false;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  std::cout << "[INFO]: Successfully link `Shader Program`" << std::endl;
  return success;
}
