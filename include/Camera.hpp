#pragma once

#include <GLFW/glfw3.h>

#include <array>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Camera {
 public:
  Camera();
  Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch,
         float movement_speed, float turn_speed);
  ~Camera();

  void KeyControl(std::array<bool, 1024> keys);
  void MouseControl(float x_change, float y_change);

  void UpdateTime();

  glm::mat4 CalculateViewMatrix();

 private:
  void update();

 private:
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 world_up_;

  float yaw_;
  float pitch_;

  float movement_speed_;
  float turn_speed_;

  float delta_time_;
  float last_time_;
};
