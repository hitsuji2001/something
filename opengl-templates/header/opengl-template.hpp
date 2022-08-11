#ifndef __OPENGL_TEMPLATE_HPP__
#define __OPENGL_TEMPLATE_HPP__

#include "./shader.hpp"
#include "./window.hpp"
#include "./texture.hpp"
#include "./camera.hpp"
#include "./mouse.hpp"
#include "./VBO.hpp"
#include "./EBO.hpp"
#include "./VAO.hpp"

class OpenGL {
public:
  static OpenGL &CreateInstance() {
    static OpenGL opengl;
    return opengl;
  }
  ~OpenGL();
  
  Window   *GetWindow();
  Shader   *GetShader();
  Texture  *GetTexture();

  VAO      *GetVAO();
  VBO      *GetVBO();
  EBO      *GetEBO();

  static Camera *GetCamera();
  static Mouse  *GetMouse();

  static void SetCamera(Camera *camera);
  static void SetMouse(Mouse *mouse);

  void SetVAO(VAO *vao);
  void SetVBO(VBO *vbo);
  void SetEBO(EBO *ebo);

  void SetCursorCallback();
  void SetScrollCallback();

public:
  static Camera *m_Camera;
  static Mouse  *m_Mouse;
  
protected:
  OpenGL();
  OpenGL(const OpenGL&) = delete;

private:
  static void CursorCallback(GLFWwindow *window, double xPosIn, double yPosIn);
  static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
  void CleanUp();

private:
  Window   *m_Window;
  Shader   *m_Shader;
  Texture  *m_Texture;

  VAO      *m_VAO;
  VBO      *m_VBO;
  EBO      *m_EBO;
};

#endif // __OPENGL_TEMPLATE_HPP__
