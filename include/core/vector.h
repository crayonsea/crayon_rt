#ifndef CRAYON_CORE_VECTOR_H
#define CRAYON_CORE_VECTOR_H

#include "core/crayon.h"


namespace crayon {

// 
// Vector 2
// 

template <typename T>
class Vector2 {
public:
    T x, y;
public:
    // constructor
    Vector2() : x(0), y(0) {}
    Vector2(T a) : x(a), y(a) {}
    Vector2(T x, T y) : x(x), y(y) {}
    // I/O
    friend std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
        os << "[ " << v.x << ", " << v.y << " ]"; return os;
    }
    // index
    T operator[](int idx) const {
        if (idx == 0) return x;
        if (idx == 1) return y;
        throw std::out_of_range("");
    }
    T &operator[](int idx) {
        if (idx == 0) return x;
        if (idx == 1) return y;
        throw std::out_of_range("");
    }
    // numeric
    template <typename U>
    Vector2<T> operator*(U s) const { return Vector2<T>(s * x, s * y); }
    template <typename U>
    Vector2<T> &operator*=(U s) { x *= s; y *= s; return *this; }
    template <typename U>
    Vector2<T> operator/(U f) const {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = 1.0 / f;
        return Vector2<T>(x * inv, y * inv);
    }
    template <typename U>
    Vector2<T> &operator/=(U f) {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = 1.0 / f; x *= inv; y *= inv;
        return *this;
    }
    friend Vector2<T> operator*(const double &a, const Vector2<T> &v) { return v * a; }
    // operator - 0
    Vector2<T> operator-() const { return Vector2(-x, -y); }
    // operator - 1
    Vector2<T> &operator+=(const Vector2<T> &v) { x += v.x; y += v.y; return *this; }
    Vector2<T> &operator-=(const Vector2<T> &v) { x -= v.x; y -= v.y; return *this; }
    bool operator==(const Vector2<T> &v) const { return x == v.x && y == v.y; }
    bool operator!=(const Vector2<T> &v) const { return x != v.x || y != v.y; }
    // operator - 2
    Vector2<T> operator+(const Vector2<T> &v) const { return Vector2(x + v.x, y + v.y); }
    Vector2<T> operator-(const Vector2<T> &v) const { return Vector2(x - v.x, y - v.y); }
    Vector2<T> operator*(const Vector2<T> &v) const { return Vector2(x * v.x, y * v.y); }
    // utils
    T length_squred() const {  return x * x + y * y; }
    T length() const { return std::sqrt(x * x + y * y); }
    Vector2<T> normalized() { T len = this->length(); return Vector3f(x / len, y / len); }
};

// Type

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

// 
//  Vector 3 
// 

