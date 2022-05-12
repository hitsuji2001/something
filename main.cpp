#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./opengl-template.hpp"

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

int main() {
  const char *vsh_path = "./vertex.glsl";
  const char *fsh_path = "./fragment.glsl";

  float verticies[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
  };

  uint32_t indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  OpenGL::GetInstance().CreateWindow("Painnnnnnnnnnnnnnnnnnnnnn");

  OpenGL::GetInstance().InitGLAD();
  OpenGL::GetInstance().LoadShaders(vsh_path, fsh_path);
  OpenGL::GetInstance().LinkProgram();

  glGenVertexArrays(1, &OpenGL::GetInstance().a_VAO);
  glGenBuffers(1, &OpenGL::GetInstance().a_VBO);
  glGenBuffers(1, &OpenGL::GetInstance().a_EBO);

  glBindVertexArray(OpenGL::GetInstance().a_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, OpenGL::GetInstance().a_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGL::GetInstance().a_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  while (!glfwWindowShouldClose(OpenGL::GetInstance().GetWindow())) {
    process_input(OpenGL::GetInstance().GetWindow());

    glClearColor(0.75f, 1.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(OpenGL::GetInstance().GetShaderProgram());
    glBindVertexArray(OpenGL::GetInstance().a_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(OpenGL::GetInstance().GetWindow());
    glfwPollEvents();
  }

  return 0;
}
