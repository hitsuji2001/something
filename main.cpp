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
  const char *vsh_path = "./shader/vertex.glsl";
  const char *fsh_path = "./shader/fragment.glsl";
  const char *fsh2_path = "./shader/fragment2.glsl";

  float left_column_l[] = {
    -0.75f,  0.75f, 0.0f,
    -0.5f,  -0.75f, 0.0f,
    -0.75f, -0.75f, 0.0f
  };

  float left_column_r[] = {
    -0.75f,  0.75f, 0.0f,
    -0.5f,   0.75f, 0.0f,
    -0.5f,  -0.75f, 0.0f
  };

  float right_column_l[] = {
     0.5f,  0.75f, 0.0f,
     0.75f, 0.75f, 0.0f,
     0.5f,  -0.75f, 0.0f
  };

  float right_column_r[] = {
     0.75f,  0.75f, 0.0f,
     0.75f, -0.75f, 0.0f,
     0.5f,  -0.75f, 0.0f
  };

  float horz_up[] = {
     -0.5f,  0.25f, 0.0f,
      0.5f,  0.25f, 0.0f,
      0.5f, -0.25f, 0.0f
  };

  float horz_down[] = {
     -0.5f,  0.25f, 0.0f,
     -0.5f, -0.25f, 0.0f,
      0.5f, -0.25f, 0.0f
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

  OpenGL &opengl = OpenGL::CreateInstance();

  opengl.CreateWindow("Finally Something");

  opengl.InitGLAD();
  opengl.LoadShaders(vsh_path,
		     fsh_path,
		     opengl.GetShaderProgramAdress(0));
  opengl.LoadShaders(vsh_path,
		     fsh2_path,
		     opengl.GetShaderProgramAdress(1));

  glGenVertexArrays(6, opengl.GetVAOAddress(0));
  glGenBuffers(6, opengl.GetVBOAddress(0));
  // glGenBuffers(1, opengl.GetEBOAddress(0));

  glBindVertexArray(opengl.GetVAO(0));
  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(0));
  glBufferData(GL_ARRAY_BUFFER, sizeof(left_column_l), left_column_l, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.GetEBO(0));
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glBindVertexArray(opengl.GetVAO(1));
  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(1));
  glBufferData(GL_ARRAY_BUFFER, sizeof(left_column_r), left_column_r, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glBindVertexArray(opengl.GetVAO(2));
  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(2));
  glBufferData(GL_ARRAY_BUFFER, sizeof(right_column_l), right_column_l, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glBindVertexArray(opengl.GetVAO(3));
  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(3));
  glBufferData(GL_ARRAY_BUFFER, sizeof(right_column_r), right_column_r, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glBindVertexArray(opengl.GetVAO(4));
  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(4));
  glBufferData(GL_ARRAY_BUFFER, sizeof(horz_down), horz_down, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glBindVertexArray(opengl.GetVAO(5));
  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(5));
  glBufferData(GL_ARRAY_BUFFER, sizeof(horz_up), horz_up, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);


  while (!glfwWindowShouldClose(opengl.GetWindow())) {
    process_input(opengl.GetWindow());

    glClearColor(0.75f, 1.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 6; ++i) {
      glUseProgram(opengl.GetShaderProgram(i % 2));
      glBindVertexArray(opengl.GetVAO(i));
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    //gldrawelements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(opengl.GetWindow());
    glfwPollEvents();
  }

  opengl.CleanUp();

  return 0;
}
