#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cmath>
#include <iostream>

Texture::Texture() {
  id_ = 0;
  width_ = 0;
  height_ = 0;
  bit_depth_ = 0;
  file_location_ = "";
}

Texture::Texture(const std::string& file) {
  id_ = 0;
  width_ = 0;
  height_ = 0;
  bit_depth_ = 0;
  file_location_ = file;
}

Texture::~Texture() { ClearTexture(); }

void Texture::LoadTexture() {
  unsigned char* tex_data =
      stbi_load(file_location_.c_str(), &width_, &height_, &bit_depth_, 0);

  if (!tex_data) {
    std::cerr << "Failed to find : " << file_location_ << std::endl;
    return;
  }

  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, tex_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(tex_data);
}

void Texture::UseTexture() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::ClearTexture() {
  glDeleteTextures(1, &id_);
  id_ = 0;
  width_ = 0;
  height_ = 0;
  bit_depth_ = 0;
  file_location_ = "";
}
