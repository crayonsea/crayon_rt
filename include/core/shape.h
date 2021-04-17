#ifndef CRAYON_CORE_SHAPE_H
#define CRAYON_CORE_SHAPE_H

#include "core/crayon.h"
#include "core/vector.h"
#include "core/ray.h"
#include "core/interaction.h"


namespace crayon {

// 
// Shape
// 
class Shape {
public:
    Shape() {}
    // interface
    virtual Bounds3d objectBound() const = 0;
    virtual bool intersect(const Ray &ray, double *t_hit, Interaction *isect) const = 0;
};

} // namespace crayon

#endif
