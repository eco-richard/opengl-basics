#pragma once

#include <GL/glew.h>
#include <stb_image.h>

#include <cstdint>
#include <string>

class Texture {
 public:
  Texture();
  Texture(const std::string& file);
  ~Texture();

  void LoadTexture();
  void UseTexture();
  void ClearTexture();

 private:
  uint32_t id_;
  int width_, height_, bit_depth_;
  std::string file_location_;
};
