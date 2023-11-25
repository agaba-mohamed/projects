/*
** EPITECH PROJECT, 2023
** aaa
** File description:
** aaaa
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../includes/RayTracer.hpp"
#include<libconfig.h++>

struct Color {
    double r, g, b;

    Color() {
        r = g = b = 0;
    }

    Color(double i, double j, double k) {
        r = i, g = j, b = k;
    }

    Color operator*(double d) {
        return Color(r * d, g * d, b * d);
    }
};

void write_color(int r, int g, int b)
{
    std::cout << r << " " << g << " " << b << std::endl;
}

struct Vector {
    double x, y, z;

    Vector() {
        x = y = z = 0;
    }

    Vector(double a, double b, double c) {
        x = a, y = b, z = c;
    }

    Vector operator+(Vector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    Vector operator-(Vector v) {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector operator*(double d)
    {
        return Vector(x * d, y * d, z * d);
    }

    Vector operator/(double d)
    {
        return Vector(x / d, y / d, z / d);
    }

    Vector normalize() {
        double mg = sqrt(x * x + y * y + z * z);
        return Vector(x / mg, y / mg, z / mg);
    }
};

double dot(Vector v, Vector b) {
    return (v.x * b.x + v.y * b.y + v.z * b.z);
}

struct Ray
{
    Vector o;
    Vector d;

    Ray(Vector i, Vector j)
    {
        o = i, d = j;
    }
};

struct Sphere {
    Vector c;
    Color clr;
    double r;

    Sphere(Vector i, double j) {
        c = i, r = j;
    }

    Vector getNormal(Vector pi) {
        return (c - pi) / r;
    }

    bool intersect(Ray ray, double& t) {
        Vector o = ray.o;
        Vector d = ray.d;
        Vector oc = o - c;
        double b = 2 * dot(oc, d);
        double c = dot(oc, oc) - r * r;
        double disc = b * b - 4 * c;
        if (disc < 0)
            return false;
        else {
            disc = sqrt(disc);
            double t0 = (-b - disc) / 2;
            double t1 = (-b + disc) / 2;
            t = (t0 < t1) ? t0 : t1;
            return true;
        }
    }
};


struct Cylinder {
    Vector center;
    double radius;
    double height;

    Cylinder(Vector c, double r, double h) {
        center = c, radius = r, height = h;
    }

    Vector getNormal(Vector pi) {
        Vector pc = pi - center;
        pc.y = 0;
        return pc.normalize();
    }

    bool intersect(Ray ray, double& t) {
        Vector o = ray.o;
        Vector d = ray.d;

        double a = d.x * d.x + d.z * d.z;
        double b = 2 * (d.x * (o.x - center.x) + d.z * (o.z - center.z));
        double c = (o.x - center.x) * (o.x - center.x) + (o.z - center.z) * (o.z - center.z);
        double disc = b * b - 4 * a * (c - radius * radius);
        if (disc < 0)
            return false;
        else {
            disc = sqrt(disc);
            double t0 = (-b - disc) / (2 * a);
            double t1 = (-b + disc) / (2 * a);
            double y0 = o.y + t0 * d.y;
            double y1 = o.y + t1 * d.y;

            // Check if the intersection is within the height range of the cylinder
            if (y0 < center.y || y0 > center.y + height) {
                if (y1 < center.y || y1 > center.y + height)
                    return false;
                else
                    t = t1;
            }
            else {
                t = t0;
            }
            return true;
        }
    }
};


typedef struct
{
    int x;
    int y;
    int z;
}pos_t;


typedef struct
{
    pos_t cam;
    int height;
    int width;
    std::vector<Sphere> spr;
    std::vector<Sphere>directional_lights;
}Scene;


Scene getScn(char *file)
{
    libconfig::Config cfg;
    Scene scn;
    int width = 500;
    int height = 500;
    cfg.readFile(file);
    const libconfig::Setting& camera = cfg.lookup("camera");
    scn.width = camera["resolution"]["width"];
    scn.height = camera["resolution"]["height"];
    scn.cam.x = camera["position"]["x"];
    scn.cam.y = camera["position"]["y"];
    scn.cam.z = camera["position"]["z"];
    const libconfig::Setting& primitives = cfg.lookup("primitives");
    const libconfig::Setting& spheres = primitives["spheres"];
    int num_spheres = spheres.getLength();
    for (int i = 0; i < num_spheres; ++i) {
        Sphere s(Vector(width / 2, height / 2, 1), 50);
        const libconfig::Setting& sphere = spheres[i];
        int test = sphere["x"];
        s.c.x = (double)test;
        test = sphere["y"];
        s.c.y = (double)test;
        test = sphere["z"];
        s.c.z = (double)test;
        test = s.r;
        s.r = (double)test;
        test = sphere["color"]["r"];
        s.clr.r = (double)test;
        test = sphere["color"]["g"];
        s.clr.g = (double)test;
        test = sphere["color"]["b"];
        s.clr.b = (double)test;
        scn.spr.push_back(s);
    }
    const libconfig::Setting& lights = cfg.lookup("lights");
    double ambient = lights["ambient"];
    double diffuse = lights["diffuse"];
    const libconfig::Setting& point_lights = lights["point"];
    int num_point_lights = point_lights.getLength();
    for (int i = 0; i < num_point_lights; ++i) {
        Sphere s(Vector(width / 2, height / 2, 1), 50);
        const libconfig::Setting& point_light = point_lights[i];
        int test = point_light["x"];
        s.c.x = (double)test;
        test = point_light["y"];
        s.c.y = (double)test;
        test = point_light["z"];
        s.c.z = (double)test;
        s.r = 1;
        scn.directional_lights.push_back(s);
    }
    return scn;
}

int main(int ac, char** av)
{
    // const int width = 500;
    // const int height = 500;
    std::ofstream out("out.ppm");
    // Color white(0, 255, 0);
    // Sphere sphere(Vector(width / 2, height / 2, 1), 50);
    // Sphere light(Vector(width / 2, 60, 50), 1);
    // Cylinder cylinder(Vector(width / 2 - 100, height / 2 - 100, 1), 50, 100);
    // std::vector<Sphere> spheres;
    // spheres.push_back(sphere);
    // spheres.push_back(light);
    // std::vector<Cylinder> cylinders;
    // cylinders.push_back(cylinder);
    Scene scn = getScn(av[1]);
    out << "P3\n"
        << scn.width << "\n"
        << scn.height << "\n"
        << "255\n";
    for (int y = 0; y < scn.height; y++) {
        for (int x = 0; x < scn.width; x++) {
            Color pixel_col;
            Ray ray(Vector(x, y, 0), Vector(0, 0, 1));
            double t = 20000;
            double u = (double)x / (scn.width - 1);
            double v = (double)y / (scn.height - 1);

            bool hit_sphere = false;
            bool hit_cylinder = false;
            for (int i = 0; i < scn.spr.size(); i++) {
                if (scn.spr[i].intersect(ray, t)) {
                    Vector pi = ray.o + ray.d * t;
                    Vector L = scn.directional_lights[0].c - pi;
                    Vector N = scn.spr[i].getNormal(pi);
                    double dt = dot(L.normalize(), N.normalize());
                    if (dt < 0)
                        dt = dt * -1;
                    pixel_col = scn.spr[i].clr * dt;
                    hit_sphere = true;
                    break;
                }
            }
            // if (!hit_sphere) {
            //     for (int i = 0; i < cylinders.size(); i++) {
            //         if (cylinders[i].intersect(ray, t)) {
            //             Vector pi = ray.o + ray.d * t;
            //             Vector L = light.c - pi;
            //             Vector N = cylinders[i].getNormal(pi);
            //             double dt = dot(L.normalize(), N.normalize());
            //             if (dt < 0)
            //                 dt = dt * -1;
            //             pixel_col = white * dt;
            //             hit_cylinder = true;
            //             break;
            //         }
            //     }
            // }

            if (!hit_sphere && !hit_cylinder) {
                // No intersection, set background color
                pixel_col = Color(0, 0, 0);
            }
            out << (int)pixel_col.r << std::endl;
            out << (int)pixel_col.g << std::endl;
            out << (int)pixel_col.b << std::endl;
        }
    }

    return 0;
}
