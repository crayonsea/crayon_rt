#ifndef CRAYON_CORE_IMAGE_H
#define CRAYON_CORE_IMAGE_H

#include "core/crayon.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


namespace crayon {

enum class ImageFormat : int {
    BMP = 1,
    PNG = 2
};

class Image {
private:
    int width, height;
    ImageFormat format;
    int pixel_index;
    std::vector<std::tuple<double, double, double>> framebuffer;
    
public:
    Image();
    Image(int width, int height, ImageFormat format);
    ~Image();
    
    void setColor(std::tuple<double, double, double> color);
    void setColor(int i, int j, std::tuple<int, int, int> color);
    void setColor(int i, int j, std::tuple<double, double, double> color);
    void save(std::string filename);
};

} // namespace crayon


#endif