template <typename T>
class Vector3 {
public:
    T x, y, z;
public:
    // constructor
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T a) : x(a), y(a), z(a) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    // explicit
    explicit Vector3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {}
    // I/O
    friend std::ostream &operator<<(std::ostream &os, const Vector3<T> &v) {
        os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]"; return os;
    }
    // index
    T operator[](int idx) const {
        if (idx == 0) return x;
        if (idx == 1) return y;
        if (idx == 2) return z;
        throw std::out_of_range("");
    }
    T &operator[](int idx) {
        if (idx == 0) return x;
        if (idx == 1) return y;
        if (idx == 2) return z;
        throw std::out_of_range("");
    }
    // numeric
    template <typename U>
    Vector3<T> operator*(U s) const { return Vector3<T>(s * x, s * y, s * z); }
    template <typename U>
    Vector3<T> &operator*=(U s) { x *= s; y *= s; z *= s; return *this; }
    template <typename U>
    Vector3<T> operator/(U f) const {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = 1.0 / f;
        return Vector3<T>(x * inv, y * inv, z * inv);
    }
    template <typename U>
    Vector3<T> &operator/=(U f) {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = 1.0 / f; x *= inv; y *= inv; z *= inv;
        return *this;
    }
    friend Vector3<T> operator*(const double &a, const Vector3<T> &v) { return v * a; }
    // operator - 0
    Vector3<T> operator-() const { return Vector3(-x, -y, -z); }
    // operator - 1
    Vector3<T> &operator+=(const Vector3<T> &v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3<T> &operator-=(const Vector3<T> &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    bool operator==(const Vector3<T> &v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const Vector3<T> &v) const { return x != v.x || y != v.y || z != v.z; }
    // operator - 2
    Vector3<T> operator+(const Vector3<T> &v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3<T> operator-(const Vector3<T> &v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3<T> operator*(const Vector3<T> &v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
    // utils
    T length_squred() const {  return x * x + y * y + z * z; }
    T length() const { return std::sqrt(x * x + y * y + z * z); }
    Vector3<T> normalized() { T len = this->length(); return Vector3(x / len, y / len, z / len); }
};

// Type

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

// Abs
template <typename T>
Vector2<T> abs(const Vector2<T> &v) { return Vector2<T>(std::abs(v.x), std::abs(v.y)); }

template <typename T>
Vector3<T> abs(const Vector3<T> &v) { return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }

// Dot
template <typename T>
inline T dot(const Vector2<T> &a, const Vector2<T> &b) { return a.x * b.x + a.y * b.y; }

template <typename T>
inline T abs_dot(const Vector2<T> &v1, const Vector2<T> &v2) { return std::abs(dot(v1, v2)); }

template <typename T>
inline T dot(const Vector3<T> &a, const Vector3<T> &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

template <typename T>
inline T abs_dot(const Vector3<T> &v1, const Vector3<T> &v2) { return std::abs(dot(v1, v2)); }

// Cross
template <typename T>
inline Vector3<T> cross(const Vector3<T> &a, const Vector3<T> &b) {
    double v1x = a.x, v1y = a.y, v1z = a.z;
    double v2x = b.x, v2y = b.y, v2z = b.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z), (v1x * v2y) - (v1y * v2x));
}

// 
// Point 2
// 

template <typename T>
class Point2
{
public:
    T x, y;
public:
    Point2() : x(0), y(0) {};
    Point2(T x, T y) : x(x), y(y) {};
    // explicit
    template <typename U>
    explicit Point2(const Point2<U> &p) : x((T)p.x), y((T)p.y) {}
    // explicit operator
    template <typename U>
    explicit operator Vector2<U>() const { return Vector2<U>(x, y); }
    // index
    T operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        throw std::out_of_range("");
    }
    T &operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        throw std::out_of_range("");
    }
    // numeric
    template <typename U>
    Point2<T> operator*(U f) const { return Point2<T>(f * x, f * y); }
    template <typename U>
    Point2<T> &operator*=(U f) { x *= f; y *= f; return *this; }
    template <typename U>
    Point2<T> operator/(U f) const {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = (double)1 / f;
        return Point2<T>(inv * x, inv * y);
    }
    template <typename U>
    Point2<T> &operator/=(U f) {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = (double)1 / f;
        x *= inv; y *= inv;;
        return *this;
    }
    // operator 0
    Point2<T> operator-() const { return Point2<T>(-x, -y); }
    // operator 1
    Point2<T> &operator+=(const Point2<T> &p) { x += p.x; y += p.y; return *this; }
    Point2<T> &operator+=(const Vector2<T> &v) { x += v.x; y += v.y; return *this; }
    Point2<T> &operator-=(const Vector2<T> &v) { x -= v.x; y -= v.y; return *this; }
    bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }
    // operator 2
    Point2<T> operator+(const Point2<T> &p) const { return Point2<T>(x + p.x, y + p.y); }
    Point2<T> operator+(const Vector2<T> &v) const { return Point2<T>(x + v.x, y + v.y); }
    Vector2<T> operator-(const Point2<T> &p) const { return Vector2<T>(x - p.x, y - p.y); }
    Point2<T> operator-(const Vector2<T> &v) const { return Point2<T>(x - v.x, y - v.y); }
};

// Type

typedef Point2<int> Point2i;
typedef Point2<float> Point2f;
typedef Point2<double> Point2d;

// 
// Point 3
// 

template <typename T>
class Point3
{
public:
    T x, y, z;
public:
    Point3() : x(0), y(0), z(0) {};
    Point3(T x, T y, T z) : x(x), y(y), z(z) {};
    // explicit
    template <typename U>
    explicit Point3(const Point3<U> &p) : x((T)p.x), y((T)p.y), z((T)p.z) {}
    // explicit operator
    template <typename U>
    explicit operator Vector3<U>() const { return Vector3<U>(x, y, z); }
    // index
    T operator[](int i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        throw std::out_of_range("");
    }
    T &operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        throw std::out_of_range("");
    }
    // numeric
    template <typename U>
    Point3<T> operator*(U f) const { return Point3<T>(f * x, f * y, f * z); }
    template <typename U>
    Point3<T> &operator*=(U f) { x *= f; y *= f; z *= f; return *this; }
    template <typename U>
    Point3<T> operator/(U f) const {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = (double)1 / f;
        return Point3<T>(inv * x, inv * y, inv * z);
    }
    template <typename U>
    Point3<T> &operator/=(U f) {
        if (f == 0) throw std::invalid_argument("devide 0");
        double inv = (double)1 / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }
    // operator 0
    Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }
    // operator 1
    Point3<T> &operator+=(const Point3<T> &p) { x += p.x; y += p.y; z += p.z; return *this; }
    Point3<T> &operator+=(const Vector3<T> &v) { x += v.x; y += v.y; z += v.z; return *this; }
    Point3<T> &operator-=(const Vector3<T> &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    bool operator==(const Point3<T> &p) const { return x == p.x && y == p.y && z == p.z; }
    bool operator!=(const Point3<T> &p) const { return x != p.x || y != p.y || z != p.z; }
    // operator 2
    Point3<T> operator+(const Point3<T> &p) const { return Point3<T>(x + p.x, y + p.y, z + p.z); }
    Point3<T> operator+(const Vector3<T> &v) const { return Point3<T>(x + v.x, y + v.y, z + v.z); }
    Vector3<T> operator-(const Point3<T> &p) const { return Vector3<T>(x - p.x, y - p.y, z - p.z); }
    Point3<T> operator-(const Vector3<T> &v) const { return Point3<T>(x - v.x, y - v.y, z - v.z); }
};

// Type

typedef Point3<int> Point3i;
typedef Point3<float> Point3f;
typedef Point3<double> Point3d;

} // namespace crayon

#endif
