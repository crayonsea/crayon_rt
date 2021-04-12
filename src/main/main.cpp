#include "core/crayon.h"
#include "core/image.h"
#include "core/vector.h"
#include "core/ray.h"
using namespace crayon;


int main() {

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    Image image(image_width, image_height, ImageFormat::BMP);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3d(0, 0, 0);
    auto horizontal = Vector3d(viewport_width, 0, 0);
    auto vertical = Vector3d(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3d(0, 0, focal_length);

    // Render

    std::cout << "gen bmp" << std::endl;

    for (int j = image_height - 1; j >= 0; j--) {
        for (int i = 0; i < image_width; i++) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            
            Vector3d unit_direction = ray.d.normalized();
            auto t = 0.5*(unit_direction.y + 1.0);
            
            auto r = (1.0 - t) * 1.0 + t * 0.5;
            auto g = (1.0 - t) * 1.0 + t * 0.7;
            auto b = (1.0 - t) * 1.0 + t * 1.0;

            // auto r = (double)i / image_width;
            // auto g = (double)j / image_height;
            // auto b = 0.2;

            image.setColor(std::make_tuple(r, g, b));
            // image.setColor(i, j, std::make_tuple(r, g, b));
        }
    }

    image.save("output.bmp");

    return 0;
}
