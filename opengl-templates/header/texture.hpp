#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./stb_image.h"

class Texture {
public:
  GLuint m_TextureID;
  GLenum m_Target;
  Texture();
  Texture(GLenum m_Target);
  ~Texture();

  void CreateTexture(GLenum target, GLint wrapping = GL_REPEAT, GLint filter = GL_LINEAR);
  void LoadTexture(const char *filePath, GLint format, GLsizei depth = 16);
  void ActiveTexture(GLenum index);
private:
  void CreateTexture2D(GLint wrapping, GLint filter);
  void CreateTexture3D(GLint wrapping, GLint filter);
};

#endif // __TEXTURE_HPP__
