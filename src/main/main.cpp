#include "core/crayon.h"
#include "core/image.h"
#include "core/objloader.h"
#include "core/vector.h"
#include "core/ray.h"
#include "shapes/sphere.h"
#include "shapes/cylinder.h"
#include "shapes/trimesh.h"
#include "core/scene.h"
using namespace crayon;


// 
// reflect
// 
Vector3d reflect(const Vector3d &I, const Vector3d &N) {
    return I - 2 * dot(I, N) * N;
}

// 
// refract
// 
Vector3d refract(const Vector3d &I, const Vector3d &N, const double &ior) {
    double cosi = clamp(-1, 1, dot(I, N));
    double etai = 1, etat = ior;
    Vector3d n = N;
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; }
    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n;
}

// 
// Recursive (Whitted-Style) Ray Tracing
// 
Color castRay(const Scene& scene, Ray &ray, int cur_d=0, int max_d=1) {

    if (cur_d >= max_d) {
        // background color - blue sky
        Vector3d unit_direction = ray.d.normalized();
        auto t = 0.5*(unit_direction.y + 1.0);
        auto r = (1.0 - t) * 1.0 + t * 0.5;
        auto g = (1.0 - t) * 1.0 + t * 0.7;
        auto b = (1.0 - t) * 1.0 + t * 1.0;
        return Color(r, g, b);
    }

    Interaction isect;
    if (scene.intersect(ray, isect)) {
        // hit point
        auto p = isect.p;
        // normal
        auto n = isect.n;
        std::cout << "*" << isect.n << std::endl;
        return Color(n[0] + 1, n[1] + 1, n[2] + 1) * 0.5;
    }

    return castRay(scene, ray, cur_d + 1);
}

int main() {

    // // test load obj
    // ObjLoader::load("scenes/models/teapot.obj");
    
    // exit(0);

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 300;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    Image image(image_width, image_height, ImageFormat::BMP);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3d(0, 0, 5);
    auto horizontal = Vector3d(viewport_width, 0, 0);
    auto vertical = Vector3d(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3d(0, 0, focal_length);

    // Scene

    TriMesh trimesh("scenes/models/teapot.obj");

    Scene scene;
    scene.add(std::make_shared<Sphere>(Point3d(0, 0, -2), 0.5));
    scene.add(std::make_shared<Triangle>(Point3d(0, 0, -2), Point3d(1, 1, -2), Point3d(-1, 1, -2)));
    // scene.add(std::make_shared<Cylinder>(Point3d(0.0, 2, -3), 0.7, 2));
    
    // Render

    std::cout << "gen bmp" << std::endl;

    for (int j = image_height - 1; j >= 0; j--) {
        std::cout << "raws: " << j << " / " << image_height << std::endl;
        for (int i = 0; i < image_width; i++) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            
            Color color = castRay(scene, ray);

            image.setColor(color);

            // image.setColor(std::make_tuple(r, g, b));
            // // image.setColor(i, j, std::make_tuple(r, g, b));
        }
    }

    image.save("output.bmp");

    return 0;
}
