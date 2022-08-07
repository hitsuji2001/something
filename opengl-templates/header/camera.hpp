#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
  Camera();
  ~Camera();

  void MoveUp(float dt);
  void MoveDown(float dt);
  void MoveLeft(float dt);
  void MoveRight(float dt);

  glm::vec3 GetPosition();
  glm::vec3 GetFrontVector();
  glm::vec3 GetUpVector();

  float GetSpeed();

  void SetFrontVector(glm::vec3 value);
  void SetSpeed(float value);

public:
  float a_Yaw;
  float a_Pitch;
  float a_FOV;

private:
  glm::vec3 a_Position;
  glm::vec3 a_Front;
  glm::vec3 a_UpVector;
  float a_Speed;
};

#endif // __CAMERA_HPP__
