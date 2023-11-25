/*
** EPITECH PROJECT, 2023
** aaa
** File description:
** aaaa
*/

#include "../includes/Vector3D.hpp"

double Math::Vector3D::length() {
            return sqrt(x*x + y*y + z*z);
}

double Math::Vector3D::dot(const Vector3D& other) {
    return x*other.x + y*other.y + z*other.z;
}

Math::Vector3D Math::Vector3D::operator+(const Vector3D& other) {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Math::Vector3D &Math::Vector3D::operator+=(const Vector3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Math::Vector3D Math::Vector3D::operator-(const Vector3D& other) {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}
Math::Vector3D &Math::Vector3D::operator-=(const Vector3D& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Math::Vector3D Math::Vector3D::operator*(double scalar) {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Math::Vector3D &Math::Vector3D::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Math::Vector3D Math::Vector3D::operator/(double scalar) {
    return Vector3D(x / scalar, y / scalar, z / scalar);
}
Math::Vector3D &Math::Vector3D::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}
