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
    Vector3d center_axis;
    Point3d p_bottom, p_up;

public:
    Cylinder(Point3d center, double radius, double length)
        : Shape(), 
        center(center), radius(radius), length(length) {
            center_axis = Vector3d(0, 1, 0);
            p_bottom = center + Point3d(1, 0, 1);
            p_up = p_bottom + center_axis * length;
            center_up = center + center_axis * length;
        }
    // interface
    Bounds3d objectBound() const;
    // intersect
    bool intersect(const Ray &ray, double &t_hit, Interaction &isect) const;
};

} // namespace crayon

#endif
