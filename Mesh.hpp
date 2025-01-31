#pragma once

#include <cstdint>
#include <vector>

class Mesh {
 public:
  Mesh();
  ~Mesh();

  void CreateMesh(std::vector<float> verticies, std::vector<uint32_t> indicies);
  void RenderMesh();

 private:
  uint32_t VAO_, VBO_, IBO_, index_count_;
};
