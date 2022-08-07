#ifndef __OPENGL_TEMPLATE_HPP__
#define __OPENGL_TEMPLATE_HPP__

#include "../header/shader.hpp"
#include "../header/window.hpp"
#include "../header/texture.hpp"
#include "../header/camera.hpp"
#include "../header/mouse.hpp"

class OpenGL {
public:
  static OpenGL &CreateInstance() {
    static OpenGL opengl;
    return opengl;
  }
  ~OpenGL();
  
  Window   *GetWindow();
  Shader   *GetShader();
  Texture  *GetTextureAt(uint32_t index);

  static Camera *GetCamera();
  static Mouse  *GetMouse();

  uint32_t  GetVAO(uint32_t index);
  uint32_t *GetVAOAddress(uint32_t index);

  uint32_t  GetVBO(uint32_t index);
  uint32_t *GetVBOAddress(uint32_t index);

  uint32_t  GetEBO(uint32_t index);
  uint32_t *GetEBOAddress(uint32_t index);

  static void SetCamera(Camera *camera);
  static void SetMouse(Mouse *mouse);

  void SetCursorCallback();
  void SetScrollCallback();

  void CleanUp();

public:
  static Camera *m_Camera;
  static Mouse  *m_Mouse;
  
protected:
  OpenGL();
  OpenGL(const OpenGL&) = delete;

private:
  static void CursorCallback(GLFWwindow *window, double xPosIn, double yPosIn);
  static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

private:
  Window   *m_Window;
  Shader   *m_Shader;
  Texture  *m_Texture;

  uint32_t *m_VAO;
  uint32_t *m_VBO;
  uint32_t *m_EBO;

  const uint32_t a_MaxBufferSize	= 10;
  const uint32_t a_MaxTextureSize	= 10;
};

#endif // __OPENGL_TEMPLATE_HPP__
