#pragma once

#include <string>
#include <vector>

#include "Shader.hpp"

#include "glm/glm.hpp"


namespace simpleStlViewer {
  struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
  };

  struct Texture {
    unsigned int id;
    std::string type;
  };

  class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(const Shader &shader);

  private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
  };
}