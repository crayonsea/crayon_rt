#ifndef CRAYON_SHAPES_CYLINDER_H
#define CRAYON_SHAPES_CYLINDER_H

#include "core/crayon.h"
#include "core/vector.h"
#include "core/shape.h"


namespace crayon {

// 
// Cylinder
// 
class Cylinder : public Shape {
private:
    Point3d center, center_up;
    double radius, length;
    Vector3d center_norm;
public:
    Cylinder(Point3d center, double radius, double length)
        : Shape(), 
        center(center), radius(radius), length(length) {
            center_norm = Vector3d(0, 1, 0);
            center_up = center + center_norm * length;
        }
    // interface
    Bounds3d objectBound() const;
    // intersect
    bool intersect(const Ray &ray, double &t_hit, Interaction &isect) const;
};

} // namespace crayon

#endif
