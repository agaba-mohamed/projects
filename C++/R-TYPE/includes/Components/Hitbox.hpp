/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Hitbox
*/

#pragma once
#include "../Components/Spawning.hpp"

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

class Hitbox : public virtual AComponents {
    public:
        Hitbox(std::size_t left, std::size_t top, std::size_t height, std::size_t width)
                : pos(left, top, 'N', 20), height(height), width(width) {};
        ~Hitbox(){};

        Hitbox& operator=(const Hitbox &other) {
            if (this != &other) {
                this->pos.x = other.pos.x;
                this->pos.y = other.pos.y;
                this->height = other.height;
                this->width = other.width;
            }
            AComponents::operator=(other);
            IComponents::operator=(other);
            return *this;
        }

        bool intersect(const Hitbox& other) const {
            std::size_t thisLeft = pos.x;
            std::size_t thisRight = pos.x + width;
            std::size_t thisTop = pos.y;
            std::size_t thisBottom = pos.y + height;
            std::size_t otherLeft = other.pos.x;
            std::size_t otherRight = other.pos.x + other.width;
            std::size_t otherTop = other.pos.y;
            std::size_t otherBottom = other.pos.y + other.height;
            bool horizontalOverlap = (thisRight >= otherLeft && thisLeft <= otherRight);
            bool verticalOverlap = (thisBottom >= otherTop && thisTop <= otherBottom);
            return (horizontalOverlap && verticalOverlap);
        }

        bool isActive = true;
        Position pos;
        std::size_t height;
        std::size_t width;

    protected:
    private:
};

#endif /* !HITBOX_HPP_ */
