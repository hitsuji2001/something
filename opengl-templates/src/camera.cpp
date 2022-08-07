#include "../header/camera.hpp"

Camera::Camera() {
  this->a_Position = glm::vec3(0.0f, 0.0f, 3.0f);
  this->a_Front    = glm::vec3(0.0f, 0.0f, -1.0f);
  this->a_UpVector       = glm::vec3(0.0f, 1.0f, 0.0f);

  this->a_Yaw            = -90.0f;
  this->a_Pitch          = 0.0f;
  this->a_FOV            = 45.0f;

  this->a_Speed    = 5.0f;
}

Camera::~Camera() {

}

glm::vec3 Camera::GetPosition() {
  return this->a_Position;
}

glm::vec3 Camera::GetFrontVector() {
  return this->a_Front;
}

glm::vec3 Camera::GetUpVector() {
  return this->a_UpVector;
}

float Camera::GetSpeed() {
  return this->a_Speed;
}

void Camera::SetFrontVector(glm::vec3 value) {
  this->a_Front = value;
}

void Camera::SetSpeed(float value) {
  this->a_Speed = value;
}

void Camera::MoveUp(float dt) {
  this->a_Position += this->a_Front * this->a_Speed * dt;
}

void Camera::MoveDown(float dt) {
  this->a_Position -= this->a_Front * this->a_Speed * dt;
}

void Camera::MoveLeft(float dt) {
  this->a_Position -= glm::normalize(glm::cross(this->a_Front, this->a_UpVector)) * this->a_Speed * dt;
}

void Camera::MoveRight(float dt) {
  this->a_Position += glm::normalize(glm::cross(this->a_Front, this->a_UpVector)) * this->a_Speed * dt;
}
