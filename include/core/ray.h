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
    mutable double tmax;
public:
    // constructor
    Ray() {}
    Ray(const Point3d &o, const Vector3d &d, double tmax=std::numeric_limits<double>().max()) : o(o), d(d), tmax(tmax) {}
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