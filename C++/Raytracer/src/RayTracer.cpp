/*
** EPITECH PROJECT, 2023
** aaa
** File description:
** aaaa
*/

#include "../includes/RayTracer.hpp"

RayTracer::Ray &RayTracer::Ray::operator=(const Ray& other) {
    if (this != &other) {
        origin = other.origin;
        direction = other.direction;
    }
    return *this;
}

RayTracer::Ray &RayTracer::Ray::operator=(Ray&& other) {
    if (this != &other) {
        origin = std::move(other.origin);
        direction = std::move(other.direction);
    }
    return *this;
}
