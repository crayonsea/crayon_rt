#include "core/crayon.h"
#include "core/image.h"

using namespace crayon;


int main() {

    // Image

    const int image_width = 256;
    const int image_height = 512;

    Image image(image_width, image_height, ImageFormat::BMP);

    // Render

    std::cout << "gen png 111" << std::endl;

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            auto r = double(j) / (image_width-1);
            auto g = double(i) / (image_height-1);
            auto b = 0.25;
            
            image.setColor(i, j, std::make_tuple(r, g, b));
        }
    }

    image.save("output.bmp");

    return 0;
}
