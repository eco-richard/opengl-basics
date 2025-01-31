#include "Mesh.hpp"

#include <GL/glew.h>

#include <cstdint>
#include <vector>

Mesh::Mesh() {
  VAO_ = 0;
  VBO_ = 0;
  IBO_ = 0;
  index_count_ = 0;
}

Mesh::~Mesh() {}

void Mesh::CreateMesh(std::vector<float> verticies,
                      std::vector<uint32_t> indicies) {
  index_count_ = indicies.size();

  glGenVertexArrays(1, &VAO_);
  glBindVertexArray(VAO_);

  glGenBuffers(1, &IBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(indicies[0]),
               indicies.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &VBO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(verticies[0]),
               verticies.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::RenderMesh() {
  glBindVertexArray(VAO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

  glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
