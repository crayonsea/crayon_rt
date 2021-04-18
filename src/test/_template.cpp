#include "core/crayon.h"
#include "core/image.h"
#include "core/vector.h"


using namespace crayon;


int main() {

    Vector3d a(1.0), b(2.0);

    std::cout << a << ", " << b << std::endl;
    
    std::cout << -a << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a * 5 << std::endl;
    std::cout << 5 * a << std::endl;
    std::cout << a.length() << std::endl;
    std::cout << a.length_squred() << std::endl;

    Vector2d c(1.0, 2.0), d(3.0, 2.0);
    std::cout << c << ", " << d << std::endl;
    std::cout << c + d << std::endl;
    std::cout << c - d << std::endl;
    std::cout << c * d << std::endl;
    std::cout << c * 2 << std::endl;
    std::cout << 2 * c << std::endl;
    std::cout << c.length() << std::endl;
    std::cout << c.length_squred() << std::endl;

    std::cout << dot(a, b) << std::endl;
    std::cout << cross(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 1.0, 0.0)) << std::endl;

    Point3d p(0.0, 0.0, 0.0), q(1.0, 0.0, 0.0);
    Vector3d pv(p - q);
    std::cout << pv << std::endl;

    return 0;
}

