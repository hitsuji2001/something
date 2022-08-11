#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../opengl-templates/header/opengl-template.hpp"

typedef struct {
  float x;
  float y;
  float z;
} Point;

float map(float input, float origin_min, float origin_max, float new_min, float new_max) {
  float old_range = origin_max - origin_min;
  float new_range = new_max - new_min;
  float new_value;
  
  new_value = (float)((new_range * (input - origin_min)) / old_range) + new_min;

  return new_value;
}

float random_range(int min, int max) {
  float res = rand() % max + min;
  if (res >= max) return max;
  else return res;
}

void genererate_vertices(Point *vertices, int rows, int cols, int div, OpenGL &opengl) {
  int index = 0;
  for (int y = 0; y < cols; ++y) {
    for (int x = 0; x < rows; ++x) {
      Point p1, p2, p3, p5;
      int w = opengl.GetWindow()->GetWidth();
      int h = opengl.GetWindow()->GetHeight();

      int org_mirange = 1;
      int org_marange = 100;

      int min_range = 0;
      int max_range = 10;
      p1 = {
	map((x + 1) * div, 0, w, -10, 10),
	// 0.0f,
	map(random_range(org_mirange, org_marange), org_mirange, org_marange, min_range, max_range),
	map((y + 0) * div, 0, h, -10, 10),
      };

      p2 = {
	map((x + 1) * div, 0, w, -10, 10),
	// 0.0f,
	map(random_range(org_mirange, org_marange), org_mirange, org_marange, min_range, max_range),
	map((y + 1) * div, 0, h, -10, 10),
      };

      p3 = {
	map((x + 0) * div, 0, w, -10, 10),
	// 0.0f,
	map(random_range(org_mirange, org_marange), org_mirange, org_marange, min_range, max_range),
	map((y + 0) * div, 0, h, -10, 10),
      };

      p5 = {
	map((x + 0) * div, 0, w, -10, 10),
	// 0.0f,
	map(random_range(org_mirange, org_marange), org_mirange, org_marange, min_range, max_range),
	map((y + 1) * div, 0, h, -10, 10),
      };

      vertices[index + 0] = p1;
      vertices[index + 1] = p2;
      vertices[index + 2] = p3;
      vertices[index + 3] = p2;
      vertices[index + 4] = p5;
      vertices[index + 5] = p3;

      index += 6;
    }
  }
}

void process_input(GLFWwindow *window, Camera *camera, float deltaTime) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->MoveUp(deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->MoveLeft(deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->MoveDown(deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->MoveRight(deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera->SetSpeed(1.5f);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) camera->SetSpeed(5.0f);
}

int main() {
  int rows;
  int cols;
  int div = 20;
  srand(time(NULL));

  const char *vsh_path	= "./shader/vertex.glsl";
  const char *fsh_path	= "./shader/fragment.glsl";

  OpenGL &opengl = OpenGL::CreateInstance();

  opengl.GetWindow()->CreateWindow("Ugrhhh");
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  glEnable(GL_DEPTH_TEST);

  opengl.GetShader()->LoadShaders(vsh_path, fsh_path);

  opengl.GetMouse()->SetLastXPos(opengl.GetWindow()->GetWidth() / 2.0f);
  opengl.GetMouse()->SetLastYPos(opengl.GetWindow()->GetHeight() / 2.0f);

  opengl.SetCursorCallback();
  opengl.SetScrollCallback();
  opengl.GetWindow()->SetMouseInputMode();

  rows = opengl.GetWindow()->GetWidth() / div;
  cols = opengl.GetWindow()->GetHeight() / div;
  int vertices_size = 6 * rows * cols;
  Point *vertices = new Point[vertices_size];

  genererate_vertices(vertices, rows, cols, div, opengl);
  // for (int i = 0; i < vertices_size; ++i) {
  //   printf("(%.2f, %.2f, %.2f)\n", vertices[i].x, vertices[i].y, vertices[i].z);
  // }    

  opengl.SetVAO(new VAO());
  opengl.GetVAO()->Bind();
  opengl.SetVBO(new VBO(vertices, vertices_size * sizeof(Point)));

  opengl.GetVAO()->LinkVBO(opengl.GetVBO(), 0);

  opengl.GetVBO()->Unbind();
  opengl.GetVAO()->Unbind();

  while (!glfwWindowShouldClose(opengl.GetWindow()->GetOpenGLWindow())) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    process_input(opengl.GetWindow()->GetOpenGLWindow(), opengl.GetCamera(), deltaTime);

    glClearColor(0.47f, 0.75f, 0.87f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view       = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model      = glm::mat4(1.0f);

    view = glm::lookAt(opengl.GetCamera()->GetPosition(), opengl.GetCamera()->GetPosition() + opengl.GetCamera()->GetFrontVector(), opengl.GetCamera()->GetUpVector());
    projection = glm::perspective(glm::radians(opengl.GetCamera()->a_FOV), (float)opengl.GetWindow()->GetWidth() / (float)opengl.GetWindow()->GetHeight(), 0.1f, 100.0f);
    // model = glm::rotate(model, (float)glm::radians(45.0f), glm::vec3(-0.25f, 0.0f, 0.0f));

    opengl.GetShader()->SetMat4("projection", projection);
    opengl.GetShader()->SetMat4("view", view);
    opengl.GetShader()->SetMat4("model", model);

    opengl.GetShader()->Use();
    opengl.GetVAO()->Bind();

    glDrawArrays(GL_TRIANGLES, 0, vertices_size);

    glfwSwapBuffers(opengl.GetWindow()->GetOpenGLWindow());
    glfwPollEvents();
  }

  // delete[] vertices;

  return 0;
}
