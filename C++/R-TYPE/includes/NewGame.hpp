/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: fedora]
** File description:
** NewGame
*/

#ifndef NEWGAME_HPP_
#define NEWGAME_HPP_

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

class NewGame {
    public:
        NewGame();
        ~NewGame();

        void resetValues(void);
        void getMapList(void);

        std::string name;
        int         level;
        int         players;
        std::string map;
        std::vector<std::string> mapList;
        int         i;
        int         iMax;
};


#endif /* !NEWGAME_HPP_ */
