#ifndef CRAYON_CORE_SCENE_H
#define CRAYON_CORE_SCENE_H

#include "core/crayon.h"
#include "core/shape.h"


namespace crayon {

// 
// Scene
// 
class Scene {
public:
    std::vector<std::shared_ptr<Shape>> objects;
public:
    Scene() {}
    
    void add(std::shared_ptr<Shape> object) {
        objects.push_back(object);
    }

    bool intersect(const Ray &ray, Interaction &isect) const {
        double t_hit = ray.tmax;
        bool hitted = false;
        for (auto object : objects) {
            if (object.get()->intersect(ray, t_hit, isect)) {
                ray.tmax = t_hit;
                hitted = true;
            }
        }
        return hitted;
    }

};

} // namespace crayon

#endif
