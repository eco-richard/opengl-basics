#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstdint>

class Window {
 public:
  Window();

  Window(uint32_t width, uint32_t height);

  int Initialize();

  int GetBufferWidth() { return buffer_width_; }
  int GetBufferHeight() { return buffer_height_; }

  bool GetShouldClose() { return glfwWindowShouldClose(window_); }

  std::array<bool, 1024> GetKeys() { return keys_; }
  float GetXChange();
  float GetYChange();

  void SwapBuffers() { glfwSwapBuffers(window_); }

  ~Window();

 private:
  static void framebuffer_size_callback(GLFWwindow* window, int width,
                                        int height);

  static void handle_keys(GLFWwindow* window, int key, int code, int action,
                          int mode);

  void create_callbacks();

  static void handle_mouse(GLFWwindow* window, double x_pos, double y_pos);

 private:
  GLFWwindow* window_;

  uint32_t width_, height_;
  int buffer_width_, buffer_height_;

  std::array<bool, 1024> keys_;

  bool mouse_first_moved_;
  float last_x_;
  float last_y_;
  float x_change_;
  float y_change_;
};
