#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../opengl-templates/header/opengl-template.hpp"

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or
      glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  } else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

int main() {
  const char *vsh_path = "./shader/vertex.glsl";
  const char *fsh_path = "./shader/fragment.glsl";

  float vertices[] = {
    -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // top left
     0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top right
     0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.5f, 0.5f, 0.6f, 0.7f  // bottom left
  };

  uint32_t indices[] = {
    0, 1, 2,
    0, 3, 2
  };

  OpenGL &opengl = OpenGL::CreateInstance();

  opengl.GetWindow()->CreateWindow("Ugrhhh");
  opengl.GetShader()->LoadShaders(vsh_path, fsh_path);

  glGenVertexArrays(1, opengl.GetVAOAddress(0));
  glGenBuffers(1, opengl.GetVBOAddress(0));
  glGenBuffers(1, opengl.GetEBOAddress(0));

  glBindVertexArray(opengl.GetVAO(0));

  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(0));
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.GetEBO(0));
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  while (!glfwWindowShouldClose(opengl.GetWindow()->GetOpenGLWindow())) {
    process_input(opengl.GetWindow()->GetOpenGLWindow());

    glClearColor(0.93f, 0.94f, 0.82f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    float r = (sin(time) / 2.0f) + 0.25f;
    float g = (cos(time) / 2.0f) + 0.25f;
    float b = (tan(time) / 2.0f) + 0.5f;

    int vertexColor = glGetUniformLocation(opengl.GetShader()->m_ProgramID, "outColor");
    opengl.GetShader()->Use();
    glUniform4f(vertexColor, r, g, b, 1.0f);
    glBindVertexArray(opengl.GetVAO(0));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(opengl.GetWindow()->GetOpenGLWindow());
    glfwPollEvents();
  }

  opengl.CleanUp();

  return 0;
}
