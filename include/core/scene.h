#ifndef CRAYON_CORE_SCENE_H
#define CRAYON_CORE_SCENE_H

#include "core/crayon.h"
#include "core/shape.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;


namespace crayon {

// 
// Scene Type Enum
// 

// Shape
enum class SHAPE {
    SPHERE, TRIANGLE, TRIMESH, CYLINDER
};  

// mapper - enum_to_string
std::unordered_map<std::string, SHAPE> shape_mapper = {
    {"Sphere", SHAPE::SPHERE},
    {"Triangle", SHAPE::TRIANGLE},
    {"TriMesh", SHAPE::TRIMESH},
    {"Cylinder", SHAPE::CYLINDER}
};

// 
// Scene
// 

class Scene {
public:
    std::vector<std::shared_ptr<Shape>> objects;
public:
    Scene() {
        // std::ifstream in("scenes/scene.json");
        // json json_scene;
        // in >> json_scene; in.close();
        
        // std::cout << json_scene["pi"] << std::endl;
        // std::cout << json_scene["renderer"].size() << std::endl;

        // for (const auto &item : json_scene["renderer"].items()) {
        //     std::cout << item.key() << " " << item.value() << std::endl;
        // }

        // auto shapes = json_scene["shapes"];
        // std::cout << shapes << std::endl;
        // std::cout << shapes.dump() << std::endl;
        // std::cout << "shapes " << shapes.size() << std::endl;
        // for (const auto &shape : shapes) {
        //     std::cout << shape["type"] << std::endl;
        //     std::cout << shape["type"].dump() << std::endl;
        //     std::cout << shape["type"].get<std::string>() << std::endl;
        //     if (shape["type"] == "Sphere") {
        //         std::cout << shape["radius"] << std::endl;
        //         std::cout << shape["center"][0] << std::endl;
        //         std::cout << typeid(decltype(0.2)).name() << std::endl;
        //         std::cout << typeid((double)shape["center"][0]).name() << std::endl;
        //     }
        // }

        // scene.add(std::make_shared<Sphere>(Point3d(0, 0, -2), 0.5));
        // scene.add(std::make_shared<Triangle>(Point3d(0, 0, -2), Point3d(1, 1, -2), Point3d(-1, 1, -2)));
        // scene.add(std::make_shared<Cylinder>(Point3d(0.0, 2, -3), 0.7, 2));
    }

    void parse(std::string json_path) {
        // parse json
        std::ifstream in(json_path);
        json json_scene;
        in >> json_scene; in.close();

        std::cout << "Scene config path: " << std::quoted(json_path) << std::endl;

        // 
        // camera


        // 
        // shapes
        std::cout << "[Shape]" << std::endl;
        auto shapes = json_scene["shapes"];
        for (const auto &shape : shapes) {
            std::cout << "  " << shape["type"] << std::endl;
            // shape object
            std::shared_ptr<Shape> cur_shape;
            // gen by type
            auto shape_type = shape_mapper[shape["type"].get<std::string>()];
            switch (shape_type) {
                case SHAPE::SPHERE: {
                    auto center = Point3d(shape["center"][0].get<double>(), shape["center"][1].get<double>(), shape["center"][2].get<double>());
                    auto radius = shape["radius"].get<double>();
                    cur_shape = std::make_shared<Sphere>(center, radius);
                }
                break;
                case SHAPE::TRIANGLE: {
                    auto p0 = Point3d(shape["p0"][0].get<double>(), shape["p0"][1].get<double>(), shape["p0"][2].get<double>());
                    auto p1 = Point3d(shape["p1"][0].get<double>(), shape["p1"][1].get<double>(), shape["p1"][2].get<double>());
                    auto p2 = Point3d(shape["p2"][0].get<double>(), shape["p2"][1].get<double>(), shape["p2"][2].get<double>());
                    cur_shape = std::make_shared<Triangle>(p0, p1, p2);
                }
                break;
                case SHAPE::TRIMESH: {
                    auto model_path = shape["path"].get<std::string>();
                    cur_shape = std::make_shared<TriMesh>(model_path);
                }
                break;
                case SHAPE::CYLINDER: {

                }
                break;
                default:
                    throw std::invalid_argument("SHAPE type error!");
            }
            // add into scene
            this->add(cur_shape);
        }

        // 
        // lights
        
    }
    
    void add(const std::shared_ptr<Shape> &object) {
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
