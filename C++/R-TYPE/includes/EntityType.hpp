#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

class Rect {
public:
    int right;
    int left;
    int top;
    int bottom;
    Rect() : left(0), right(0), top(0), bottom(0) {}
    Rect(int right, int left, int top, int bottom) : right(right), left(left), top(top), bottom(bottom) {}
};

class Pos {
public:
    float x;
    float y;
    float speed;
    char direction;
    Pos() : x(0), y(0), speed(0), direction('N') {}
    Pos(float x, float y, int speed, const char &direction) : x(x), y(y), speed(speed), direction(direction) {}
};

class EntityType {
public:
    EntityType(const std::string &fileConf);
    EntityType(){}
    std::string name;
    std::string text;
    Pos pos;
    Pos size;
    Rect rect;
    bool hitbox;
    bool render;
    int health;
    std::string weapon;
    std::string script;
    std::string file;
    std::string fileDesc = "\"";
};
