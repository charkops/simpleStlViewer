#include "StlReader.hpp"
#include "geometry.hpp"

#include "stl_reader/stl_reader.h"

namespace simpleStlViewer {
  // Returns a vector of triangles of the provided stlFile, if file doesn't exist
  // or it is empty returns an empty vector
  std::vector<Triangle> loadStlFileIntoTriangles(const std::string &filePath) {
    std::vector<Triangle> triangles;

    try {
      stl_reader::StlMesh <float, unsigned int> mesh (filePath);

      triangles.reserve(mesh.num_tris());
      for(size_t itri = 0; itri < mesh.num_tris(); ++itri) {
        Point points[3];
        for(size_t icorner = 0; icorner < 3; ++icorner) {
          const float* c = mesh.tri_corner_coords (itri, icorner);
          // std::cout << "(" << c[0] << ", " << c[1] << ", " << c[2] << ") ";
          points[icorner] = Point(c[0], c[1], c[2]);
        }
        triangles.emplace_back(points[0], points[1], points[2]);
      }
    }
    catch (std::exception& e) {
      return std::vector<Triangle>();
    }

    return triangles;
  };
}