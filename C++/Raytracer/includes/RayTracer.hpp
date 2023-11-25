#include "Vector3D.hpp"
#include "Point3D.hpp"
#include<utility>
#include<vector>
namespace RayTracer {
    class Ray {
    public:
        Math::Point3D origin;
        Math::Vector3D direction;
        Ray() : origin(Math::Point3D()), direction(Math::Vector3D()) {}
        Ray(const Math::Point3D& o, const Math::Vector3D& d) : origin(o), direction(d) {}
        Ray(const Ray& other) : origin(other.origin), direction(other.direction) {}
        Ray(Ray&& other) : origin(std::move(other.origin)), direction(std::move(other.direction)) {}
        Ray& operator=(const Ray& other);
        Ray& operator=(Ray&& other);
    };
    class Sphere {
    public:
        Math::Point3D center;
        double radius;
        Sphere(Math::Point3D center, double radius) : center(center), radius(radius) {}
        bool hits(Ray ray);
    };
    class Rect {
    public:
        Math::Point3D center;
        double radius;
        Rect(Math::Point3D center, double radius) : center(center), radius(radius) {}
        bool hits(Ray ray);
    };
    class Rectangle3D {
    public:
        Math::Point3D origin;
        Math::Vector3D bottom_side;
        Math::Vector3D left_side;

        Rectangle3D(Math::Point3D _origin,Math::Vector3D _bottom_side,Math::Vector3D _left_side)
            : origin(_origin), bottom_side(_bottom_side), left_side(_left_side) {}

        Math::Point3D pointAt(double u, double v) {
            return origin + bottom_side * u + left_side * v;
        }
    };
    class Camera {
    public:
        Math::Point3D origin;
        Rectangle3D screen;
        Camera() : origin(Math::Point3D(0, 0, 0)), screen(Rectangle3D(Math::Point3D(-0.5, -0.5, 1), Math::Vector3D(1, 0, 0), Math::Vector3D(0, 1, 0))) {}
        Ray ray(double u, double v) {
            return Ray(origin, (screen.pointAt(u, v) - origin));
        }
    };
}
