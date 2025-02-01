#include "Shader.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader() {
  program_ = 0;
  uniform_model_ = 0;
  uniform_projection_ = 0;
}

Shader::~Shader() {}

void Shader::CreateFromFiles(const std::string& vertex,
                             const std::string& fragment) {
  std::string vertex_shader_source = read_shader_file(vertex);
  std::string fragment_shader_source = read_shader_file(fragment);

  compile_shader(vertex_shader_source.c_str(), fragment_shader_source.c_str());
}

std::string Shader::read_shader_file(const std::string& path) {
  std::string code;
  std::ifstream file;
  file.exceptions(std::ifstream::badbit);

  try {
    file.open(path);
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();

    code = stream.str();
  } catch (std::ifstream::failure& e) {
    std::cout << "Shader file: " << path << " cannot be read." << std::endl;
  }

  return code;
}

void Shader::add_shader(const char* shader_source, GLenum shader_type) {
  uint32_t shader = glCreateShader(shader_type);

  glShaderSource(shader, 1, &shader_source, 0);
  glCompileShader(shader);

  int result = 0;
  char info_log[1024];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

  if (!result) {
    glGetShaderInfoLog(shader, 1024, nullptr, info_log);
    std::cerr << "Error compiling the " << shader_type
              << " shader: " << info_log << std::endl;
    return;
  }

  glAttachShader(program_, shader);
}

void Shader::compile_shader(const char* vertex_shader,
                            const char* fragment_shader) {
  program_ = glCreateProgram();

  if (!program_) {
    std::cerr << "Error creating program" << std::endl;
    return;
  }

  add_shader(vertex_shader, GL_VERTEX_SHADER);
  add_shader(fragment_shader, GL_FRAGMENT_SHADER);

  int result = 0;
  char info_log[1024];

  glLinkProgram(program_);
  glGetProgramiv(program_, GL_LINK_STATUS, &result);

  if (!result) {
    glGetProgramInfoLog(program_, 1024, nullptr, info_log);
    std::cerr << "Error linking the program: " << info_log << std::endl;

    return;
  }

  glValidateProgram(program_);
  glGetProgramiv(program_, GL_VALIDATE_STATUS, &result);

  if (!result) {
    glGetProgramInfoLog(program_, 1024, nullptr, info_log);
    std::cerr << "Error validating the program: " << info_log << std::endl;

    return;
  }

  uniform_model_ = glGetUniformLocation(program_, "model");
  uniform_projection_ = glGetUniformLocation(program_, "projection");
  uniform_view_ = glGetUniformLocation(program_, "view");
  uniform_ambient_color_ =
      glGetUniformLocation(program_, "directional_light.color");
  uniform_ambient_intensity_ =
      glGetUniformLocation(program_, "directional_light.ambientIntensity");
}
