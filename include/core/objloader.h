#ifndef CRAYON_CORE_OBJLOADER_H
#define CRAYON_CORE_OBJLOADER_H

#include "core/crayon.h"
#include "core/vector.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


namespace crayon {

class ObjLoader {
private:
    
public:
    ObjLoader() {}
    static void load(std::string model_path);
    static void load(std::string model_path, std::vector<Point3d> &verts, std::vector<std::tuple<int, int, int>> &faces);
};

} // namespace crayon

#endif
