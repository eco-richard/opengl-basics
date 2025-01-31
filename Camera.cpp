#include "Camera.hpp"

#include <GLFW/glfw3.h>

#include <array>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch,
               float move_speed, float turn_speed) {
  position_ = position;
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;

  front_ = glm::vec3(0.0f, 0.0f, -1.0f);

  movement_speed_ = move_speed;
  turn_speed_ = turn_speed;

  update();
}
Camera::~Camera() {
  delta_time_ = 0.0f;
  last_time_ = 0.0f;
}

void Camera::update() {
  front_.x = glm::cos(glm::radians(yaw_) * glm::cos(glm::radians(pitch_)));
  front_.y = glm::sin(glm::radians(pitch_));
  front_.z = glm::sin(glm::radians(yaw_) * glm::cos(glm::radians(pitch_)));
  front_ = glm::normalize(front_);

  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
}

void Camera::KeyControl(std::array<bool, 1024> keys) {
  float velocity = movement_speed_ * delta_time_;
  if (keys[GLFW_KEY_W]) {
    position_ += front_ * velocity;
  }
  if (keys[GLFW_KEY_S]) {
    position_ -= front_ * velocity;
  }
  if (keys[GLFW_KEY_A]) {
    position_ -= right_ * velocity;
  }
  if (keys[GLFW_KEY_D]) {
    position_ += right_ * velocity;
  }
}

void Camera::MouseControl(float x_change, float y_change) {
  x_change *= turn_speed_;
  y_change *= turn_speed_;

  yaw_ += x_change;
  pitch_ += y_change;

  if (pitch_ > 89.0f) {
    pitch_ = 89.0;
  }

  if (pitch_ < -89.0) {
    pitch_ = -89.0;
  }

  update();
}

glm::mat4 Camera::CalculateViewMatrix() {
  return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::UpdateTime() {
  float now = glfwGetTime();
  delta_time_ = now - last_time_;
  last_time_ = now;
}
