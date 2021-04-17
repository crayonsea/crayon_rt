#include "shapes/sphere.h"

namespace crayon {

Bounds3d Sphere::objectBound() const {
    return Bounds3d(Point3d(-radius, -radius, -radius), Point3d(radius, radius, radius));
}

bool Sphere::intersect(const Ray &ray, double *t_hit, Interaction *isect) const {
    auto x = ray.o - center;
    double a = dot(ray.d, ray.d);
    double b = 2 * dot(x, ray.d);
    double c = dot(x, x) - radius * radius;
    
    double t0, t1;
    if (!Quadratic(a, b, c, &t0, &t1)) return false;
    if (t0 > ray.tmax || t1 < 0.0) return false;

    auto t = t0 < 0.0? t1: t0;
    auto p_hit = ray.at(t);
    // norm = hit - center
    auto p_norm = (p_hit - center).normalized();
    
    *t_hit = t0;
    *isect = Interaction(p_hit, p_norm, -ray.d);
    
    return true;
}
    
} // namespace crayon
