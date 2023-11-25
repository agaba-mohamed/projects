#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "../includes/EntityType.hpp"


EntityType::EntityType(const std::string &fileConf) {
    std::ifstream fileStream(fileConf);
    std::string line;
    while (std::getline(fileStream, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            auto removeSpaces = [](char c) { return std::isspace(static_cast<unsigned char>(c)); };
            key.erase(std::remove_if(key.begin(), key.end(), removeSpaces), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), removeSpaces), value.end());
            if (key == "name") {
                name = value;
            } else if (key == "file") {
                script = value;
            } else if (key == "hitbox") {
                hitbox = (value == "true");
            } else if (key == "texture") {
                text = value;
                render = true;
            } else if (key == "pos") {
                float x, y;
                char dir;
                float speed;
                sscanf(value.c_str(), "{%f,%f,%f,%c}", &x, &y, &speed, &dir);
                pos = Pos(x, y, speed, dir);
            } else if (key == "rect") {
                int left, right, top, bottom;
                sscanf(value.c_str(), "{%d,%d,%d,%d}", &left, &right, &top, &bottom);
                rect = Rect(right, left, top, bottom);
            } else if (key == "size") {
                std::size_t width, height;
                sscanf(value.c_str(), "{%ld,%ld}", &width, &height);
                size = Pos(width, height, 0, 'N');
            } else if (key == "health") {
                health = std::stoi(value);
            } else if (key == "fileDesc") {
                fileDesc = value;
            } else if (key == "weapon") {
                weapon = value;
            }
        }
    }
    fileStream.close();
}
