#include "Window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window() {
  width_ = 800;
  height_ = 600;
  buffer_width_ = 0;
  buffer_height_ = 0;
  window_ = nullptr;

  keys_ = {0};
}

Window::Window(uint32_t width, uint32_t height) {
  width_ = width;
  height_ = height;
  buffer_width_ = 0;
  buffer_height_ = 0;
  window_ = nullptr;
}

int Window::Initialize() {
  if (!glfwInit()) {
    std::cerr << "GLFW Library load failed ... " << std::endl;
    glfwTerminate();
    return 1;
  }

  // Setup the GLFW window properties
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window_ = glfwCreateWindow(width_, height_, "Main Window", nullptr, nullptr);

  if (!window_) {
    std::cerr << "Failed to create GLFW window..." << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwGetFramebufferSize(window_, &buffer_width_, &buffer_height_);
  glfwMakeContextCurrent(window_);

  create_callbacks();

  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glewExperimental = GL_TRUE;

  GLenum error = glewInit();
  if (error != GLEW_OK) {
    std::cerr << "GLEW failed to initialize..." << std::endl;
    glfwDestroyWindow(window_);
    glfwTerminate();
    return 1;
  }

  glEnable(GL_DEPTH_TEST);

  // Setup viewport size
  glViewport(0, 0, buffer_width_, buffer_height_);

  glfwSetWindowUserPointer(window_, this);

  return 0;
}

float Window::GetXChange() {
  float change = x_change_;
  x_change_ = 0.0f;
  return change;
}

float Window::GetYChange() {
  float change = y_change_;
  y_change_ = 0.0f;
  return change;
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width,
                                       int height) {
  glViewport(0, 0, width, height);
}

void Window::handle_keys(GLFWwindow* window, int key, int code, int action,
                         int mode) {
  Window* window_obj = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS) {
      window_obj->keys_[key] = true;
    } else if (action == GLFW_RELEASE) {
      window_obj->keys_[key] = false;
    }
  }
}

void Window::create_callbacks() {
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
  glfwSetKeyCallback(window_, handle_keys);
  glfwSetCursorPosCallback(window_, handle_mouse);
}

void Window::handle_mouse(GLFWwindow* window, double x_pos, double y_pos) {
  Window* window_obj = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (window_obj->mouse_first_moved_) {
    window_obj->last_x_ = x_pos;
    window_obj->last_y_ = y_pos;
    window_obj->mouse_first_moved_ = false;
  }

  window_obj->x_change_ = x_pos - window_obj->last_x_;
  window_obj->y_change_ = window_obj->last_y_ - y_pos;

  window_obj->last_x_ = x_pos;
  window_obj->last_y_ = y_pos;
}
