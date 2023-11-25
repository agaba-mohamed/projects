/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: fedora]
** File description:
** RectData
*/

#ifndef RECTDATA_HPP_
#define RECTDATA_HPP_

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

class RectData {
    public:
        RectData();
        ~RectData();

        std::string _name;
        std::size_t _difficulty;
        std::size_t  _playersMax;
        std::string _mapName;
        std::size_t _position;
        bool isNotEmpty;

    protected:
    private:
};

#endif /* !RECTDATA_HPP_ */
