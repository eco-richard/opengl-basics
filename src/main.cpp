#define STB_IMAGE_IMPLEMENTAION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Window.hpp"

std::vector<Mesh> create_objects();
std::vector<Shader> create_shaders();

int main() {
  Window window;

  window.Initialize();

  auto mesh_list = create_objects();
  auto shader_list = create_shaders();

  Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                -90.0f, 0.0f, 5.0f, 0.5f);

  Light ambient_light = Light(0.5f, 0.5f, 0.0f, 0.5f);

  auto brick_texture{Texture("../textures/brick.png")};
  brick_texture.LoadTexture();
  auto dirt_texture{Texture("../textures/dirt.png")};
  dirt_texture.LoadTexture();

  uint32_t uniform_model, uniform_projection, uniform_view,
      uniform_ambient_intensity, uniform_ambient_color;

  glm::mat4 projection = glm::perspective(
      45.0f,
      GLfloat(window.GetBufferWidth()) / GLfloat(window.GetBufferHeight()),
      0.1f, 100.f);

  // Main Loop
  while (!window.GetShouldClose()) {
    camera.UpdateTime();

    // Get + Handle user events
    glfwPollEvents();

    camera.KeyControl(window.GetKeys());
    camera.MouseControl(window.GetXChange(), window.GetYChange());

    // Clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_list[0].UseShader();
    uniform_model = shader_list[0].GetModelLocation();
    uniform_projection = shader_list[0].GetProjectionLocation();
    uniform_view = shader_list[0].GetViewLocation();
    uniform_ambient_color = shader_list[0].GetAmbientColor();
    uniform_ambient_intensity = shader_list[0].GetAmbientIntensity();

    ambient_light.UseLight(uniform_ambient_intensity, uniform_ambient_color);

    glm::mat4 model = glm::identity<glm::mat4>();

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniform_projection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    glUniformMatrix4fv(uniform_view, 1, GL_FALSE,
                       glm::value_ptr(camera.CalculateViewMatrix()));
    brick_texture.UseTexture();
    mesh_list[0].RenderMesh();

    model = glm::identity<glm::mat4>();
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniform_projection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    dirt_texture.UseTexture();
    mesh_list[1].RenderMesh();

    glUseProgram(0);

    window.SwapBuffers();
  }
}

std::vector<Mesh> create_objects() {
  std::vector<uint32_t> indicies = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

  std::vector<float> verticies = {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
                                  1.0f,  0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 1.0f,
                                  0.0f,  0.0f,  1.0f, 0.0f, 0.5f,  1.0f};

  auto mesh_list = std::vector<Mesh>{};

  Mesh obj1;
  obj1.CreateMesh(verticies, indicies);
  mesh_list.push_back(obj1);

  Mesh obj2;
  obj2.CreateMesh(verticies, indicies);
  mesh_list.push_back(obj2);

  return mesh_list;
}

std::vector<Shader> create_shaders() {
  auto shader_list = std::vector<Shader>{};
  Shader shader{};

  shader.CreateFromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl");
  shader_list.push_back(shader);

  return shader_list;
}
