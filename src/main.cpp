#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../opengl-templates/header/opengl-template.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../opengl-templates/header/stb_image.h"

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
  const char *img_path = "./shader/ava.jpg";

  float vertices[] = {
    // positions        // colors         // texture coodinates
    -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top left
     0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.5f, 0.5f, 0.6f, 0.7f, 0.0f, 0.0f  // bottom left
  };

  uint32_t indices[] = {
    0, 1, 2,
    0, 3, 2
  };

  OpenGL &opengl = OpenGL::CreateInstance();

  opengl.GetWindow()->CreateWindow("Ugrhhh", 1024, 1024);
  opengl.GetShader()->LoadShaders(vsh_path, fsh_path);

  glGenVertexArrays(1, opengl.GetVAOAddress(0));
  glGenBuffers(1, opengl.GetVBOAddress(0));
  glGenBuffers(1, opengl.GetEBOAddress(0));

  glBindVertexArray(opengl.GetVAO(0));

  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(0));
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.GetEBO(0));
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  int width, height, nr_channels;
  unsigned char *data = stbi_load(img_path, &width, &height, &nr_channels, 0);
  if(data == NULL) {
    std::cerr << "Could not load image" << std::endl;
    exit(1);
  }
  uint32_t texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  while (!glfwWindowShouldClose(opengl.GetWindow()->GetOpenGLWindow())) {
    process_input(opengl.GetWindow()->GetOpenGLWindow());

    glClearColor(0.93f, 0.94f, 0.82f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    float r = (sin(time) / 2.0f) + 0.25f;
    float g = (cos(time) / 2.0f) + 0.25f;
    float b = (tan(time) / 2.0f) + 0.5f;

    int vertexColor = glGetUniformLocation(opengl.GetShader()->m_ProgramID, "outColor");
    glBindTexture(GL_TEXTURE_2D, texture);

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
