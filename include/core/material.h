#ifndef CRAYON_CORE_MATERIAL_H
#define CRAYON_CORE_MATERIAL_H

#include "core/crayon.h"
#include "core/vector.h"
#include "core/ray.h"
#include "core/interaction.h"


namespace crayon {

// 
// Material
// 
class Material {
public:
    Material() {}
    // interface
public:
    virtual bool scatter(const Ray& ray_in, const Interaction& isect, Ray& ray_scattered) const = 0;
};

// 
// 
// 

// 
// 
// 



} // namespace crayon

#endif
