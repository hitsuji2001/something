#include "../header/EBO.hpp"

EBO::EBO(GLfloat *vertices, GLsizeiptr size) {
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

EBO::EBO() {
  glGenBuffers(1, &this->ID);
}

void EBO::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void EBO::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
  glDeleteBuffers(1, &this->ID);
}
