/*
** EPITECH PROJECT, 2023
** aaaa
** File description:
** aaa
*/

#pragma once
#include"Vector3D.hpp"

namespace Math {

    class Point3D {
    public:
        double x, y, z;
        Point3D() : x(0), y(0), z(0) {}
        Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
        Point3D(const Point3D& other) = default;
        Point3D(Point3D&& other) = default;
        Point3D& operator=(const Point3D& other) = default;
        Point3D& operator=(Point3D&& other) = default;
        Point3D operator+(const Vector3D& vec);
        Point3D& operator+=(const Vector3D& vec);
        Vector3D operator-(const Point3D& other);
        Point3D operator-(const Vector3D& vec);
        Point3D& operator-=(const Vector3D& vec);
        bool operator==(const Point3D& other);
        bool operator!=(const Point3D& other);
    };
};

