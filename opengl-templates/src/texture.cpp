#include "../header/texture.hpp"

Texture::Texture() {

}

Texture::~Texture() {

}

void Texture::CreateTexture(GLenum target, GLint wrapping, GLint filter) {
  this->m_Target = target;

  glGenTextures(1, &this->m_TextureID);
  glBindTexture(this->m_Target, this->m_TextureID);

  if (this->m_Target == GL_TEXTURE_2D) this->CreateTexture2D(wrapping, filter);
  else if (this->m_Target == GL_TEXTURE_3D) this->CreateTexture3D(wrapping, filter);
  else {
    std::cerr << "There is no such target: " << target << std::endl;
    exit(1);
  }
}

void Texture::CreateTexture2D(GLint wrapping, GLint filter) {
  glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::LoadTexture(const char *file_path, GLint format, GLsizei depth) {
  int width, height, color_channels;
  unsigned char *data = stbi_load(file_path, &width, &height, &color_channels, 0);
  if (data == NULL) {
    std::cerr << "Could not load file `" << file_path << "`" << std::endl;
    exit(1);
  }
  if (this->m_Target == GL_TEXTURE_2D) {
     glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else if (this->m_Target == GL_TEXTURE_3D) {
    glTexImage3D(GL_TEXTURE_3D, 0, format, width, height, depth, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_3D);
  } else {
    std::cerr << "Unreachable" << std::endl;
    exit(1);
  }
  stbi_image_free(data);
}

void Texture::ActiveTexture(GLenum index) {
  glActiveTexture(index);
  glBindTexture(this->m_Target, this->m_TextureID);
}

void Texture::CreateTexture3D(GLint wrapping, GLint filter) {
  glBindTexture(GL_TEXTURE_3D, this->m_TextureID);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrapping);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrapping);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrapping);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, filter);
}
