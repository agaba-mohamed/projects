/*
** EPITECH PROJECT, 2023
** aaaaa
** File description:
** aaaa
*/

#include "../includes/RayTracer.hpp"

bool RayTracer::Sphere::hits(Ray ray)
{
    Math::Point3D o = ray.origin;
    Math::Vector3D d = ray.direction;
    double a = d.dot(d);
    double b = 2 * d.dot(o - center);
    double c = (o - center).dot(o - center) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    } else {
        return true;
    }
}
bool RayTracer::Rect::hits(RayTracer::Ray ray) {
    float denom = ray.direction.dot(ray.direction);
    if (abs(denom) > 0.0001f) // your favorite epsilon
    {
        float t = (center - ray.origin).dot(ray.direction) / denom;
        if (t >= 0) return true; // you might want to allow an epsilon here too
    }
    return false;
}
