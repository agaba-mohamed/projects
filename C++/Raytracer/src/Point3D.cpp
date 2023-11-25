/*
** EPITECH PROJECT, 2023
** aaaa
** File description:
** aaa
*/

#include "../includes/Point3D.hpp"

Math::Point3D Math::Point3D::operator+(const Math::Vector3D& vec) {
    return Math::Point3D(x + vec.x, y + vec.y, z + vec.z);
}

Math::Point3D &Math::Point3D::operator+=(const Math::Vector3D& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Math::Vector3D Math::Point3D::operator-(const Math::Point3D& other) {
    return Math::Vector3D(x - other.x, y - other.y, z - other.z);
}

Math::Point3D Math::Point3D::operator-(const Math::Vector3D& vec) {
    return Math::Point3D(x - vec.x, y - vec.y, z - vec.z);
}

Math::Point3D &Math::Point3D::operator-=(const Math::Vector3D& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

bool Math::Point3D::operator==(const Math::Point3D& other) {
    return x == other.x && y == other.y && z == other.z;
}

bool Math::Point3D::operator!=(const Math::Point3D& other) {
    return !(*this == other);
}
