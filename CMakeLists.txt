cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

project(modern-opengl)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  GLEW::GLEW
  glfw
  glm::glm-header-only
)

