#include "shapes/cylinder.h"

namespace crayon {

Bounds3d Cylinder::objectBound() const {
    return Bounds3d(Point3d(-radius, -radius, -radius), Point3d(radius, radius, radius));
}

bool Cylinder::intersect(const Ray &ray, double &t_hit, Interaction &isect) const {
    // 平行于 y 轴的圆柱
    auto &n = center_axis;
    
    // 与底面相交
    double t = ray.tmax;
    double t0 = dot((p_bottom - ray.o), n) / dot(ray.d, n);
    double t1 = dot((p_up - ray.o), n) / dot(ray.d, n);
    // 与平面相交
    if (0 < t0 && t0 < ray.tmax) {
        auto p0 = ray.at(t0);
        auto dist_0 = dot(p0-center, p0-center);
        if (dist_0 < radius * radius) {  // 与底面相交
            t = t0;
            isect = Interaction(p0, center_axis, -ray.d);
        }
    }
    if (0 < t1 && t1 < t) {
        auto p1 = ray.at(t1);
        auto dist_1 = dot(p1-center, p1-center);
        if (dist_1 < radius * radius) {  // 与底面相交
            t = t1;
            isect = Interaction(p1, center_axis, -ray.d);
        }
    }

    // 与柱面相交

    auto x = ray.o - center;
    double a = ray.d[0] * ray.d[0] + ray.d[2] * ray.d[2];
    double b = 2 * (x[0] * ray.d[0] + x[2] * ray.d[2]);
    double c = (x[0]*x[0] + x[2]*x[2]) - radius * radius;
    
    // double t0, t1;
    if (!Quadratic(a, b, c, &t0, &t1)) {
        return t < ray.tmax;
    }
    if (t0 > ray.tmax || t1 < 0.0) {
        return t < ray.tmax;
    }

    auto t2 = t0 < 0.0? t1: t0;
    auto p_hit = ray.at(t2);

    if (t2 < t && center[1] < p_hit[1] && p_hit[1] < center_up[1]) {
        // norm = hit - center
        auto p_center = Point3d(center[0], p_hit[1], center[2]);
        auto p_norm = (p_hit - p_center).normalized();
        t_hit = t;
        isect = Interaction(p_hit, p_norm, -ray.d);
    }
    
    return t < ray.tmax;
}
    
} // namespace crayon
