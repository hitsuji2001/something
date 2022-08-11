#include "../header/VBO.hpp"

VBO::VBO(void *vertices, GLsizeiptr size) {
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::VBO() {
  glGenBuffers(1, &this->ID);
}

void VBO::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
  glDeleteBuffers(1, &this->ID);
}
