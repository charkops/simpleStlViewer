#include <vector>
#include <string>
#include "geometry.hpp"


namespace simpleStlViewer {
  std::vector<Triangle> loadStlFileIntoTriangles(const std::string &filePath);
}