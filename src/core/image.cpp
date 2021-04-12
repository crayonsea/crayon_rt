#include "core/image.h"

namespace crayon {

Image::Image() {}

Image::Image(int width, int height, ImageFormat format) {
    this->width = width;
    this->height = height;
    this->format = format;
    this->framebuffer.resize(width * height);
    this->pixel_index = 0;
}

Image::~Image() {}

//  Set

// (i, j) - pixel sequence coordination
// j: h-1 -> 0, i: 0 -> w
// 从上到下, 从左到右, index++
// 0:(0, h-1), 1:(1, h-1), ... (w-1, h-1)
// ...
// (0, 0), (1, 0), ... (w-1, 0)
void Image::setColor(std::tuple<double, double, double> color) {
    framebuffer[pixel_index++] = color;
}

void Image::setColor(int i, int j, std::tuple<int, int, int> color) {
    double ir, ig, ib;
    std::tie(ir, ig, ib) = color;
    this->setColor(i, j, std::make_tuple(ir, ig, ib));
}

void Image::setColor(int i, int j, std::tuple<double, double, double> color) {
    framebuffer[(height - 1 - j) * width + i] = color;
}

// Save

void Image::save(std::string filename) {
    int pixels = width * height, channels_num = 3;
    unsigned char* output = new unsigned char[pixels * channels_num];
    
    for (size_t i = 0; i < pixels; i++) {
        output[i * 3 + 0] = (unsigned char)(255 * std::max(0.0, std::min(1.0, std::get<0>(framebuffer[i]))));
        output[i * 3 + 1] = (unsigned char)(255 * std::max(0.0, std::min(1.0, std::get<1>(framebuffer[i]))));
        output[i * 3 + 2] = (unsigned char)(255 * std::max(0.0, std::min(1.0, std::get<2>(framebuffer[i]))));
	}

    switch (format) {
        case ImageFormat::BMP:
            stbi_write_bmp(filename.c_str(), width, height, channels_num, output);
            break;
        case ImageFormat::PNG:
            stbi_write_png(filename.c_str(), width, height, channels_num, output, width * channels_num);
            break;
        default:
            throw std::invalid_argument("image format");
    }

    if (output) delete output;
}
    
} // namespace crayon
