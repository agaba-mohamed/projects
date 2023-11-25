/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Position
*/

#include "Health.hpp"

#ifndef POSITION_HPP_
#define POSITION_HPP_

class Position : public virtual AComponents{
    public:
        Position(float x, float y, char direction,  float speed) {
            this->x = x;
            this->y = y;
            this->direction = direction;
            this->speed = speed;
        };
        ~Position() {};

        Position& operator=(const Position &other) {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
                this->direction = other.direction;
                this->speed = other.speed;
            }
            AComponents::operator=(other);
            IComponents::operator=(other);
            return *this;
        }

        float x;
        float y;
        char direction;
        float speed;

    protected:
    private:
};

#endif /* !POSITION_HPP_ */
