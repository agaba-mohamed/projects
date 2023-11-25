/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** IComponents
*/

#include "../RType.hpp"

#ifndef ICOMPONENTS_HPP_
#define ICOMPONENTS_HPP_

class IComponents {
    public:
        virtual ~IComponents() = default;

        virtual IComponents& operator=(const IComponents &other) {
            // Default implementation here.
            return *this;
        }

    protected:
    private:
};

#endif /* !ICOMPONENTS_HPP_ */
