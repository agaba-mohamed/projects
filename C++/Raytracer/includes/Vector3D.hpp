/*
** EPITECH PROJECT, 2023
** aaaa
** File description:
** aaaa
*/

#pragma once
#include<math.h>

namespace Math {
    class Vector3D {
    public:
        double x, y, z;
        Vector3D() : x(0), y(0), z(0) {}
        Vector3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
        Vector3D(const Vector3D& other) = default;
        Vector3D(Vector3D&& other) = default;
        Vector3D& operator=(const Vector3D& other) = default;
        Vector3D& operator=(Vector3D&& other) = default;
        double length();
        double dot(const Vector3D& other);
        Vector3D operator+(const Vector3D& other);
        Vector3D& operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other);
        Vector3D& operator-=(const Vector3D& other);
        Vector3D operator*(double scalar);
        Vector3D& operator*=(double scalar);
        Vector3D operator/(double scalar);
        Vector3D& operator/=(double scalar);
    };
}
