#ifndef CRAYON_CORE_RAY_H
#define CRAYON_CORE_RAY_H

#include "core/crayon.h"
#include "core/vector.h"


namespace crayon {

// 
// Ray
// 
class Ray {
public:
    Point3d o;
    Vector3d d;
public:
    // constructor
    Ray() {}
    Ray(const Point3d &o, const Vector3d &d) : o(o), d(d) {}
    // I/O
    friend std::ostream &operator<<(std::ostream &os, const Ray &r) {
        os << "[o=" << r.o << ", d=" << r.d << "]"; return os;
    }
    // at
    Point3d at(double t) const { return o + t * d; }
    Point3d operator()(double t) const { return o + t * d; }
};
  
} // namespace crayon


#endif