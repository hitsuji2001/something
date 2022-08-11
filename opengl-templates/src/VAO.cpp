#include "../header/VAO.hpp"

VAO::VAO() {
  glGenVertexArrays(1, &this->ID);
}

void VAO::LinkVBO(VBO *vbo, GLuint layout, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) {
  vbo->Bind();

  glVertexAttribPointer(layout, size, type, normalized, stride, pointer);
  glEnableVertexAttribArray(layout);

  vbo->Unbind();
}

void VAO::Bind() {
  glBindVertexArray(this->ID);
}

void VAO::Unbind() {
  glBindVertexArray(0);
}

void VAO::Delete() {
  glDeleteVertexArrays(1, &this->ID);
}
