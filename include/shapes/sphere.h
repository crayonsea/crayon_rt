#ifndef CRAYON_SHAPES_SPHERE_H
#define CRAYON_SHAPES_SPHERE_H

#include "core/crayon.h"
#include "core/vector.h"
#include "core/shape.h"


namespace crayon {

// 
// Sphere
// 
class Sphere : public Shape {
private:
    Point3d center;
    double radius;
public:
    Sphere(Point3d center, double radius)
        : Shape(), 
        center(center), radius(radius) {}
    // interface
    Bounds3d objectBound() const;
    // intersect
    bool intersect(const Ray &ray, double &t_hit, Interaction &isect) const;
};

} // namespace crayon

#endif
