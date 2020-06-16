#pragma once

#include <ostream>

namespace simpleStlViewer {
  class Point {
  public:
    Point(float x, float y, float z);
    Point();
    ~Point() = default;

    Point & operator = (const Point &p);
    friend std::ostream & operator <<(std::ostream &os, const Point &p);

  private:
    float x_, y_, z_;
  };

  class Triangle {
  public:
    Triangle();
    Triangle(const Point &p0, const Point &p1, const Point &p2);
    ~Triangle() = default;

    friend std::ostream & operator <<(std::ostream &os, const Triangle &tri);
  private:
    Point p0_, p1_, p2_;
  };
}