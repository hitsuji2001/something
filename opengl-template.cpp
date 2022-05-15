#include "./opengl-template.hpp"

OpenGL::OpenGL() {
  this->InitGLFW();
  this->m_Window = NULL;
  this->m_Monitors = glfwGetMonitors(&this->a_MonitorCount);
  this->m_VideoMode = glfwGetVideoMode(this->m_Monitors[0]);
  this->a_WindowWidth = this->m_VideoMode->width / 1.75f;
  this->a_WindowHeight = this->a_WindowWidth / 16 * 9;

  this->a_CurrentMaxShaderProgram = 0;
  this->m_ShaderProgram = new uint32_t[this->a_MaxShaderProgramSize];

  this->m_VAO = new uint32_t[this->a_MaxBufferSize];
  this->m_VBO = new uint32_t[this->a_MaxBufferSize];
  this->m_EBO = new uint32_t[this->a_MaxBufferSize];
}

OpenGL::~OpenGL() {
  delete[] this->m_VAO;
  delete[] this->m_VBO;
  delete[] this->m_EBO;

  delete[] this->m_ShaderProgram;
  glfwTerminate();
}

GLFWwindow *OpenGL::GetWindow() {
  return this->m_Window;
}

uint32_t OpenGL::GetShaderProgram(uint32_t index) {
  assert(index < this->a_MaxShaderProgramSize);
  return this->m_ShaderProgram[index];
}

uint32_t *OpenGL::GetShaderProgramAdress(uint32_t index) {
  assert(index < this->a_MaxShaderProgramSize);
  return &this->m_ShaderProgram[index];
}


uint32_t *OpenGL::GetVAOAddress(uint32_t index) {
  assert(index < this->a_MaxBufferSize);
  return &this->m_VAO[index];
}

uint32_t *OpenGL::GetVBOAddress(uint32_t index) {
  assert(index < this->a_MaxBufferSize);
  return &this->m_VBO[index];
}

uint32_t *OpenGL::GetEBOAddress(uint32_t index) {
  assert(index < this->a_MaxBufferSize);
  return &this->m_EBO[index];
}

uint32_t OpenGL::GetVAO(uint32_t index) {
  assert(index < this->a_MaxBufferSize);
  return this->m_VAO[index];
}

uint32_t OpenGL::GetVBO(uint32_t index) {
  assert(index < this->a_MaxBufferSize);
  return this->m_VBO[index];
}

uint32_t OpenGL::GetEBO(uint32_t index) {
  assert(index < this->a_MaxBufferSize);
  return this->m_EBO[index];
}

bool OpenGL::CreateWindow(const char *title, uint32_t width, uint32_t height, bool centered) {
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
  if (!centered) {
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);
    glfwShowWindow(this->m_Window);
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
  return true;
}

bool OpenGL::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath, GLuint *shaderProgram) {  
  GLuint vertexShader = 0;
  if (!this->CompileShaderFile(vertexFilePath, GL_VERTEX_SHADER, &vertexShader)) {
    return false;
  }

  GLuint fragmentShader = 0;
  if (!this->CompileShaderFile(fragmentFilePath, GL_FRAGMENT_SHADER, &fragmentShader)) {
    return false;
  }
  
  if (!this->LinkProgram(vertexShader, fragmentShader, shaderProgram)) {
    return false;
  }

  return true;
}

bool OpenGL::InitGLFW() {
  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return true;
}  

void OpenGL::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  (void) window;
  glViewport(0, 0, width, height);
}

bool OpenGL::InitGLAD() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Could not initialize GLAD\n";
    return false;
  }
  return true;
}

std::string OpenGL::SlurpFile(const char *file_path){
  std::ifstream file(file_path);
  std::string fileContent;
  std::string temp;

  while (getline(file, temp)) {
    fileContent += temp + "\n";
  }
  file.close();

  return fileContent;
}
 
bool OpenGL::CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader) {
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

  std::cout << "[INFO]: Successfully compile " << type << " Shader[" << this->a_CurrentMaxShaderProgram << "]" << std::endl;
  return true;
}
   
bool OpenGL::CompileShaderFile(const char *file_path, GLenum shaderType, GLuint *shader){
  std::string fileContent = this->SlurpFile(file_path);
  const char *source = fileContent.c_str();
  
  if (source == NULL) {
    std::cerr << "[ERROR]: Failed to read file " << file_path << std::endl;
    return false;
  }
  bool success = this->CompileShaderSource(source, shaderType, shader);
  if (!success) {
    std::cerr << "[ERROR]: Failed to compile " << file_path << " (shader file)" << std::endl;
  }
  
  return success;
}
     
bool OpenGL::LinkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint *shaderProgram) {
  *shaderProgram = glCreateProgram();
  glAttachShader(*shaderProgram, vertexShader);
  glAttachShader(*shaderProgram, fragmentShader);

  glLinkProgram(*shaderProgram);

  GLint success = 0;
  glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    GLchar logMessage[1024];
    glGetProgramInfoLog(*shaderProgram, sizeof(logMessage), NULL, logMessage);
    std::cerr << "[ERROR]: Link program failed: " << logMessage << std::endl;
    return false;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  std::cout << "[INFO]: Successfully link program" << std::endl;
  this->a_CurrentMaxShaderProgram++;
  return success;
}
