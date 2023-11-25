/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Health
*/

#include "AComponents.hpp"

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

class Health : public AComponents {
    public:
        Health(std::size_t life) {
            this->life = life;
            this->isAlive = true;
            this->isHit = false;
        };
        ~Health() {};

        void setValue(std::size_t newHealth) {
            life = newHealth;
        };

        std::size_t getValue() {
            return life;
        };

        bool isAlive;
        bool isHit;

    protected:
    private:
        std::size_t life;
};

#endif /* !HEALTH_HPP_ */
