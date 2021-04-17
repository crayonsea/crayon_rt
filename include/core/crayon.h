#ifndef CRAYON_H
#define CRAYON_H

// type
#include <type_traits>
// numeric
#include <limits>
#include <cmath>
// I/O
#include <iostream>
// STL
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>

namespace crayon {
    // I/O
    class Image;
    // Scene

    // Geometry
    template <typename T>
    class Vector2;
    template <typename T>
    class Vector3;
    template <typename T>
    class Point2;
    template <typename T>
    class Point3;

    // Utils
    inline bool Quadratic(double A, double B, double C, double *t0, double *t1) {
        double discrim = B * B - 4.0 * A * C;
        if (discrim < 0.0) return false;
        
        double root_d = std::sqrt(discrim);
        
        double q;
        if (B < 0) q = -0.5 * (B - root_d);
        else q = -0.5 * (B + root_d);
        
        *t0 = q / A;
        *t1 = C / q;
        if (*t0 > *t1) std::swap(*t0, *t1);
        
        return true;
    }

    
} // namespace crayon





#endif