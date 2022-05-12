#include "./opengl-template.hpp"

OpenGL::OpenGL() {
  this->InitGLFW();
  this->m_Window = NULL;
  this->m_Monitors = glfwGetMonitors(&this->a_MonitorCount);
  this->m_VideoMode = glfwGetVideoMode(this->m_Monitors[0]);
  this->a_WindowWidth = this->m_VideoMode->width / 1.75f;
  this->a_WindowHeight = this->a_WindowWidth / 16 * 9;
}

OpenGL::~OpenGL() {
  glfwTerminate();
}

GLFWwindow *OpenGL::GetWindow() {
  return this->m_Window;
}

uint32_t OpenGL::GetShaderProgram() {
  return this->a_ShaderProgram;
}

uint32_t OpenGL::GetVAO() {
  return this->a_VAO;
}

uint32_t OpenGL::GetVBO() {
  return this->a_VBO;
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

bool OpenGL::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath) {
  bool success;
  success = this->CompileShaderFile(vertexFilePath, GL_VERTEX_SHADER, &this->a_VertexShader);
  success &= this->CompileShaderFile(fragmentFilePath, GL_FRAGMENT_SHADER, &this->a_FragmentShader);
  return success;
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

  std::cout << "[INFO]: Successfully compile " << type << " Shader" << std::endl;
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
     
bool OpenGL::LinkProgram() {
  this->a_ShaderProgram = glCreateProgram();

  glAttachShader(this->a_ShaderProgram, this->a_VertexShader);
  glAttachShader(this->a_ShaderProgram, this->a_FragmentShader);
  glLinkProgram(this->a_ShaderProgram);

  GLint success = 0;
  glGetProgramiv(this->a_ShaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    GLchar logMessage[1024];
    glGetProgramInfoLog(this->a_ShaderProgram, sizeof(logMessage), NULL, logMessage);
    std::cerr << "[ERROR]: Link program failed: " << logMessage << std::endl;
    return false;
  }
  glDeleteShader(this->a_VertexShader);
  glDeleteShader(this->a_FragmentShader);

  std::cout << "[INFO]: Successfully link program" << std::endl;
  return success;
}
