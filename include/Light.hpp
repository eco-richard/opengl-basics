#pragma once

#include <glm/ext/vector_float3.hpp>

class Light {
 public:
  Light();
  Light(float red, float green, float blue, float alpha);

  void UseLight(float ambient_intensity_location, float ambient_color_location);

  ~Light();

 private:
  glm::vec3 color_;
  float ambient_intensity_;
};
