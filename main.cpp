#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./opengl-template.hpp"

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main() {
  const char *vsh_path = "./vertex.glsl";
  const char *fsh_path = "./fragment.glsl";

  float verticies[] = {
    // x     y     z
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
  };

  OpenGL::GetInstance().CreateWindow("Pain");
  OpenGL::GetInstance().InitGLAD();

  glGenBuffers(1, &OpenGL::GetInstance().a_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, OpenGL::GetInstance().a_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glGenVertexArrays(1, &OpenGL::GetInstance().a_VAO);
  glBindVertexArray(OpenGL::GetInstance().a_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, OpenGL::GetInstance().a_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  OpenGL::GetInstance().LoadShaders(vsh_path, fsh_path);
  OpenGL::GetInstance().LinkProgram();

  while (!glfwWindowShouldClose(OpenGL::GetInstance().GetWindow())) {
    process_input(OpenGL::GetInstance().GetWindow());

    glClearColor(0.75f, 1.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(OpenGL::GetInstance().GetShaderProgram());
    glBindVertexArray(OpenGL::GetInstance().GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(OpenGL::GetInstance().GetWindow());
    glfwPollEvents();
  }

  return 0;
}
