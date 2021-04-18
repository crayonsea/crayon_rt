#ifndef CRAYON_SHAPES_TRIMESH_H
#define CRAYON_SHAPES_TRIMESH_H

#include "core/crayon.h"
#include "core/vector.h"
#include "core/shape.h"
#include "core/objloader.h"


namespace crayon {

// 
// Triangle
// 
class Triangle : public Shape {
private:
    Point3d a, b, c;
    Vector3d ab, bc, ca, n;
public:
    Triangle(const Point3d &a, const Point3d &b, const Point3d &c) : Shape(), a(a), b(b), c(c) {
        // edge
        ab = b - a; bc = c - b; ca = a - c;
        // normal
        n = cross(ab, bc).normalized();
    }
    // interface
    Bounds3d objectBound() const;
    bool intersect(const Ray &ray, double &t_hit, Interaction &isect) const;
};

// 
// Triangle Mesh
// 
class TriMesh : public Shape {
private:
    std::vector<std::shared_ptr<Triangle>> triangles;

public:
    TriMesh() : Shape() {}
    TriMesh(std::string model_path);
    // interface
    Bounds3d objectBound() const;
    bool intersect(const Ray &ray, double &t_hit, Interaction &isect) const;
};

} // namespace crayon

#endif
