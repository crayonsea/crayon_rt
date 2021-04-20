#include "shapes/cylinder.h"

namespace crayon {

Bounds3d Cylinder::objectBound() const {
    return Bounds3d(Point3d(-radius, -radius, -radius), Point3d(radius, radius, radius));
}

bool Cylinder::intersect(const Ray &ray, double &t_hit, Interaction &isect) const {
    // 垂直于 xoz 平面的圆柱
    auto &n = center_norm;
    
    // 与底面相交
    double t = ray.tmax;
    double t0 = dot((center - ray.o), n) / dot(ray.d, n);
    double t1 = dot((center_up - ray.o), n) / dot(ray.d, n);
    
    // 交点是否在底面上
    auto p0 = ray.at(t0);
    auto p1 = ray.at(t1);
    auto dist_0 = (p0 - center).length();
    auto dist_1 = (p1 - center_up).length();

    auto n0 = dot(n, ray.d) < 0? n: -n;
    if (0 < t0 && t0 < t && dist_0 < radius) {
        isect = Interaction(p0, n0, -ray.d);
        t = t0;
    }
    if (0 < t1 && t1 < t && dist_1 < radius) {
        isect = Interaction(p1, n0, -ray.d);
        t = t1;
    }

    // 交点是否在柱面上
    auto a = ray.o - center;
    auto A = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
    auto B = 2 * (a.x * ray.d.x + a.z * ray.d.z);
    auto C = a.x * a.x + a.z * a.z - radius * radius;

    if (Quadratic(A, B, C, &t0, &t1)) {
        auto t2 = t0 < 0.0? t1: t0;
        auto p2 = ray.at(t2);

        if (t2 < t && center.y < p2.y && p2.y < center_up.y) {
            auto n2 = (p2 - Point3d(center.x, p2.y, center.z)).normalized();
            isect = Interaction(p2, n2, -ray.d);
            t = t2;
        }
    }
    
    t_hit = t;

    return t_hit < ray.tmax;
    
    // // 与底面相交
    // double t = ray.tmax;
    // double t0 = dot((p_bottom - ray.o), n) / dot(ray.d, n);
    // double t1 = dot((p_up - ray.o), n) / dot(ray.d, n);
    // // 与平面相交
    // if (0 < t0 && t0 < ray.tmax) {
    //     auto p0 = ray.at(t0);
    //     auto dist_0 = (p0 - center).length();
    //     if (dist_0 < radius) {  // 与底面相交
    //         t = t0;
    //         isect = Interaction(p0, center_norm, -ray.d);
    //     }
    // }
    // if (0 < t1 && t1 < t) {
    //     auto p1 = ray.at(t1);
    //     auto dist_1 = (p1 - center_up).length();
    //     if (dist_1 < radius) {  // 与底面相交
    //         t = t1;
    //         isect = Interaction(p1, -center_norm, -ray.d);
    //     }
    // }

    // // 与柱面相交

    // auto x = ray.o - center;
    // double a = ray.d[0] * ray.d[0] + ray.d[2] * ray.d[2];
    // double b = 2 * (x[0] * ray.d[0] + x[2] * ray.d[2]);
    // double c = (x[0]*x[0] + x[2]*x[2]) - radius * radius;
    
    // // double t0, t1;
    // if (!Quadratic(a, b, c, &t0, &t1)) {
    //     return t < ray.tmax;
    // }
    // if (t0 > ray.tmax || t1 < 0.0) {
    //     return t < ray.tmax;
    // }

    // auto t2 = t0 < 0.0? t1: t0;
    // auto p_hit = ray.at(t2);

    // if (t2 < t && center[1] < p_hit[1] && p_hit[1] < center_up[1]) {
    //     // norm = hit - center
    //     auto p_center = Point3d(center[0], p_hit[1], center[2]);
    //     auto p_norm = (p_hit - p_center).normalized();
    //     t_hit = t;
    //     isect = Interaction(p_hit, p_norm, -ray.d);
    // }
    
    return false;
}
    
} // namespace crayon
