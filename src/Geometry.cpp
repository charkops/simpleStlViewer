

#include "Geometry.hpp"

namespace simpleStlViewer {

  Point::Point ()
    : x_ (0.0), y_ (0.0), z_ (0.0) {};

  Point::Point (float x, float y, float z)
    : x_ (x), y_ (y), z_ (z) {};

  Point & Point::operator= (const Point &p) {
    // Avoid self-assignment
    if (this == &p) {
      return *this;
    }

    x_ = p.x_;
    y_ = p.y_;
    z_ = p.z_;

    return *this;
  };

  std::ostream & operator<< (std::ostream &os, const Point &p) {
    return os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
  }

  Triangle::Triangle()
    : p0_ (Point()), p1_ (Point()), p2_ (Point()) {};
  
  Triangle::Triangle(const Point &p0, const Point &p1, const Point &p2) 
    : p0_ (p0), p1_ (p1), p2_ (p2) {};
    
  std::ostream & operator <<(std::ostream &os, const Triangle &tri) {
    return os << tri.p0_ << " " << tri.p1_ << " " << tri.p2_;
  }

}