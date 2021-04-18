#include "shapes/trimesh.h"


namespace crayon {
    
    // 
    // Triangle
    // 
    
    Bounds3d Triangle::objectBound() const {
        return Bounds3d();
    }

    bool Triangle::intersect(const Ray &ray, double *t_hit, Interaction *isect) const {
        // 判断 Ray 与 三角形 是否相交
        // 1. Ray 与 三角形所在的平面相交, 得到交点 p
        // 2. 判断交点 p 是否在三角形内部

        // 1.
        double t = dot((a - ray.o), n) / dot(ray.d, n);
        if (t < 0 || t > ray.tmax) return false;

        // 2.
        auto p = ray.at(t);
        auto ap = p - a;
        auto bp = p - b;
        auto cp = p - c;
        auto t0 = cross(ab, ap);
        auto t1 = cross(bc, bp);
        auto t2 = cross(ca, cp);
        auto ret_0 = dot(t0, t1);
        auto ret_1 = dot(t1, t2);
        auto ret_2 = dot(t2, t0);

        if (ret_0 < 0 || ret_1 < 0 || ret_2 < 0) return false;

        *t_hit = t;
        *isect = Interaction(p, n, -ray.d);
        
        return true;
    }

    // 
    // TriMesh
    // 

    TriMesh::TriMesh(std::string model_path) {

        std::vector<Point3d> verts;
        std::vector<std::tuple<int, int, int>> faces;
        
        ObjLoader::load(model_path, verts, faces);

        for (auto face : faces) {
            auto idx_a = std::get<0>(face);
            auto idx_b = std::get<1>(face);
            auto idx_c = std::get<2>(face);
            triangles.push_back(std::make_shared<Triangle>(verts[idx_a], verts[idx_b], verts[idx_c]));
        }
    }

    Bounds3d TriMesh::objectBound() const {
        return Bounds3d();
    }

    bool TriMesh::intersect(const Ray &ray, double *t_hit, Interaction *isect) const {
        bool hit = false;
        for (auto triangle : triangles) {
            if (triangle.get()->intersect(ray, t_hit, isect)) {
                ray.tmax = *t_hit;
                hit = true;
            }
        }
        return hit;
    }
    
} // namespace crayon
