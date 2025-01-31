#pragma once

#include <GL/glew.h>

#include <cstdint>
#include <string>

class Shader {
 public:
  Shader();
  ~Shader();

  void CreateFromFiles(const std::string& vertex, const std::string& fragment);
  void UseShader() { glUseProgram(program_); }
  uint32_t GetModelLocation() { return uniform_model_; }
  uint32_t GetProjectionLocation() { return uniform_projection_; }
  uint32_t GetViewLocation() { return uniform_view_; }

 private:
  std::string read_shader_file(const std::string& path);
  void add_shader(const char* shader_source, GLenum shader_type);
  void compile_shader(const char* vertex_shader, const char* fragment_shader);

 private:
  uint32_t program_, uniform_model_, uniform_projection_, uniform_view_;
};
