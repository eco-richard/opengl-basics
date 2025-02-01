#include "Light.hpp"

#include <GL/glew.h>

#include <glm/ext/vector_float3.hpp>

Light::Light() {
  color_ = glm::vec3(1.0f, 1.0f, 1.0f);
  ambient_intensity_ = 1.0f;
}

Light::Light(float red, float green, float blue, float alpha) {
  color_ = glm::vec3(red, green, blue);
  ambient_intensity_ = alpha;
}

void Light::UseLight(float ambient_intensity_location,
                     float ambient_color_location) {
  glUniform3f(ambient_color_location, color_.x, color_.y, color_.z);
  glUniform1f(ambient_intensity_location, ambient_intensity_);
}

Light::~Light() {}
