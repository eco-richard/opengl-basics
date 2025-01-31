cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

project(modern-opengl)

find_package(assimp CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR} .)
add_executable(main main.cpp Window.cpp Shader.cpp Mesh.cpp Camera.cpp)

target_link_libraries(main
  PRIVATE
  assimp::assimp
  GLEW::GLEW
  glfw
  glm::glm-header-only)

