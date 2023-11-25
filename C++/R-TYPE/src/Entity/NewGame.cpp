/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman [WSL: fedora]
** File description:
** NewGame
*/

#include "../../includes/NewGame.hpp"

NewGame::NewGame()
{
    name.assign("");
    level = 0;
    players = 0;
    map = "map2.txt";
    i = 0;
    getMapList();

}

void NewGame::resetValues(void)
{
    name.assign("");
    level = 0;
    players = 0;
    map = "map2.txt";
    i = 0;
    getMapList();
}

void NewGame::getMapList(void)
{
    std::vector<std::string> fileList;
    std::string directoryPath = "../maps";
    iMax = 0;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                fileList.push_back(entry.path().filename().string());
                iMax++;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    mapList = fileList;
    // if (!mapList.empty()) {
    //     std::cout << "Liste des fichiers dans le dossier :" << std::endl;
    //     for (const std::string& fileName : mapList) {
    //         std::cout << fileName << std::endl;
    //     }
    // } else {
    //     std::cout << "Le dossier est vide ou n'existe pas." << std::endl;
    // }
}

NewGame::~NewGame()
{
}
