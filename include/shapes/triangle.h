#ifndef CRAYON_TRIANGLE_SPHERE_H
#define CRAYON_TRIANGLE_SPHERE_H

#include "core/crayon.h"
#include "core/vector.h"
#include "core/shape.h"


namespace crayon {

// 
// Triangle
// 
class Triangle : public Shape {
private:
    Point3d a, b, c;
    Vector3d ab, bc, ca, n;
public:
    Triangle(Point3d a, Point3d b, Point3d c) : Shape(), a(a), b(b), c(c) {
        // edge
        ab = b - a; bc = c - b; ca = a - c;
        // normal
        n = cross(ab, bc).normalized();
    }
    // interface
    Bounds3d objectBound() const;
    bool intersect(const Ray &ray, double *t_hit, Interaction *isect) const;
};

} // namespace crayon

#endif
