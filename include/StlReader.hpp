#include <vector>
#include <string>
#include "Geometry.hpp"


namespace simpleStlViewer {
  std::vector<Triangle> loadStlFileIntoTriangles(const std::string &filePath);
}