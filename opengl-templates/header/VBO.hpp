#ifndef __VBO_HPP__
#define __VBO_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
public:
  GLuint ID;
  VBO(void *vertices, GLsizeiptr size);
  VBO();

  void Bind();
  void Unbind();
  void Delete();
};

#endif // __VBO_HPP__
