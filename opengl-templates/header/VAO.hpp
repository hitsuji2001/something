#ifndef __VAO_HPP__
#define __VAO_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./VBO.hpp"

class VAO {
public:
  VAO();

  void LinkVBO(VBO *vbo, GLuint layout, GLint size = 3, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 3 * sizeof(float), const GLvoid *pointer = (void*) 0);
  void Bind();
  void Unbind();
  void Delete();

public:
  GLuint ID;
};

#endif // __VAO_HPP__
