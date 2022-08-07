#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../opengl-templates/header/opengl-template.hpp"

static glm::vec3 cameraPos	= glm::vec3(0.0f, 0.0f, 3.0f);
static glm::vec3 cameraFront	= glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp	= glm::vec3(0.0f, 1.0f, 0.0f);

static float sensitivty		= 0.1f;

static bool first_mouse		= true;
static float yaw		= -90.0f;
static float pitch		= 0.0f;
static float lastX		= 0.0f;
static float lastY		= 0.0f;
static float fov		= 45.0f;

static float deltaTime		= 0.0f;
static float lastFrame		= 0.0f;

void process_input(GLFWwindow *window) {
  const float cameraSpeed = 2.5f * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow *window, double xPosIn, double yPosIn) {
  (void) window;
  float xpos = (float)xPosIn;
  float ypos = (float)yPosIn;

  if (first_mouse) {
    lastX = xpos;
    lastY = ypos;
    first_mouse = false;
  }
  
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  xoffset *= sensitivty;
  yoffset *= sensitivty;

  yaw   += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;
  
  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  (void) window;
  (void) xoffset;

  fov -= (float) yoffset;
  if (fov < 1.0f) fov = 1.0f;
  if (fov > 45.0f) fov = 45.0f;
}

int main() {
  const char *vsh_path	= "./shader/vertex.glsl";
  const char *fsh_path	= "./shader/fragment.glsl";
  const char *img_path	= "./shader/ava.jpg";
  const char *img_path2 = "./shader/awesomeface.png";

  float vertices[] = {
     // positions        // colors         // texture coodinates
    -0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.2f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.5f, 0.3f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.9f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.5f, 0.2f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.5f, 0.6f, 0.9f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 0.0f, 1.0f
  };

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
  };

  // uint32_t indices[] = {
  //   0, 1, 2,
  //   0, 3, 2
  // };

  OpenGL &opengl = OpenGL::CreateInstance();

  opengl.GetWindow()->CreateWindow("Ugrhhh");

  lastX = opengl.GetWindow()->GetWidth() / 2.0f;
  lastY = opengl.GetWindow()->GetHeight() / 2.0f;

  glfwSetCursorPosCallback(opengl.GetWindow()->GetOpenGLWindow(), mouse_callback);
  glfwSetScrollCallback(opengl.GetWindow()->GetOpenGLWindow(), scroll_callback);
  glfwSetInputMode(opengl.GetWindow()->GetOpenGLWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glEnable(GL_DEPTH_TEST);
  opengl.GetShader()->LoadShaders(vsh_path, fsh_path);

  glGenVertexArrays(1, opengl.GetVAOAddress(0));
  glGenBuffers(1, opengl.GetVBOAddress(0));
  // glGenBuffers(1, opengl.GetEBOAddress(0));

  glBindVertexArray(opengl.GetVAO(0));

  glBindBuffer(GL_ARRAY_BUFFER, opengl.GetVBO(0));
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.GetEBO(0));
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  opengl.GetTextureAt(0)->CreateTexture(GL_TEXTURE_2D);
  opengl.GetTextureAt(0)->LoadTexture(img_path, GL_RGB);

  opengl.GetTextureAt(1)->CreateTexture(GL_TEXTURE_2D);
  opengl.GetTextureAt(1)->LoadTexture(img_path2, GL_RGBA);

  opengl.GetShader()->Use();
  opengl.GetShader()->SetInteger("texture1", 0);
  opengl.GetShader()->SetInteger("texture2", 1);

  while (!glfwWindowShouldClose(opengl.GetWindow()->GetOpenGLWindow())) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    process_input(opengl.GetWindow()->GetOpenGLWindow());

    float time = glfwGetTime();
    float r = (sin(time) / 2.0f) + 0.25f;
    float g = (cos(time) / 2.0f) + 0.25f;
    float b = (sin(2.0f * time) / 2.0f) + 0.5f;

    // glClearColor(0.93f, 0.94f, 0.82f, 1.0f);
    glClearColor(r * cos(time), g * sin(time), b * cos(time * 2), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    int vertexColor = glGetUniformLocation(opengl.GetShader()->m_ProgramID, "outColor");

    opengl.GetTextureAt(0)->ActiveTexture(GL_TEXTURE0);
    opengl.GetTextureAt(1)->ActiveTexture(GL_TEXTURE1);

    opengl.GetShader()->Use();

    glUniform4f(vertexColor, r, g, b, 1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov),
				  (float)opengl.GetWindow()->GetWidth() / (float)opengl.GetWindow()->GetHeight(),
				  0.1f,
				  100.0f);
    opengl.GetShader()->SetMat4("projection", projection);
    opengl.GetShader()->SetMat4("view", view);

    glBindVertexArray(opengl.GetVAO(0));
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for (uint32_t i = 0; i < 10; ++i) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, time * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      opengl.GetShader()->SetMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(opengl.GetWindow()->GetOpenGLWindow());
    glfwPollEvents();
  }

  opengl.CleanUp();
  return 0;
}
