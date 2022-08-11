#ifndef __EBO_HPP__
#define __EBO_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO {
public:
  GLuint ID;
  EBO(GLfloat *vertices, GLsizeiptr size);
  EBO();

  void Bind();
  void Unbind();
  void Delete();
};

#endif // __EBO_HPP__
