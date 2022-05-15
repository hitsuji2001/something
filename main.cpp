#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./opengl-template.hpp"

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  } else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

int main() {
  const char *vsh_path = "./vertex.glsl";
  const char *fsh_path = "./fragment.glsl";
  const char *fsh2_path = "./fragment2.glsl";

  float fTri[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  float sTri[] = {
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  // float verticies[] = {
  //    0.5f,  0.5f, 0.0f,  // top right
  //    0.5f, -0.5f, 0.0f,  // bottom right
  //   -0.5f, -0.5f, 0.0f,  // bottom left
  //   -0.5f,  0.5f, 0.0f   // top left
  // };

  // uint32_t indices[] = {
  //   0, 1, 3,
  //   1, 2, 3
  // };

  OpenGL::GetInstance().CreateWindow("Finally Something");

  OpenGL::GetInstance().InitGLAD();
  OpenGL::GetInstance().LoadShaders(vsh_path,
				    fsh_path,
				    OpenGL::GetInstance().GetShaderProgramAdress(0));
  OpenGL::GetInstance().LoadShaders(vsh_path,
				    fsh2_path,
				    OpenGL::GetInstance().GetShaderProgramAdress(1));

  glGenVertexArrays(2, OpenGL::GetInstance().GetVAOAddress(0));
  glGenBuffers(2, OpenGL::GetInstance().GetVBOAddress(0));
  // glGenBuffers(1, OpenGL::GetInstance().GetEBOAddress(0));

  glBindVertexArray(OpenGL::GetInstance().GetVAO(0));

  glBindBuffer(GL_ARRAY_BUFFER, OpenGL::GetInstance().GetVBO(0));
  glBufferData(GL_ARRAY_BUFFER, sizeof(fTri), fTri, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGL::GetInstance().GetEBO(0));
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glBindVertexArray(OpenGL::GetInstance().GetVAO(1));
  glBindBuffer(GL_ARRAY_BUFFER, OpenGL::GetInstance().GetVBO(1));
  glBufferData(GL_ARRAY_BUFFER, sizeof(sTri), sTri, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(OpenGL::GetInstance().GetWindow())) {
    process_input(OpenGL::GetInstance().GetWindow());

    glClearColor(0.75f, 1.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(OpenGL::GetInstance().GetShaderProgram(0));
    glBindVertexArray(OpenGL::GetInstance().GetVAO(0));
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(OpenGL::GetInstance().GetShaderProgram(1));
    glBindVertexArray(OpenGL::GetInstance().GetVAO(1));
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //gldrawelements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(OpenGL::GetInstance().GetWindow());
    glfwPollEvents();
  }

  return 0;
}
