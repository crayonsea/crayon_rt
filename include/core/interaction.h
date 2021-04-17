#ifndef CRAYON_CORE_INTERACTION_H
#define CRAYON_CORE_INTERACTION_H

#include "core/crayon.h"
#include "core/vector.h"

namespace crayon {

// 
// Intersection
// 
class Interaction {
public:
    Point3d p;
    Vector3d n;
    // the negative ray direction is stored in wo
    Vector3d wo;
public:
    Interaction() {}
    Interaction(const Point3d &p, const Vector3d &n, const Vector3d &wo) : p(p), n(n), wo(wo) {}
};
    
} // namespace crayon

#endif
